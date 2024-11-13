/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:56 by athonda           #+#    #+#             */
/*   Updated: 2024/11/13 22:34:19 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin_in_child(t_ms *ms)
{
	if (ms->fd_r > 2)
		dup2_and_close(ms->fd_r, STDIN_FILENO);
	if (ms->fd_w[0] > 2)
		close(ms->fd_w[0]);
	if (ms->fd_w[1] > 2)
		dup2_and_close(ms->fd_w[1], STDOUT_FILENO);
	builtin(ms);
	exit(ms->exit_status);
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
	if (!ft_strlen(*ms->cmd))
	{
		ft_dprintf(2, "Command '' not found\n");
		exit(127);
	}
	execve(ms->cmd[0], ms->cmd, ms->cmd_envp);
	cmd_exe = get_fullpath(ms->cmd[0], ms);
	if (cmd_exe == NULL)
		error_wrong_cmd(ms);
	execve(cmd_exe, ms->cmd, ms->cmd_envp);
	perror(ms->cmd[0]);
	free(cmd_exe);
	exit(EXIT_FAILURE);
}

void	exec_parent_wait(t_ms *ms)
{
	int	status;

	status = 0;
	waitpid(ms->pid, &status, 0);
	while (1)
	{
		if (wait(0) == -1)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	if (WIFEXITED(status) && (!ms->builtin_cmd || ms->in_pipe))
		ms->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		ms->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == 2)
			ft_dprintf(2, "\n");
		else if (WTERMSIG(status) == 3)
			ft_dprintf(ms->fd_w[1], "Quit (core dumped)\n");
	}
}

void	fork_process(t_ms *ms)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("fork error!");
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
}
