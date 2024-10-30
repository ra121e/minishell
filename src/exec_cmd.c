/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:56 by athonda           #+#    #+#             */
/*   Updated: 2024/10/30 08:33:12 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_ms *ms, t_node *cur)
{
	char	*cmd_exe;

	if (cur->fd_r > 2)
		dup2_and_close(cur->fd_r, STDIN_FILENO);
	if (cur->fd_w[0] > 2)
		close(cur->fd_w[0]);
	if (cur->fd_w[1] > 2)
		dup2_and_close(cur->fd_w[1], STDOUT_FILENO);
	execve(cur->cmd[0], cur->cmd, ms->cmd_envp);
	cmd_exe = get_fullpath(cur->cmd[0], ms);
	if (cmd_exe == NULL)
		error_wrong_cmd(ms);
	execve(cmd_exe, cur->cmd, ms->cmd_envp);
	perror(cur->cmd[0]);
	free(cmd_exe);
	free_cmd(cur);
	free_cmd_envp(ms->cmd_envp);
	exit(EXIT_FAILURE);
}

void	exec_parent_wait(t_ms *ms)
{
	int	status;

	if (ms->sig == 2)
	{
		ms->exit_status = 130;
		return ;
	}
	waitpid(ms->pid, &status, 0);
	while (1)
	{
		if (wait(0) == -1)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	ft_signal();
	if (ms->cmd_error)
		ms->exit_status = 1;
	else if (!ms->builtin_cmd)
		ms->exit_status = WEXITSTATUS(status);
}

void	exec_cmd(t_ms *ms, t_node *cur)
{
	pid_t	pid;

	cmd_envp(ms);
	if (is_builtin(cur->cmd[0]) == true)
	{
		ms->builtin_cmd = 1;
		builtin(ms, cur);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			error_exit("fork error!");
		ms->pid = pid;
		ft_signal_cmd();
		if (pid == 0)
			exec_child(ms, cur);
	}
	close_fd(cur);
	free_cmd(cur);
	exec_parent_wait(ms);
}
