/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:23:05 by xlok              #+#    #+#             */
/*   Updated: 2024/12/04 16:15:22 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	display_numeric_error(t_ms *ms, unsigned long res, int sign)
{
	if (sign == 1 && (res > LONG_MAX))
	{
		ft_dprintf(2, "exit\n");
		ft_dprintf(2, "bash: exit: %s: numeric argument required\n", ms->cmd[1]);
		before_exit(ms, 2);
	}
	else if (sign == -1 && (res - 1 > LONG_MAX))
	{
		ft_dprintf(2, "exit\n");
		ft_dprintf(2, "bash: exit: %s: numeric argument required\n", ms->cmd[1]);
		before_exit(ms, 2);
	}
}

void	long_check(t_ms *ms)
{
	unsigned long	res;
	int				sign;
	int				i;

	i = 0;
	sign = 1;
	if (ms->cmd[1][i] == '-')
		sign = -1;
	if (ms->cmd[1][i] == '+' || ms->cmd[1][i] == '-')
		i++;
	if ((i == 0 && ft_strlen(ms->cmd[1]) > 19) || \
		(i == 1 && ft_strlen(ms->cmd[1]) > 20))
	{
		ft_dprintf(2, "exit\n");
		ft_dprintf(2, "bash: exit: %s: numeric argument required\n", ms->cmd[1]);
		before_exit(ms, 2);
	}
	res = 0;
	while (ms->cmd[1][i] >= '0' && ms->cmd[1][i] <= '9')
	{
		res = (res * 10) + (ms->cmd[1][i] - '0');
		display_numeric_error(ms, res, sign);
		i++;
	}
}
