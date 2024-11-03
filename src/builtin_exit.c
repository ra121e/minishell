/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:58:55 by athonda           #+#    #+#             */
/*   Updated: 2024/11/03 21:52:23 by athonda          ###   ########.fr       */
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
	if (ms->cmd[1] && (ms->cmd[1][i] == '-' || ms->cmd[1][i] == '+'))
		i++;
	while (ms->cmd[1] && ms->cmd[1][i])
	{
		if (!ft_isdigit(ms->cmd[1][i]))
		{
			ft_dprintf(2, "bash: exit: %s: numeric argument required\n", ms->cmd[1]);
			exit(2);
		}
		i++;
	}
	if (ms->cmd[1])
		c = ft_atoi(ms->cmd[1]);
	else
		c = 0;
	if (ms->in_pipe == 0)
	{
		ft_dprintf(2, "exit\n");
		if (!ms->cmd[1])
			exit(0);
		else if (ms->cmd[2])
		{
			ft_dprintf(2, "bash: exit: too many arguments\n");
			ms->exit_status = 1;
		}
		else
			exit(c);
	}
	else
	{
		if (ms->cmd[2])
		{
			ft_dprintf(2, "bash: exit: too many arguments\n");
			exit(1);
		}
		else
			exit(c);
	}
}