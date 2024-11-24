/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:54:47 by xlok              #+#    #+#             */
/*   Updated: 2024/11/24 16:43:23 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check(t_ms *ms, char *str, char *var)
{
	if (ft_strchr(str, ' ') || ft_strchr(str, '\t') || ft_strchr(str, '\n') \
			|| !*ms->new_str)
	{
		ft_dprintf(2, "minishell: %s: ambiguogus redirect\n", var);
		ms->error = 1;
		ms->exit_status = 1;
		free(ms->new_str);
		return (1);
	}
	return (0);
}

static void	redirect(t_ms *ms, t_node **cur, int fd_w[2])
{
	t_node	*redirect_node;
	int		kind;

	redirect_node = *cur;
	kind = (*cur)->kind;
	*cur = (*cur)->right;
	if (kind != ND_REDIRECT_HEREDOC)
	{
		expand_var(ms, (*cur)->str, 0);
		if (check(ms, ms->new_str, (*cur)->str))
			return ;
	}
	if (kind == ND_REDIRECT_IN)
		ms->fd_r = get_filename_fd(ms, ms->new_str, ms->fd_r, READ);
	else if (kind == ND_REDIRECT_HEREDOC)
		ms->fd_r = heredoc_expand(ms, redirect_node);
	else if (kind == ND_REDIRECT_OUT || kind == ND_REDIRECT_APPEND)
	{
		if (kind == ND_REDIRECT_OUT)
			fd_w[1] = get_filename_fd(ms, ms->new_str, fd_w[1], WRITE);
		else
			fd_w[1] = get_filename_fd(ms, ms->new_str, fd_w[1], APPEND);
	}
	if (kind != ND_REDIRECT_HEREDOC)
		free(ms->new_str);
}

void	cmd_found(t_ms *ms, t_node *cur, int fd_w[2])
{
	while (cur != NULL)
	{
		if (cur->kind IS_REDIRECT)
		{
			redirect(ms, &cur, fd_w);
			if (g_sig == 2 || ms->error)
				break ;
		}
		else
		{
			expand_var(ms, cur->str, 0);
			if (*ms->new_str || !ft_strchr(cur->str, '$'))
				add_cmd_arg(ms, ms->new_str, ms->split_s, \
					ft_strlen(ms->new_str));
			free_str(ms->new_str);
		}
		cur = cur->right;
	}
}

void	redirection(t_ms *ms, t_node *cur, int fd_w[2])
{
	if (!fd_w)
		fd_w = init_fd_w(ms);
	init_cmd(ms);
	while (cur && cur->kind)
	{
		if (cur->kind IS_REDIRECT)
		{
			redirect(ms, &cur, fd_w);
			if (g_sig == 2 || ms->error)
				break ;
		}
		else
		{
			cmd_found(ms, cur, fd_w);
			break ;
		}
		cur = cur->right;
	}
	ms->fd_w[0] = fd_w[0];
	ms->fd_w[1] = fd_w[1];
}
