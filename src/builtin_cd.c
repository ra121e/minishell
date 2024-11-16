/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:02:22 by athonda           #+#    #+#             */
/*   Updated: 2024/11/16 21:25:33 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	invalid_dir(t_ms *ms, char *arg)
{
	if (chdir(arg) == -1)
	{
		if (errno == EACCES)
			ft_dprintf(2, "minishell: cd: %s: Permission denied\n", arg);
		else
			ft_dprintf(2, "minishell: cd: %s: No such file or directory\n", arg);
		ms->exit_status = 1;
	}
	else
		ms->exit_status = 0;
}

void	builtin_cd(t_ms *ms)
{
	char	**homepath;

	if (ms->cmd[1] == NULL)
	{
		homepath = find_envpath(ms, "HOME=");
		if (!homepath || chdir(get_var(ms, "HOME")) == -1)
		{
			ft_dprintf(2, "minishell: cd: HOME not set\n");
			ms->exit_status = 1;
		}
		else
			ms->exit_status = 0;
		if (homepath)
			free_str_array(homepath);
	}
	else if (ms->cmd[2])
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		ms->exit_status = 1;
	}
	else
		invalid_dir(ms, ms->cmd[1]);
}
