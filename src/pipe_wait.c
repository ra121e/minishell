/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:19:51 by xlok              #+#    #+#             */
/*   Updated: 2024/11/21 21:36:11 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all_child(void)
{
	int	status_b;

	status_b = 0;
	while (1)
	{
		if (wait(&status_b) == -1)
		{
			if (errno == ECHILD)
				break ;
		}
		if (WIFSIGNALED(status_b) && WTERMSIG(status_b) == 2)
			g_sig = WTERMSIG(status_b);
	}
}

void	pipe_wait(t_ms *ms)
{
	int	status;

	status = 0;
	waitpid(ms->pid, &status, 0);
	wait_all_child();
	if (WIFEXITED(status) && (!ms->builtin_cmd || ms->in_pipe))
		ms->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_sig = WTERMSIG(status);
		ms->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == 2)
			ft_dprintf(2, "\n");
		else if (WTERMSIG(status) == 3)
			ft_dprintf(2, "Quit (core dumped)\n");
	}
	ms->forked = 0;
}
