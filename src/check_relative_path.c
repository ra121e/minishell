/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_relative_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:33:32 by xlok              #+#    #+#             */
/*   Updated: 2024/11/18 22:12:15 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_relative_path(t_ms *ms, char *path)
{
	struct stat	sb;
	char		*res;

	sb.st_mode = 0;
	stat(path, &sb);
	if (S_ISDIR(sb.st_mode))
	{
		ft_dprintf(2, "minishell: %s is a directory\n", path);
		clean_cmd_before_exit(ms, 126);
	}
	else if (!access(path, F_OK) && access(path, X_OK))
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", path);
		clean_cmd_before_exit(ms, 126);
	}
	else if (!access(path, F_OK) && !access(path, X_OK))
	{
		res = ft_strdup(path);
		if (!res)
			error_malloc(ms, "check relative path malloc error");
		return (res);
	}
	return (0);
}
