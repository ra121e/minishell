/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:34:39 by athonda           #+#    #+#             */
/*   Updated: 2024/10/30 17:48:30 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_env.c
 */

#include "minishell.h"

/**
 * @fn env
 * @brief to display the list of Environment variables
 * @param[in] envp passed from main()
 */

void	builtin_env(t_ms *ms, t_node *cur)
{
	int	i;

	if (cur->cmd[1])
	{
		dprintf(2, "Subject requirement: env with no options or arguments\n");
		return ;
	}
	i = 0;
	while (ms->envp[i])
	{
		if (ms->envp[i]->value)
			dprintf(cur->fd_w[1], "%s\n", ms->envp[i]->pair);
		i++;
	}
}
