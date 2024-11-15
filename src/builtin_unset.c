/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:28:53 by xlok              #+#    #+#             */
/*   Updated: 2024/11/10 19:54:04 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_if_found(t_ms *ms, t_envp **envp, int i)
{
	int	j;

	j = 0;
	while (ms->cmd[++j])
	{
		if (!ft_strncmp(envp[i]->key, ms->cmd[j], ft_strlen(ms->cmd[j]) + 1))
		{
			free_str(envp[i]->key);
			free_str(envp[i]->value);
			free_str(envp[i]->pair);
			free(envp[i]);
			envp[i] = 0;
			break ;
		}
	}
}

void	update_envp(t_ms *ms, t_envp **envp, int new_envp_len)
{
	int	i;
	int	n;

	ms->envp = malloc(sizeof(t_envp) * (new_envp_len + 1));
	if (!ms->envp)
		error_malloc(ms, "malloc error for update_envp after unset");
	n = 0;
	i = -1;
	while (envp[++i])
	{
		unset_if_found(ms, envp, i);
		if (envp[i])
			ms->envp[n++] = envp[i];
	}
	ms->envp[n] = 0;
	free(envp);
	envp = 0;
}

void	builtin_unset(t_ms *ms)
{
	int	i;
	int	j;
	int	var;

	var = 0;
	i = -1;
	while (ms->envp[++i])
	{
		j = 0;
		while (ms->cmd[++j])
		{
			if (!ft_strncmp(ms->envp[i]->key, ms->cmd[j], \
						ft_strlen(ms->cmd[j]) + 1))
				var++;
		}
	}
	if (var)
		update_envp(ms, ms->envp, i - var);
	ms->exit_status = 0;
}
