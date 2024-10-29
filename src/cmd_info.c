/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:54:47 by xlok              #+#    #+#             */
/*   Updated: 2024/10/29 21:02:56 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_ms *ms, t_node **cur, int fd_w[2])
{
	int		kind;

	kind = (*cur)->kind;
	*cur = (*cur)->right;
	if (kind == ND_REDIRECT_IN)
		ms->fd_r = get_filename_fd((*cur)->str, ms->fd_r, READ);
	else if (kind == ND_REDIRECT_HEREDOC)
		heredoc(ms, (*cur)->str);
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
	ms->cmd_node->fd_r = ms->fd_r;
	ms->cmd_node->fd_w[0] = fd_w[0];
	ms->cmd_node->fd_w[1] = fd_w[1];
}

void	cmd_found(t_ms *ms, t_node *cur, int fd_w[2])
{
	int		i;

	ms->cmd[0] = cur->str;
	cur = cur->right;
	i = 1;
	while (cur != NULL)
	{
		if (cur->kind IS_REDIRECT)
		{
			if (cur->right->kind == ND_COMMAND || \
					cur->right->kind == ND_HEREDOC_DELIMITER)
				redirect(ms, &cur, fd_w);
			if (ms->cmd_error || ms->sig == 2)
				return ;
		}
		else
			ms->cmd[i++] = cur->str;
		cur = cur->right;
	}
	ms->cmd[i] = NULL;
	ms->cmd_node->cmd = ms->cmd;
}

void	cmd_info(t_ms *ms, t_node *cur, int fd_w[2])
{
	if (!fd_w)
		fd_w = init_fd_w(ms);
	init_cmd(ms, cur, fd_w);
	while (cur && cur->kind)
	{
		if (cur->kind IS_REDIRECT)
		{
			if (cur->right->kind == ND_COMMAND || \
					cur->right->kind == ND_HEREDOC_DELIMITER)
				redirect(ms, &cur, fd_w);
			if (ms->cmd_error || ms->sig == 2)
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
	ms->fd_r = fd_w[0];
}
