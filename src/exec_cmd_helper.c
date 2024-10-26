/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:41:57 by xlok              #+#    #+#             */
/*   Updated: 2024/10/26 20:24:07 by athonda          ###   ########.fr       */
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
	ms->cmd[0] = 0;
	ms->cmd_error = 0;
	ms->builtin_cmd = 0;
	ms->fd_w_malloc = 0;
}

int	*init_fd_w(t_ms *ms)
{
	ms->fd_w = malloc(sizeof(int) * 2);
	ms->fd_w[0] = 0;
	ms->fd_w[1] = 1;
	ms->fd_w_malloc = 1;
	return (ms->fd_w);
}

void	dup2_and_close(pid_t old_fd, pid_t new_fd)
{
	if (dup2(old_fd, new_fd) < 0)
		error_exit("dup2 error");
	close(old_fd);
}

pid_t	get_filename_fd(t_ms *ms, char *str, pid_t fd, int mode)
{
	char	*filename;
	pid_t	file_fd;

	if (*str == '/')
		filename = ft_strdup(str);
	else
		filename = ft_strsjoin(3, getcwd(0, 0), "/", str);
	if (fd > 2)
		close(fd);
	file_fd = open(filename, mode, 0644);
	if (file_fd == -1)
	{
		perror("minishell");
		ms->cmd_error = 1;
		if (ms->fd_w_malloc)
			free(ms->fd_w);
	}
	free(filename);
	return (file_fd);
}
