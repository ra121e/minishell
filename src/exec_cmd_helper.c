/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:33:50 by xlok              #+#    #+#             */
/*   Updated: 2024/11/19 18:01:08 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_envp(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->envp[i])
		i++;
	ms->cmd_envp = malloc(sizeof (char *) * (i + 1));
	if (ms->cmd_envp == NULL)
		return ;
	i = -1;
	while (ms->envp[++i])
		ms->cmd_envp[i] = ms->envp[i]->pair;
	ms->cmd_envp[i] = NULL;
}

void	close_fd(t_ms *ms)
{
	if (ms->fd_r > 2)
	{
		close(ms->fd_r);
		ms->fd_r = 0;
	}
	if (ms->fd_w[1] > 2)
	{
		close(ms->fd_w[1]);
		ms->fd_w[1] = 1;
	}
}

void	dup_fds(t_ms *ms)
{
	if (ms->fd_r > 2)
	{
		if (dup2(ms->fd_r, STDIN_FILENO) < 0)
			error_exit("dup2 error");
		close(ms->fd_r);
		ms->fd_r = 0;
	}
	if (ms->fd_w[0] > 2)
	{
		close(ms->fd_w[0]);
		ms->fd_w[0] = 0;
	}
	if (ms->fd_w[1] > 2)
	{
		if (dup2(ms->fd_w[1], STDOUT_FILENO) < 0)
			error_exit("dup2 error");
		close(ms->fd_w[1]);
		ms->fd_w[1] = 1;
	}
}
