/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:23:05 by xlok              #+#    #+#             */
/*   Updated: 2024/11/16 22:07:53 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_numeric_error(t_ms *ms, unsigned long res, int sign)
{
	if (sign == 1 && (res > LONG_MAX))
	{
		ft_dprintf(2, "exit\n");
		ft_dprintf(2, "bash: exit: %s: numeric argument required\n", ms->cmd[1]);
		clean_before_exit(ms, 2);
	}
	else if (sign == -1 && (res - 1 > LONG_MAX))
	{
		ft_dprintf(2, "exit\n");
		ft_dprintf(2, "bash: exit: %s: numeric argument required\n", ms->cmd[1]);
		clean_before_exit(ms, 2);
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
		clean_before_exit(ms, 2);
	}
	res = 0;
	while (ms->cmd[1][i] >= '0' && ms->cmd[1][i] <= '9')
	{
		res = (res * 10) + (ms->cmd[1][i] - '0');
		display_numeric_error(ms, res, sign);
		i++;
	}
}
