/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:58:55 by athonda           #+#    #+#             */
/*   Updated: 2024/11/02 13:50:35 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_exit
 */

#include "minishell.h"

/**
 * @fn builtin_exit
 * @brief exit command by exit system call
 * @param[in] ms for command name and arguments
 * @param[out] nothing
 * @note
 * 	- case non numeric argument
 * 	- case in prompt or in pipe
 *		- exit number and one more arguments
 */

void	builtin_exit(t_ms *ms)
{
	unsigned char	c;
	int				i;

	i = 0;
	if (ms->cmd[1][i] == '-' || ms->cmd[1][i])
		i++;
	while (ms->cmd[1][i])
	{
		if (!ft_isdigit(ms->cmd[1][i]))
		{
			dprintf(2, "bash: exit: %s: numeric argument required\n", ms->cmd[1]);
			exit(2);
		}
		i++;
	}
/*
	if (ms->cmd[2])
	{
		dprintf(2, "exit\n");
		dprintf(2, "bash: exit: too many arguments\n");
		ms->exit_status = 1;
		return ;
	}
*/
	c = ft_atoi(ms->cmd[1]);
	if (ms->fd_r == 0 && ms->fd_w[0] == 0 && ms->fd_w[1] == 1)
	{
		dprintf(2, "exit\n");
		if (ms->cmd[2])
		{
			dprintf(2, "bash: exit: too many arguments\n");
			exit(1);
		}
		exit(c);
	}
	else
	{
		if (ms->cmd[2])
		{
			dprintf(2, "bash: exit: too many arguments\n");
		}
		ms->exit_status = c;
		exit(c);
	}
}