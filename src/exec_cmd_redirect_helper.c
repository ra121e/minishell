/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_redirect_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:41:57 by xlok              #+#    #+#             */
/*   Updated: 2024/11/03 21:32:37 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_ms *ms)
{
	ms->cmd = 0;
	ms->i = 0;
	ms->cmd_error = 0;
	ms->builtin_cmd = 0;
	ms->fd_r = 0;
}

int	*init_fd_w(t_ms *ms)
{
	ms->fd_w[0] = 0;
	ms->fd_w[1] = 1;
	return (ms->fd_w);
}

static void	add_cmd_arg2(t_ms *ms, int i)
{
	char	**tmp;
	int		j;

	tmp = ms->cmd;
	ms->cmd = malloc(sizeof(char *) * (i + 2));
	if (!ms->cmd)
		perror("malloc error for ms->cmd");
	j = -1;
	while (++j < i)
		ms->cmd[j] = tmp[j];
	ms->cmd[j++] = ms->new_str;
	ms->cmd[j] = 0;
	free(tmp);
}

void	add_cmd_arg(t_ms *ms, char *str, int s, int i)
{
	ms->new_str = ft_substr(str, s, i - s);
	ms->old_str = ms->new_str;
	ms->new_str = remove_quote(ms->old_str);
	add_cmd_arg2(ms, ms->i++);
	free(ms->old_str);
	ms->old_str = 0;
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
