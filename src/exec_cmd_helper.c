/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:41:57 by xlok              #+#    #+#             */
/*   Updated: 2024/10/29 21:03:37 by xlok             ###   ########.fr       */
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

void	init_cmd(t_ms *ms, t_node *cur, int fd_w[2])
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
	ms->cmd[0] = 0;
	ms->exit_status = 0;
	ms->cmd_error = 0;
	ms->builtin_cmd = 0;
	ms->cmd_node = cur;
	ms->cmd_node->fd_r = ms->fd_r;
	ms->cmd_node->fd_w[0] = fd_w[0];
	ms->cmd_node->fd_w[1] = fd_w[1];
}

int	*init_fd_w(t_ms *ms)
{
	ms->fd_w[0] = 0;
	ms->fd_w[1] = 1;
	return (ms->fd_w);
}

void	dup2_and_close(pid_t old_fd, pid_t new_fd)
{
	if (dup2(old_fd, new_fd) < 0)
		error_exit("dup2 error");
	close(old_fd);
}

int	get_filename_fd(char *str, pid_t fd, int mode)
{
	char	*filename;
	pid_t	file_fd;

	if (*str == '/')
		filename = ft_strdup(str);
	else
		filename = ft_strsjoin(3, getcwd(0, 0), "/", str);
	if (fd > 2)
		close(fd);
	if (mode == READ)
		file_fd = open(filename, mode);
	else
		file_fd = open(filename, mode, 0644);
	if (file_fd == -1)
		perror("minishell");
	free(filename);
	return (file_fd);
}
