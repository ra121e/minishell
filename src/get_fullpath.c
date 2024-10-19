/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fullpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:25:29 by athonda           #+#    #+#             */
/*   Updated: 2024/10/19 20:34:37 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_fullpath.c
 * @brief make an executable command
 * @param[in] cmd command name
 * @param[in] ms->cmd_envp environment variable as 3rd argument from command line
 * @return string of command with full path
 * @note file should be independent, reusable and limited
 * 	- file name: represent function is to get full path from environment
 * 	- file structure: process control function and brunch functions
 */

#include "minishell.h"

/**
 * @fn char	**find_ms->cmd_envpath
 * @brief find "PATH=" int the ms->cmd_envp, and cut by [:] into substring
 * @param[in] ms->cmd_envp
 * @return path double pointer to the address of string of path
 */

char	**find_envpath(t_ms *ms)
{
	char	*envpath;
	char	**path;
	int		i;

	i = 0;
	while (ms->cmd_envp[i])
	{
		if (ft_strncmp(ms->cmd_envp[i], "PATH=", 5) == 0)
		{
			envpath = ms->cmd_envp[i] + 5;
			break ;
		}
		i++;
	}
	if (ms->cmd_envp[i] == NULL)
		return (NULL);
	path = ft_split(envpath, ':');
	return (path);
}

/**
 * @fn char *join_cmd_path
 * @brief connect path and [/] and command name
 * @param[in] cmd command name
 * @param[in] path
 * @return string of full path
 */

char	*join_cmd_path(char *cmd, char *path)
{
	char	*dir;
	char	*fullpath;

	dir = ft_strjoin(path, "/");
	if (dir == NULL)
		return (NULL);
	fullpath = ft_strjoin(dir, cmd);
	free(dir);
	return (fullpath);
}

/**
 * @fn char *get_fullpath
 * @brief main process to make executable command
 * @param[in] cmd command name mostly comes from argv[1] or argv[2]
 * @param[in] ms->cmd_envp enviroment variable storing PATH
 * @return string of executable command with fullpath
 * @sa int	access(const char *pathname, int mode);
 * @note this function is controling process
 	- find_envpath: find "PATH=" in the string from ms->cmd_envp
 	- (loop) join_cmd_path: connect directory and command name
	- (loop) access: library function in unistd.h
 */

char	*get_fullpath(char *cmd, t_ms *ms)
{
	char	**path;
	char	*fullpath;
	int		i;

	path = find_envpath(ms);
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i])
	{
		fullpath = join_cmd_path(cmd, path[i]);
		if (access(fullpath, X_OK) == 0)
		{
			free_split(path);
			return (fullpath);
		}
		i++;
		free(fullpath);
	}
	free_split(path);
	return (NULL);
}
