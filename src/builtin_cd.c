/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:02:22 by athonda           #+#    #+#             */
/*   Updated: 2024/11/01 21:47:57 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(t_ms *ms)
{
	if (ms->cmd[1] == NULL)
		return ;
	else if (ms->cmd[2])
	{
		dprintf(2, "bash: cd: too many arguments\n");
		return ;
	}
	if (chdir(ms->cmd[1]) == -1)
	{
		dprintf(2, "bash: cd: %s: No such file or directory\n", ms->cmd[1]);
		return ;
	}
}