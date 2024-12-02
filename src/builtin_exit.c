/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:58:55 by athonda           #+#    #+#             */
/*   Updated: 2024/12/02 22:45:08 by xlok             ###   ########.fr       */
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

static void	before_exit(t_ms *ms, unsigned char c)
{
	if (ms->in_pipe == 0)
	{
		if (dup2(ms->fd_stdin, STDIN_FILENO) < 0)
			error_exit("dup2 error");
		if (dup2(ms->fd_stdout, STDOUT_FILENO) < 0)
			error_exit("dup2 error");
		close(ms->fd_stdin);
		close(ms->fd_stdout);
	}
	clean_cmd_before_exit(ms, c);
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
		before_exit(ms, c);
}

static void	process_in_child(t_ms *ms, unsigned char c)
{
	if (ms->cmd[1] && ms->cmd[2])
	{
		ft_dprintf(2, "bash: exit: too many arguments\n");
		clean_cmd_before_exit(ms, 1);
	}
	else
		clean_cmd_before_exit(ms, c);
}

static void	process_arg(t_ms *ms)
{
	int	i;
	int	sign;

	sign = 0;
	if (ms->cmd[1][0] == '-' || ms->cmd[1][0] == '+')
		sign = 1;
	if (sign && !ms->cmd[1][1])
	{
		ft_dprintf(2, "exit\n");
		ft_dprintf(2, "bash: exit: %s: numeric argument required\n", ms->cmd[1]);
		before_exit(ms, 2);
	}
	i = sign;
	while (ms->cmd[1] && ms->cmd[1][i])
	{
		if (!ft_isdigit(ms->cmd[1][i]))
		{
			ft_dprintf(2, "exit\n");
			ft_dprintf(2, "bash: exit: %s: numeric argument required\n", \
			ms->cmd[1]);
			before_exit(ms, 2);
		}
		i++;
	}
}

void	builtin_exit(t_ms *ms)
{
	unsigned char	c;

	if (ms->cmd[1])
	{
		process_arg(ms);
		long_check(ms);
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
