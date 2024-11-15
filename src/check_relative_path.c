/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_relative_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:33:32 by xlok              #+#    #+#             */
/*   Updated: 2024/11/15 22:09:10 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_relative_path(char *cmd)
{
	struct stat	sb;

	stat(cmd, &sb);
	if (cmd && (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')))
	{
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
			return (1);
	}
	return (0);
}
