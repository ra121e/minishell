/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:56 by athonda           #+#    #+#             */
/*   Updated: 2024/10/21 18:52:32 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_ms *ms, t_node *cur)
{
	int	i;

	i = 0;
	while (cur)
	{
		i++;
		cur = cur->right;
	}
	ms->cmd = malloc(sizeof(char *) * (i + 1));
	if (!ms->cmd)
		perror("ms->cmd malloc error");//malloc error
}

int	execute(t_ms *ms, int fd_w[2])
{
	pid_t	pid;
	char	*cmd_exe;

	cmd_envp(ms);
	if (is_builtin(ms->cmd[0]) == true)
	{
		printf("built in command: %s\n", ms->cmd[0]);
		return (0);
	}
	pid = fork();
	if (pid < 0)
		error_exit("fork error!");
	ms->pid = pid;
	if (pid == 0)
	{
		if (ms->fd_r > 2)
		{
			if (dup2(ms->fd_r, STDIN_FILENO) < 0)
				error_exit("dup2 error");
			close(ms->fd_r);
		}
		if (fd_w[0] > 2)
			close(fd_w[0]);
		if (fd_w[1] > 2)
		{
			if (dup2(fd_w[1], STDOUT_FILENO) < 0)
				error_exit("dup2 write end error");
			close(fd_w[1]);
		}
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
	if (ms->fd_r > 2)
		close(ms->fd_r);
	if (fd_w[1] > 2)
		close(fd_w[1]);
	ms->fd_r = fd_w[0];
	return (0);
}

void	node_after_redirect_is_cmd(t_node **cur, int fd_w[2])
{
	char	*file_name;

	file_name = malloc(1024);
	file_name = ft_strsjoin(3, getcwd(file_name, 1024), "/", (*cur)->right->str);
	dprintf(1, "redirect file name is %s\n", file_name);
	if (fd_w && fd_w[1] > 2)
		close(fd_w[1]);
	if (fd_w)
		fd_w[1] = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dprintf(1, "fd_w[1]: %d\n", fd_w[1]);
	*cur = (*cur)->right;
}

int	exec_cmd(t_node *cur, t_ms *ms, int fd_w[2])
{
	int		i;

	if (!fd_w)
	{
		fd_w = malloc(sizeof(int) * 2);
		fd_w[0] = 0;
		fd_w[1] = 1;
	}
	while (cur->kind)
	{
		if (cur->kind == ND_REDIRECT_IN || \
			cur->kind == ND_REDIRECT_OUT || \
			cur->kind == ND_REDIRECT_HEREDOC || \
			cur->kind == ND_REDIRECT_APPEND)
		{
			if (cur->right->kind == ND_COMMAND)
				node_after_redirect_is_cmd(&cur, fd_w);
		}
		else
		{
			init_cmd(ms, cur);
			ms->cmd[0] = cur->str;
			cur = cur->right;
			i = 1;
			while (cur != NULL)
			{
				if (cur->kind == ND_REDIRECT_IN || \
					cur->kind == ND_REDIRECT_OUT || \
					cur->kind == ND_REDIRECT_HEREDOC ||
					cur->kind == ND_REDIRECT_APPEND)
				{
					if (cur->right->kind == ND_COMMAND)
						node_after_redirect_is_cmd(&cur, fd_w);
				}
				else
					ms->cmd[i++] = cur->str;
				cur = cur->right;
			}
			ms->cmd[i] = NULL;
			break ;
		}
		cur = cur->right;
	}
	return (execute(ms, fd_w));
}
