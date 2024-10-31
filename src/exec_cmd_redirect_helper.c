/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_redirect_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:41:57 by xlok              #+#    #+#             */
/*   Updated: 2024/11/01 22:03:19 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_ms *ms, t_node *cur)
{
	t_node	*tmp;
	int		i;

	tmp = cur;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->right;
	}
	ms->cmd = malloc(sizeof(char *) * (i + 1));
	if (!ms->cmd)
		perror("ms->cmd malloc error");//malloc error
	ms->cmd[0] = 0;
	ms->exit_status = 0;
	ms->cmd_error = 0;
	ms->builtin_cmd = 0;
}

int	*init_fd_w(t_ms *ms)
{
	ms->fd_w[0] = 0;
	ms->fd_w[1] = 1;
	return (ms->fd_w);
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
