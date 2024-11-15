/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:16:22 by athonda           #+#    #+#             */
/*   Updated: 2024/11/15 10:35:16 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	traverse_cmd(t_node *cur, t_ms *ms, int fd_w[2])
{
	redirection(ms, cur, fd_w);
	if (!g_sig && !ms->error)
	{
		if (ms->cmd && ms->cmd[0])
			exec_cmd(ms);
		else
		{
			close_fd(ms);
			ms->fd_r = ms->fd_w[0];
		}
	}
}

void	traverse(t_node *cur, t_ms *ms, int fd_w[2])
{
	int		pipfd[2];

	if (cur->kind == ND_PIPE)
	{
		if (pipe(pipfd) == -1)
			error_exit("pip creation error");
		ms->in_pipe = 1;
		traverse(cur->left, ms, pipfd);
		if (g_sig == 0)
			traverse(cur->right, ms, fd_w);
	}
	else if (cur->kind == ND_AND || cur->kind == ND_OR)
	{
		traverse(cur->left, ms, fd_w);
		if (ms->forked)
			pipe_wait(ms);
		ms->in_pipe = 0;
		if (cur->kind == ND_AND && (!ms->exit_status && g_sig == 0))
			traverse(cur->right, ms, fd_w);
		else if (cur->kind == ND_OR && (ms->exit_status && g_sig == 0))
			traverse(cur->right, ms, fd_w);
	}
	else
		traverse_cmd(cur, ms, fd_w);
}

void	traverse_start(t_node *head, t_ms *ms)
{
	if (!head || head->error == true || ms->error)
		return ;
	ms->in_pipe = 0;
	ms->forked = 0;
	traverse(head, ms, 0);
	if (ms->forked)
		pipe_wait(ms);
}
