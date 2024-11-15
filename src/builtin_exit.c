/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:58:55 by athonda           #+#    #+#             */
/*   Updated: 2024/11/15 08:01:02 by xlok             ###   ########.fr       */
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

static void	clean_before_exit(t_ms *ms, unsigned char c)
{
	free(ms->cmd_envp);
	free_str_array(ms->cmd);
	cleanup(ms);
	cleanup_final(ms);
	exit(c);
}

static void	process_in_parent(t_ms *ms, unsigned char c)
{
	ft_dprintf(2, "exit\n");
	if (ms->cmd[1] && ms->cmd[2])
	{
		ft_dprintf(2, "bash: exit: too many arguments\n");
		ms->exit_status = 1;
	}
	else
		clean_before_exit(ms, c);
}

static void	process_in_child(t_ms *ms, unsigned char c)
{
	if (ms->cmd[1] && ms->cmd[2])
	{
		ft_dprintf(2, "bash: exit: too many arguments\n");
		exit(1);
	}
	else
		exit(c);
}

static void	process_arg(t_ms *ms, int i)
{
	if (!ft_isdigit(ms->cmd[1][i]))
	{
		ft_dprintf(2, "bash: exit: %s: numeric argument required\n", ms->cmd[1]);
		if (ms->in_pipe == 0)
			clean_before_exit(ms, 2);
		else
			exit(2);
	}
}

void	builtin_exit(t_ms *ms)
{
	unsigned char	c;
	int				i;

	i = 0;
	if (ms->cmd[1] && (ms->cmd[1][i] == '-' || ms->cmd[1][i] == '+'))
		i++;
	while (ms->cmd[1] && ms->cmd[1][i])
	{
		process_arg(ms, i);
		i++;
	}
	if (ms->cmd[1])
		c = ft_atoi(ms->cmd[1]);
	else
		c = ms->exit_status;
	if (ms->in_pipe == 0)
		process_in_parent(ms, c);
	else
		process_in_child(ms, c);
}
