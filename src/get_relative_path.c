/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_relative_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:00:29 by xlok              #+#    #+#             */
/*   Updated: 2024/11/19 21:54:53 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_path(t_ms *ms, char *str)
{
	char	*tmp;

	tmp = ms->rpath;
	if (!ft_strncmp(str, "..", 3))
	{
		if (ft_strlen(ms->rpath) == ft_strlen(ft_strrchr(ms->rpath, '/')))
			ms->rpath = ft_strdup("/");
		else
			ms->rpath = ft_substr(ms->rpath, 0, \
				ft_strlen(ms->rpath) - ft_strlen(ft_strrchr(ms->rpath, '/')));
		if (!ms->rpath)
			error_malloc(ms, "relative path malloc error");
	}
	else
	{
		if (!ft_strncmp(ms->rpath, "/", 2))
			ms->rpath = ft_strjoin(ms->rpath, str);
		else
			ms->rpath = ft_strsjoin(3, ms->rpath, "/", str);
		if (!ms->rpath)
			error_malloc(ms, "relative path malloc error");
	}
	free(tmp);
	is_path_valid(ms, ms->rpath, str);
}

void	parent_or_current_dir(t_ms *ms, char *str)
{
	if (!ft_strncmp(str + ms->i, "..", 3))
	{
		update_path(ms, "..");
		ms->i += 2;
	}
	else if (!ft_strncmp(str + ms->i, "../", 4))
	{
		update_path(ms, "..");
		ms->i += 3;
	}
	else if (!ft_strncmp(str + ms->i, ".", 2))
		ms->i += 1;
	else if (!ft_strncmp(str + ms->i, "./", 3))
		ms->i += 2;
	ms->start = ms->i;
}

void	add_dir(t_ms *ms, char *str)
{
	char	*tmp;

	tmp = ft_substr(str, ms->start, ms->i - ms->start);
	if (!tmp)
		error_malloc(ms, "relative path malloc error");
	if (*tmp)
		update_path(ms, tmp);
	else
	{
		ft_dprintf(2, "%s: cannot access '%s'\n", *ms->cmd, str);
		ms->error = 1;
		ms->exit_status = 2;
		free(tmp);
	}
	free(tmp);
	ms->start = ++ms->i;
}

void	final_path(t_ms *ms, char *str)
{
	char	*tmp;

	tmp = ms->rpath;
	if (!ft_strncmp(ms->rpath, "/", 2) && ft_strrchr(str, '/'))
		ms->rpath = ft_strjoin(ms->rpath, ft_strrchr(str, '/') + 1);
	else if (ft_strncmp(ms->rpath, "/", 2) && ft_strrchr(str, '/'))
		ms->rpath = ft_strjoin(ms->rpath, ft_strrchr(str, '/'));
	else if (!ft_strncmp(ms->rpath, "/", 2) && !ft_strrchr(str, '/'))
		ms->rpath = ft_strjoin(ms->rpath, str);
	else if (ft_strncmp(ms->rpath, "/", 2) && !ft_strrchr(str, '/'))
		ms->rpath = ft_strsjoin(3, ms->rpath, "/", str);
	free(tmp);
}

char	*get_relative_path(t_ms *ms, char *str)
{
	if (*str == '/')
		ms->rpath = ft_strdup("/");
	else
		ms->rpath = getcwd(0, 0);
	if (!ms->rpath)
		error_malloc(ms, "relative path malloc error");
	ms->start = 0;
	ms->i = 0;
	if (*str == '/')
		ms->start = ++ms->i;
	while (str[ms->i])
	{
		if (!ms->i || str[ms->i - 1] == '/')
			parent_or_current_dir(ms, str);
		else if (str[ms->i] == '/')
			add_dir(ms, str);
		ms->i++;
		if (ms->error)
			return (free(ms->rpath), NULL);
	}
	final_path(ms, str);
	return (ms->rpath);
}
