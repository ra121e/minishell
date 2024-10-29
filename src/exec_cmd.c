/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:56 by athonda           #+#    #+#             */
/*   Updated: 2024/10/29 18:10:05 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_ms *ms, int fd_w[2])
{
	char	*cmd_exe;

	if (ms->fd_r > 2)
		dup2_and_close(ms->fd_r, STDIN_FILENO);
	if (fd_w[0] > 2)
		close(fd_w[0]);
	if (fd_w[1] > 2)
		dup2_and_close(fd_w[1], STDOUT_FILENO);
	execve(ms->cmd[0], ms->cmd, ms->cmd_envp);
	cmd_exe = get_fullpath(ms->cmd[0], ms);
	if (cmd_exe == NULL)
		error_wrong_cmd(ms);
	execve(cmd_exe, ms->cmd, ms->cmd_envp);
	perror(ms->cmd[0]);
	free(cmd_exe);
	free(ms->cmd);
	exit(EXIT_FAILURE);
}

void	exec_cmd(t_ms *ms, int fd_w[2])
{
	pid_t	pid;

	cmd_envp(ms);
	if (is_builtin(ms->cmd[0]) == true)
	{
		ms->builtin_cmd = 1;
		builtin(ms);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			error_exit("fork error!");
		ms->pid = pid;
		ft_signal_cmd();
		if (pid == 0)
			execute_child(ms, fd_w);
	}
	if (ms->fd_r > 2)
		close(ms->fd_r);
	if (fd_w[1] > 2)
		close(fd_w[1]);
	ms->fd_r = fd_w[0];
	free(ms->cmd);
}
