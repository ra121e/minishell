/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 08:45:33 by xlok              #+#    #+#             */
/*   Updated: 2024/12/07 08:46:11 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shlvl(t_ms *ms, int shlvl, int i)
{
	char	*tmp;

	tmp = ms->envp[i]->value;
	ms->envp[i]->value = ft_itoa(shlvl);
	if (!ms->envp[i]->value)
		error_malloc(ms, "init_envp_shlvl malloc error");
	free_str(tmp);
	tmp = ms->envp[i]->pair;
	ms->envp[i]->pair = ft_strsjoin(3, ms->envp[i]->key, \
			"=", ms->envp[i]->value);
	if (!ms->envp[i]->pair)
		error_malloc(ms, "init_envp_shlvl malloc error");
	free_str(tmp);
}

void	init_envp_shlvl(t_ms *ms)
{
	int		shlvl;
	int		i;

	i = -1;
	while (ms->envp[++i])
	{
		if (!ft_strncmp(ms->envp[i]->key, "SHLVL", 6))
		{
			shlvl = ft_m_atoi(ms->envp[i]->value) + 1;
			if (shlvl < 0)
				shlvl = 0;
			else if (shlvl > 999)
			{
				ft_dprintf(2, "minishell: warning: shell level ");
				ft_dprintf(2, "(%d) too high, resetting to 1\n", shlvl);
				shlvl = 1;
			}
			update_shlvl(ms, shlvl, i);
			return ;
		}
	}
	ms->key = ft_strdup("SHLVL");
	ms->value = ft_strdup("1");
	ms->pair = ft_strdup("SHLVL=1");
	export_add(ms, ms->envp);
}
