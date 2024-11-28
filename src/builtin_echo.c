/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 05:18:17 by xlok              #+#    #+#             */
/*   Updated: 2024/11/28 20:28:08 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_opt(char *str)
{
	int	i;

	if (str[0] == '-' && str[1] == 'n')
	{
		i = 1;
		while (str[++i])
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	else
		return (0);
}

void	print_loop(t_ms *ms, int n_opt, int i)
{
	while (ms->cmd[i])
	{
		ft_dprintf(STDOUT_FILENO, "%s", ms->cmd[i]);
		if (ms->cmd[i + 1] && *ms->cmd[i + 1])
			ft_dprintf(STDOUT_FILENO, " ");
		i++;
	}
	if (!n_opt)
		ft_dprintf(STDOUT_FILENO, "\n");
}

void	builtin_echo(t_ms *ms)
{
	int	n_opt;
	int	i;

	if (!ms->cmd[1])
		n_opt = 0;
	else
		n_opt = is_n_opt(ms->cmd[1]);
	i = 1;
	if (!n_opt)
		print_loop(ms, n_opt, i);
	else
	{
		while (ms->cmd[i] && is_n_opt(ms->cmd[i]))
			i++;
		print_loop(ms, n_opt, i);
	}
	ms->exit_status = 0;
}
