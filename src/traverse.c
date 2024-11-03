/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:16:22 by athonda           #+#    #+#             */
/*   Updated: 2024/11/03 19:23:53 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	traverse_cmd(t_node *cur, t_ms *ms, int fd_w[2], int action)
{
	if (action == HEREDOC)
		heredoc(ms, cur);
	else
	{
		redirection(ms, cur, fd_w);
		if (!g_sig)
		{
			if (ms->cmd && ms->cmd[0])
				exec_cmd(ms);
			else
			{
				close_fd(ms);
				ms->fd_r = ms->fd_w[0];
			}
		}
//		ft_dprintf(1, "g_sig: %d\n", g_sig);
//		ft_dprintf(1, "ms->exit_status: %d\n", ms->exit_status);
	}
}

void	traverse_continue(t_node *cur, t_ms *ms, int fd_w[2], int action)
{
	if (cur->kind == ND_AND)
	{
		traverse(cur->left, ms, fd_w, action);
		ms->in_pipe = 0;
		if (!ms->exit_status && g_sig == 0)
			traverse(cur->right, ms, fd_w, action);
	}
	else if (cur->kind == ND_OR)
	{
		traverse(cur->left, ms, fd_w, action);
		ms->in_pipe = 0;
		if (ms->exit_status && g_sig == 0)
			traverse(cur->right, ms, fd_w, action);
	}
	else
		traverse_cmd(cur, ms, fd_w, action);
}

void	traverse(t_node *cur, t_ms *ms, int fd_w[2], int action)
{
	int		pipfd[2];

	if (cur->kind == ND_PIPE)
	{
		ms->in_pipe = 1;
		if (pipe(pipfd) == -1)
			error_exit("pip creation error");
		traverse(cur->left, ms, pipfd, action);
		if (g_sig == 0)
			traverse(cur->right, ms, fd_w, action);
	}
	else
		traverse_continue(cur, ms, fd_w, action);
}

void	traverse_start(t_node *head, t_ms *ms, int action)
{
	if (!head)
		return ;
	ms->in_pipe = 0;
	traverse(head, ms, 0, action);
}
