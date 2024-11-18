/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_relative_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:00:29 by xlok              #+#    #+#             */
/*   Updated: 2024/11/18 08:12:02 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_parent_dir(char *str, int i)
{
	if (!i || str[i - 1] == '/')
	{
		if (str[i] == '.' && str[i + 1] == '.' && !str[i + 2])
			return (2);
		else if (str[i] == '.' && str[i + 1] == '.' && str[i + 2] == '/')
			return (3);
	}
	return (0);
}

int	is_current_dir(char *str, int i)
{
	if (!i || str[i - 1] == '/')
	{
		if (str[i] == '.' && !str[i + 1])
			return (1);
		else if (str[i] == '.' && str[i + 1] == '/')
			return (2);
	}
	return (0);
}

char	*update_path(t_ms *ms, char *path, char *str)
{
	char	*tmp;

	tmp = path;
	if (!ft_strncmp(str, "..", 3))
	{
		if (ft_strlen(path) == ft_strlen(ft_strrchr(path, '/')))
			path = ft_strdup("/");
		else
			path = ft_substr(path, 0, \
				ft_strlen(path) - ft_strlen(ft_strrchr(path, '/')));
		if (!path)
			error_malloc(ms, "relative path malloc error");
	}
	else
	{
		if (!ft_strncmp(path, "/", 2))
			path = ft_strjoin(path, str);
		else
			path = ft_strsjoin(3, path, "/", str);
		if (!path)
			error_malloc(ms, "relative path malloc error");
	}
	free(tmp);
	return (path);
}

char	*get_relative_path(t_ms *ms, char *str)
{
	char	*path;
	char	*dir;
	char	*tmp;
	int		i;
	int		s;

	if (*str == '/')
		path = ft_strdup("/");
	else if (is_parent_dir(str, 0) || is_current_dir(str, 0))
		path = getcwd(0, 0);
	if (!path)
		error_malloc(ms, "relative path malloc error");
	s = 0;
	i = 0;
	if (*str == '/')
		s = ++i;
	while (str[i])
	{
		if (is_parent_dir(str, i))
		{
			path = update_path(ms, path, "..");
			i += is_parent_dir(str, i);
			s = i;
		}
		else if (is_current_dir(str, i))
		{
			i += is_current_dir(str, i);
			s = i;
		}
		else if (str[i] == '/')
		{
			dir = ft_substr(str, s, i - s);
			if (!dir)
				error_malloc(ms, "relative path malloc error");
			if (*dir)
				path = update_path(ms, path, dir);
			else
			{
				ft_dprintf(2, "%s: cannot access '%s'\n", *ms->cmd, str);
				ms->error = 1;
				ms->exit_status = 2;
				free(dir);
				break ;
			}
			free(dir);
			s = ++i;
		}
		else
			i++;
	}
	if (ms->error)
		return (free(path), NULL);
	tmp = path;
	if (!ft_strncmp(path, "/", 2))
		path = ft_strdup(ft_strrchr(str, '/'));
	else
		path = ft_strjoin(path, ft_strrchr(str, '/'));
	free(tmp);
	return (path);
}
