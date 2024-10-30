/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:28:53 by xlok              #+#    #+#             */
/*   Updated: 2024/10/30 23:17:36 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_if_found(t_envp **envp, t_node *cur, int i)
{
	int	j;

	j = 0;
	while (cur->cmd[++j])
	{
		if (!ft_strncmp(envp[i]->key, cur->cmd[j], ft_strlen(cur->cmd[j]) + 1))
		{
			free(envp[i]->key);
			free(envp[i]->value);
			free(envp[i]->pair);
			free(envp[i]);
			envp[i] = 0;
			break ;
		}
	}
}

void	update_envp(t_ms *ms, t_envp **envp, t_node *cur, int new_envp_len)
{
	int	i;
	int	n;

	ms->envp = malloc(sizeof(t_envp) * (new_envp_len + 1));
	if (!ms->envp)
		perror("malloc error for update_envp after unset\n");
	n = 0;
	i = -1;
	while (envp[++i])
	{
		unset_if_found(envp, cur, i);
		if (envp[i])
			ms->envp[n++] = envp[i];
	}
	ms->envp[n] = 0;
}

void	builtin_unset(t_ms *ms, t_node *cur)
{
	int	i;
	int	j;
	int	var;

	var = 0;
	i = -1;
	while (ms->envp[++i])
	{
		j = 0;
		while (cur->cmd[++j])
		{
			if (!ft_strncmp(ms->envp[i]->key, cur->cmd[j], \
						ft_strlen(cur->cmd[j]) + 1))
				var++;
		}
	}
	if (var)
		update_envp(ms, ms->envp, cur, i - var);
}
