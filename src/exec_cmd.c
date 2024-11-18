/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:56 by athonda           #+#    #+#             */
/*   Updated: 2024/11/18 00:12:33 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin_in_child(t_ms *ms)
{
	int	exit_status;

	if (ms->fd_r > 2)
		dup2_and_close(ms->fd_r, STDIN_FILENO);
	if (ms->fd_w[0] > 2)
		close(ms->fd_w[0]);
	if (ms->fd_w[1] > 2)
		dup2_and_close(ms->fd_w[1], STDOUT_FILENO);
	builtin(ms);
	exit_status = ms->exit_status;
	clean_cmd_before_exit(ms, exit_status);
}

void	exec_child(t_ms *ms)
{
	char	*cmd_exe;

	if (ms->fd_r > 2)
		dup2_and_close(ms->fd_r, STDIN_FILENO);
	if (ms->fd_w[0] > 2)
		close(ms->fd_w[0]);
	if (ms->fd_w[1] > 2)
		dup2_and_close(ms->fd_w[1], STDOUT_FILENO);
	if (ms->error)
		clean_cmd_before_exit(ms, 1);
	if (!ft_strlen(*ms->cmd) && !ms->cmd[1])
	{
		ft_dprintf(2, "Command '' not found\n");
		exit(127);
	}
	if (ms->cmd[0][0] == '/' || (ms->cmd[0][0] == '.' && ms->cmd[0][1] == '/'))
		cmd_exe = check_relative_path(ms, ms->cmd[0]);
	else
		cmd_exe = get_fullpath(ms->cmd[0], ms);
	if (!cmd_exe)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", ms->cmd[0]);
		clean_cmd_before_exit(ms, 127);
	}
	execve(cmd_exe, ms->cmd, ms->cmd_envp);
	free(cmd_exe);
	clean_cmd_before_exit(ms, 0);
}

void	fork_process(t_ms *ms)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("fork error!");
	ms->forked = 1;
	ms->pid = pid;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (ms->builtin_cmd && ms->in_pipe)
			exec_builtin_in_child(ms);
		else
			exec_child(ms);
	}
	signal(SIGINT, SIG_IGN);
}

void	exec_cmd(t_ms *ms)
{
	cmd_envp(ms);
	if (is_builtin(ms->cmd[0]) == true)
	{
		ms->builtin_cmd = 1;
		if (ms->in_pipe)
			fork_process(ms);
		else
			builtin(ms);
	}
	else
		fork_process(ms);
	close_fd(ms);
	ms->fd_r = ms->fd_w[0];
	free(ms->cmd_envp);
	free_str_array(ms->cmd);
	ms->cmd = 0;
}
