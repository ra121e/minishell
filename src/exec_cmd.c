/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:56 by athonda           #+#    #+#             */
/*   Updated: 2024/10/24 07:39:48 by xlok             ###   ########.fr       */
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

void	execute(t_ms *ms, int fd_w[2])
{
	pid_t	pid;

	cmd_envp(ms);
	if (is_builtin(ms->cmd[0]) == true)
	{
		ms->builtin_cmd = 1;
		builtin(ms);
//		printf("built in command: %s\nfunction WIP\n", ms->cmd[0]);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			error_exit("fork error!");
		ms->pid = pid;
		if (pid == 0)
			execute_child(ms, fd_w);
	}
	if (ms->fd_r > 2)
		close(ms->fd_r);
	if (fd_w[1] > 2)
		close(fd_w[1]);
	ms->fd_r = fd_w[0];
}

void	redirect(t_ms *ms, t_node **cur, int fd_w[2])
{
	int		kind;

	kind = (*cur)->kind;
	*cur = (*cur)->right;
	if (kind == ND_REDIRECT_IN)
		ms->fd_r = get_filename_fd(ms, (*cur)->str, ms->fd_r, READ);
	else if (kind == ND_REDIRECT_OUT || kind == ND_REDIRECT_APPEND)
	{
		if (fd_w)
		{
			if (kind == ND_REDIRECT_OUT)
				fd_w[1] = get_filename_fd(ms, (*cur)->str, fd_w[1], WRITE);
			else
				fd_w[1] = get_filename_fd(ms, (*cur)->str, fd_w[1], APPEND);
		}
	}
}

void	cmd_found(t_ms *ms, t_node *cur, int fd_w[2])
{
	int		i;

	init_cmd(ms, cur);
	ms->cmd[0] = cur->str;
	cur = cur->right;
	i = 1;
	while (cur != NULL)
	{
		if (cur->kind > 100)
		{
			if (cur->right->kind == ND_COMMAND)
				redirect(ms, &cur, fd_w);
			if (ms->cmd_error)
				return ;
		}
		else
			ms->cmd[i++] = cur->str;
		cur = cur->right;
	}
	ms->cmd[i] = NULL;
}

void	exec_cmd(t_node *cur, t_ms *ms, int fd_w[2])
{
	ms->cmd_error = 0;
	ms->builtin_cmd = 0;
	ms->fd_w_malloc = 0;
	if (!fd_w)
		fd_w = init_fd_w(ms);
	while (cur->kind)
	{
		if (cur->kind > 100)
		{
			if (cur->right->kind == ND_COMMAND)
				redirect(ms, &cur, fd_w);
			if (ms->cmd_error)
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
	execute(ms, fd_w);
//TODO:	free ms->cmd, ms->fd_w (if malloced)
	if (ms->fd_w_malloc)
		free(ms->fd_w);
}
