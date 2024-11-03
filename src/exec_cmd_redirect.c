/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:54:47 by xlok              #+#    #+#             */
/*   Updated: 2024/11/03 19:18:47 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect(t_ms *ms, t_node **cur, int fd_w[2])
{
	t_node	*redirect_node;
	int		kind;

	redirect_node = *cur;
	kind = (*cur)->kind;
	*cur = (*cur)->right;
	if (kind == ND_REDIRECT_IN)
		ms->fd_r = get_filename_fd((*cur)->str, ms->fd_r, READ);
	else if (kind == ND_REDIRECT_HEREDOC)
		ms->fd_r = heredoc_expand(ms, redirect_node);
	else if (kind == ND_REDIRECT_OUT || kind == ND_REDIRECT_APPEND)
	{
		if (fd_w)
		{
			if (kind == ND_REDIRECT_OUT)
				fd_w[1] = get_filename_fd((*cur)->str, fd_w[1], WRITE);
			else
				fd_w[1] = get_filename_fd((*cur)->str, fd_w[1], APPEND);
		}
	}
}

static void	word_split(t_ms *ms)
{
	char	*str;
	int		i;

	str = ms->new_str;
	ms->start = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ms->c = str[i++];
			while (str[i] != ms->c)
				i++;
		}
		else if (ft_isspace(str[i]))
		{
			if (i > ms->start)
				add_cmd_arg(ms, str, ms->start, i);
			i++;
			while (ft_isspace(str[i]))
				i++;
			ms->start = i;
		}
	}
	add_cmd_arg(ms, str, ms->start, i);
}

void	cmd_found(t_ms *ms, t_node *cur, int fd_w[2])
{
	while (cur != NULL)
	{
		if (cur->kind IS_REDIRECT)
		{
			redirect(ms, &cur, fd_w);
			if (ms->cmd_error || g_sig == 2)
				return ;
		}
		else
		{
			expansion_var(ms, cur->str);
			word_split(ms);
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
			if (ms->cmd_error || g_sig == 2)
				return ;
		}
		else
		{
			cmd_found(ms, cur, fd_w);
			if (ms->cmd_error)
				return ;
			break ;
		}
		cur = cur->right;
	}
	ms->fd_w[0] = fd_w[0];
	ms->fd_w[1] = fd_w[1];
}
