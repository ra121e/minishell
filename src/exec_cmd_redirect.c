/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:54:47 by xlok              #+#    #+#             */
/*   Updated: 2024/11/30 20:58:38 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check(t_ms *ms, char *str, char **ws, char *var)
{
	char	*tmp;

	if ((str && !*str) || !ws || (ws[0] && ws[1]))
	{
		if ((str && !*str && ws) || \
				ft_strchr(var, '\'') || ft_strchr(var, '\"'))
			ft_dprintf(2, "minishell: : No such file or directory\n", var);
		else
			ft_dprintf(2, "minishell: %s: ambiguous redirect\n", var);
		ms->error = 1;
		ms->exit_status = 1;
		free(ms->new_str);
		if (ws)
			free_str_array(ms->word_split);
		return (1);
	}
	if (ws)
	{
		tmp = ms->new_str;
		ms->new_str = *ws;
		free(tmp);
		free(ms->word_split);
		ms->word_split = 0;
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
		if (check(ms, ms->new_str, ms->word_split, (*cur)->str))
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

static void	word_split_to_cmd(t_ms *ms)
{
	int	i;

	i = -1;
	while (ms->word_split[++i])
		add_cmd_arg2(ms, ms->word_split[i]);
	free(ms->word_split);
	ms->word_split = 0;
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
			if (ms->word_split)
				word_split_to_cmd(ms);
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
