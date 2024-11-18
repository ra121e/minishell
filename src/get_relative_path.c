/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_relative_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:00:29 by xlok              #+#    #+#             */
/*   Updated: 2024/11/19 00:15:11 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_parent_or_current_dir(t_ms *ms, char *path, char *str, int i)
{
	if (!i || str[i - 1] == '/')
	{
		if (str[i] == '.' && str[i + 1] == '.' && !str[i + 2])
		{
			path = update_path(ms, path, "..");
			return (2);
		}
		else if (str[i] == '.' && str[i + 1] == '.' && str[i + 2] == '/')
		{
			path = update_path(ms, path, "..");
			return (3);
		}
		else if (str[i] == '.' && !str[i + 1])
			return (1);
		else if (str[i] == '.' && str[i + 1] == '/')
			return (2);
	}
	return (0);
}

char	*get_relative_path(t_ms *ms, char *str)
{
	char	*path;
	char	*tmp;
	int		i;
	int		s;

	if (*str == '/')
		path = ft_strdup("/");
	else
		path = getcwd(0, 0);
	if (!path)
		error_malloc(ms, "relative path malloc error");
	s = 0;
	i = 0;
	if (*str == '/')
		s = ++i;
	while (str[i])
	{
		if (is_parent_or_current_dir(ms, path, str, i))
		{
			i += is_parent_or_current_dir(ms, path, str, i);
			s = i;
		}
		else if (str[i] == '/')
		{
			tmp = ft_substr(str, s, i - s);
			if (!tmp)
				error_malloc(ms, "relative path malloc error");
			if (*tmp)
				path = update_path(ms, path, tmp);
			else
			{
				ft_dprintf(2, "%s: cannot access '%s'\n", *ms->cmd, str);
				ms->error = 1;
				ms->exit_status = 2;
				free(tmp);
				break ;
			}
			free(tmp);
			s = ++i;
		}
		else
			i++;
	}
	if (ms->error)
		return (free(path), NULL);
	tmp = path;
	if (!ft_strncmp(path, "/", 2) && ft_strrchr(str, '/'))
		path = ft_strjoin(path, ft_strrchr(str, '/') + 1);
	else if (ft_strncmp(path, "/", 2) && ft_strrchr(str, '/'))
		path = ft_strjoin(path, ft_strrchr(str, '/'));
	else if (!ft_strncmp(path, "/", 2) && !ft_strrchr(str, '/'))
		path = ft_strjoin(path, str);
	else if (ft_strncmp(path, "/", 2) && !ft_strrchr(str, '/'))
		path = ft_strsjoin(3, path, "/", str);
	free(tmp);
	return (path);
}
