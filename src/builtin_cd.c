/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:02:22 by athonda           #+#    #+#             */
/*   Updated: 2024/11/03 21:25:11 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(t_ms *ms)
{
	if (ms->cmd[1] == NULL)
	{
		if (chdir(get_var(ms, "HOME")) == -1)
		{
			ft_dprintf(2, "bash: cd: HOME not set\n");
			ms->exit_status = 1;
		}
	}
	else if (ms->cmd[2])
	{
		ft_dprintf(2, "bash: cd: too many arguments\n");
		ms->exit_status = 1;
	}
	else if (chdir(ms->cmd[1]) == -1)
	{
		ft_dprintf(2, "bash: cd: %s: No such file or directory\n", ms->cmd[1]);
		ms->exit_status = 1;
	}
}
