/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_redirect_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:41:57 by xlok              #+#    #+#             */
/*   Updated: 2024/11/18 23:15:06 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_ms *ms)
{
	ms->cmd = 0;
	ms->i = 0;
	ms->builtin_cmd = 0;
}

int	*init_fd_w(t_ms *ms)
{
	ms->fd_w[0] = 0;
	ms->fd_w[1] = 1;
	return (ms->fd_w);
}

static void	add_cmd_arg2(t_ms *ms, char *new_str)
{
	char	**tmp;
	int		i;

	tmp = ms->cmd;
	i = 0;
	while (tmp && tmp[i])
		i++;
	ms->cmd = malloc(sizeof(char *) * (i + 2));
	if (!ms->cmd)
		error_malloc(ms, "malloc error for ms->cmd");
	i = 0;
	while (tmp && tmp[i])
	{
		ms->cmd[i] = tmp[i];
		i++;
	}
	ms->cmd[i++] = new_str;
	ms->cmd[i] = 0;
	free(tmp);
}

void	add_cmd_arg(t_ms *ms, char *str, int s, int i)
{
	char	*new_str;

	new_str = ft_substr(str, s, i - s);
	if (!new_str)
	{
		error_malloc(ms, "add_cmd_arg malloc error");
		free_str(ms->new_str);
		cleanup(ms);
		cleanup_final(ms);
		exit(EXIT_FAILURE);
	}
	add_cmd_arg2(ms, new_str);
}

int	get_filename_fd(t_ms *ms, char *str, pid_t fd, int mode)
{
	char	*filename;
	pid_t	file_fd;

	file_fd = -1;
	filename = get_relative_path(ms, str);
	if (fd > 2)
		close(fd);
	if (mode == READ && !access(filename, R_OK))
		file_fd = open(filename, mode);
	else if (mode != READ && \
			!(!access(filename, F_OK) && access(filename, W_OK)))
		file_fd = open(filename, mode, 0644);
	if (file_fd == -1)
		error_filename(ms, str);
	free(filename);
	return (file_fd);
}
