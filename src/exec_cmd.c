/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:56 by athonda           #+#    #+#             */
/*   Updated: 2024/10/20 21:16:22 by athonda          ###   ########.fr       */
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
	ms->cmd = malloc(sizeof(char *) * i + 1);
	if (!ms->cmd)
		perror("");//malloc error
}

int	execute(t_ms *ms, int fd_r, int fd_w[2])
{
	pid_t	pid;
	int		wstatus;
	char	*cmd_exe;

	(void)fd_r;
	(void)fd_w;
	cmd_envp(ms);
	if (is_builtin(ms->cmd[0]) == true)
	{
		printf("built in command: %s\n", ms->cmd[0]);
		return (0);
	}
	pid = fork();
	if (pid < 0)
		error_exit("fork error!");
	else if (pid == 0)
	{
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
//	if (fd_r)
//	{
//		close(fd_r[0]);
//		close(fd_r[1]);
//	}
	waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}

int	exec_cmd(t_node *cur, t_ms *ms, int fd_r, int fd_w[2])
{
	char	*file_name;
	int		i;

	while (cur->kind)
	{
		if (cur->kind == ND_REDIRECT_IN || \
			cur->kind == ND_REDIRECT_OUT || \
			cur->kind == ND_REDIRECT_HEREDOC || \
			cur->kind == ND_REDIRECT_APPEND)
		{
			if (cur->right->kind == ND_COMMAND)
			{
				file_name = malloc(1024);
//						getcwd(file_name, 1024);
				file_name = ft_strjoin(getcwd(file_name, 1024), "/");
				file_name = ft_strjoin(file_name, cur->right->str);
				dprintf(1, "redirect out file name is %s\n", file_name);
				if (fd_w[1] != 0)
					close(fd_w[1]);
				fd_w[1] = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				dprintf(1, "fd_w[1]: %d\n", fd_w[1]);
//				close(fd_r); cur = cur->right;
			}
		}
		else
		{
			//if (check_cmd == 0)
			//{
			//	dprintf(2, "needs command\n");
			//	return (NULL);
			//}
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
					{
						file_name = malloc(1024);
//						getcwd(file_name, 1024);
						file_name = ft_strjoin(getcwd(file_name, 1024), "/");
						file_name = ft_strjoin(file_name, cur->right->str);
						dprintf(1, "redirect file name is %s\n", file_name);
						if (fd_w[1] != 0)
							close(fd_w[1]);
						fd_w[1] = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
						dprintf(1, "fd_w[1]: %d\n", fd_w[1]);
//						close(fd_w[1]);
						cur = cur->right;
					}
				}
				else
				{
					ms->cmd[i++] = cur->str;
				}
				cur = cur->right;
			}
			ms->cmd[i] = NULL;
			if (dup2(fd_w[1], STDOUT_FILENO) < 0)
				error_exit("dup2 write end error");
			close(fd_w[1]);
			if (fd_r > 2)
			{
				if (dup2(fd_r, STDIN_FILENO) < 0)
					error_exit("dup2 error");
				close(fd_r);
			}
//			dprintf(2, "fd_r: %d\n\n", fd_r);
//			dprintf(2, "fd_w[1]: %d\n\n", fd_w[1]);
			break ;
		}
		cur = cur->right;
	}
	execute(ms, fd_r, fd_w);
	return (fd_w[0]);
}
