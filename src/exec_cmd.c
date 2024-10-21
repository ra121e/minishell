/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:56 by athonda           #+#    #+#             */
/*   Updated: 2024/10/21 23:25:45 by xlok             ###   ########.fr       */
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
		printf("built in command: %s\nfunction WIP\n", ms->cmd[0]);
		return ;
	}
	pid = fork();
	if (pid < 0)
		error_exit("fork error!");
	ms->pid = pid;
	if (pid == 0)
		execute_child(ms, fd_w);
	if (ms->fd_r > 2)
		close(ms->fd_r);
	if (fd_w[1] > 2)
		close(fd_w[1]);
	ms->fd_r = fd_w[0];
}

void	node_after_redirect_is_cmd(t_ms *ms, t_node **cur, int fd_w[2])
{
	char	*file_name;
	int		kind;

	kind = (*cur)->kind;
	*cur = (*cur)->right;
	file_name = ft_strsjoin(3, getcwd(0, 0), "/", (*cur)->str);
	dprintf(1, "redirect file name is %s\n", file_name);
	if (kind == ND_REDIRECT_IN)
	{
		if (ms->fd_r > 2)
			close(ms->fd_r);
		ms->fd_r = open(file_name, O_RDONLY, 0644);
//TODO:	supposed to print error ": No such file or directory" if file doesn't exist
		dprintf(1, "ms->fd_r: %d\n", ms->fd_r);
	}
	else if (kind == ND_REDIRECT_OUT || kind == ND_REDIRECT_APPEND)
	{
		if (fd_w && fd_w[1] > 2)
			close(fd_w[1]);
		if (fd_w)
		{
			if (kind == ND_REDIRECT_OUT)
				fd_w[1] = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd_w[1] = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		dprintf(1, "fd_w[1]: %d\n", fd_w[1]);
	}
	free(file_name);
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
				node_after_redirect_is_cmd(ms, &cur, fd_w);
		}
		else
			ms->cmd[i++] = cur->str;
		cur = cur->right;
	}
	ms->cmd[i] = NULL;
}

void	exec_cmd(t_node *cur, t_ms *ms, int fd_w[2])
{
	if (!fd_w)
	{
		fd_w = malloc(sizeof(int) * 2);
		fd_w[0] = 0;
		fd_w[1] = 1;
	}
	while (cur->kind)
	{
		if (cur->kind > 100)
		{
			if (cur->right->kind == ND_COMMAND)
				node_after_redirect_is_cmd(ms, &cur, fd_w);
		}
		else
		{
			cmd_found(ms, cur, fd_w);
			break ;
		}
		cur = cur->right;
	}
	execute(ms, fd_w);
}
