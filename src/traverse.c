/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:16:22 by athonda           #+#    #+#             */
/*   Updated: 2024/10/24 21:21:07 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	traverse_cmd(t_node *cur, t_ms *ms, int fd_w[2])
{
	int	status;

	expansion(ms, cur);
	exec_cmd(cur, ms, fd_w);
	waitpid(ms->pid, &status, 0);
	while (1)
	{
		if (wait(0) == -1)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	if (ms->cmd_error)
		ms->exit_status = 1;
	else if (!ms->builtin_cmd)
		ms->exit_status = WEXITSTATUS(status);
}

void	traverse(t_node *cur, t_ms *ms, int fd_w[2])
{
	int		pipfd[2];

	if (cur->kind == ND_PIPE)
	{
		if (pipe(pipfd) == -1)
			error_exit("pip creation error");
		traverse(cur->left, ms, pipfd);
		traverse(cur->right, ms, fd_w);
	}
	else if (cur->kind == ND_AND)
	{
		traverse(cur->left, ms, fd_w);
		if (!ms->exit_status)
			traverse(cur->right, ms, fd_w);
	}
	else if (cur->kind == ND_OR)
	{
		traverse(cur->left, ms, fd_w);
		if (ms->exit_status)
			traverse(cur->right, ms, fd_w);
	}
	else
		traverse_cmd(cur, ms, fd_w);
}

void	traverse_start(t_node *head, t_ms *ms)
{
	if (!head)
		return ;
	traverse(head, ms, 0);
}
