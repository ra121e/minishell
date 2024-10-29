/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:02:22 by athonda           #+#    #+#             */
/*   Updated: 2024/10/28 22:16:29 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(t_ms *ms)
{
	char	*dir;

	dir = getcwd(0, 0);
	dprintf(2, "current dir: %s\n", dir);
	dprintf(2, "command: %s\n", ms->cmd[0]);
	dprintf(2, "path: %s\n", ms->cmd[1]);
	chdir(ms->cmd[1]);
	dir = getcwd(dir, 1024);
	dprintf(2, "current dir: %s\n", dir);
}