/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_relative_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:33:32 by xlok              #+#    #+#             */
/*   Updated: 2024/11/16 17:10:20 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_relative_path(char *cmd)
{
	struct stat	sb;
	char		*res;

	stat(cmd, &sb);
	if (S_ISDIR(sb.st_mode))
	{
		ft_dprintf(2, "minishell: %s is a directory\n", cmd);
		exit (126);
	}
	else if (!access(cmd, F_OK) && access(cmd, X_OK))
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", cmd);
		exit (126);
	}
	else if (!access(cmd, F_OK) && !access(cmd, X_OK))
	{
		res = ft_strdup(cmd);
		return (res);
	}
	return (0);
}
