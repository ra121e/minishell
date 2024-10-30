/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 05:18:17 by xlok              #+#    #+#             */
/*   Updated: 2024/10/30 08:21:04 by xlok             ###   ########.fr       */
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

void	print_loop(t_node *cur, int n_opt, int i)
{
	while (cur->cmd[i])
	{
		dprintf(cur->fd_w[1], "%s", cur->cmd[i]);
		if (cur->cmd[i + 1])
			dprintf(cur->fd_w[1], " ");
		i++;
	}
	if (!n_opt)
		dprintf(cur->fd_w[1], "\n");
}

void	builtin_echo(t_node *cur)
{
	int	n_opt;
	int	i;

	if (!cur->cmd[1])
		return ;
	n_opt = is_n_opt(cur->cmd[1]);
	i = 1;
	if (!n_opt)
		print_loop(cur, n_opt, i);
	else
	{
		while (is_n_opt(cur->cmd[i]))
			i++;
		print_loop(cur, n_opt, i);
	}
}
