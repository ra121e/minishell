/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:58:26 by xlok              #+#    #+#             */
/*   Updated: 2024/10/23 07:13:51 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_if_no_arg(t_ms *ms)
{
	int	i;

	if (!ms->cmd[1])
	{
		i = -1;
		while (ms->envp[++i])
		{
			if (!ms->envp[i]->value)
				printf("declare -x %s\n", ms->envp[i]->key);
			else if (!ft_strncmp(ms->envp[i]->value, "", 1))
				printf("declare -x %s=\"\"\n", ms->envp[i]->key);
			else
				printf("declare -x %s=\"%s\"\n", ms->envp[i]->key, ms->envp[i]->value);
		}
		return (1);
	}
	return (0);
}

void	export_add(t_ms *ms, t_envp **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	ms->envp = malloc(sizeof(t_envp) * (i + 2));
	if (!ms->envp)
		perror("malloc error for export_add\n");
	i = -1;
	while (envp[++i])
	{
		ms->envp[i] = malloc(sizeof(t_envp));
		if (!ms->envp[i])
			perror("malloc error for export_add\n");
		ms->envp[i] = envp[i];
	}
	ms->envp[i] = malloc(sizeof(t_envp));
	if (!ms->envp[i])
		perror("malloc error for export_add\n");
	ms->envp[i]->key = ms->key;
	ms->envp[i]->value = ms->value;
	ms->envp[i]->pair = ms->pair;
	ms->envp[++i] = 0;
	free(envp);
}

void	update_env(t_ms *ms)
{
	int	i;

	ms->len = ft_strlen(ms->key);
	i = -1;
	while (ms->envp[++i])
	{
		if (!ft_strncmp(ms->envp[i]->key, ms->key, ms->len + 1))
		{
			if (!ms->envp[i]->value || ms->value)
			{
//				ms->envp[i]->key = ms->key;
				ms->envp[i]->value = ms->value;
				ms->envp[i]->pair = ms->pair;
				break ;
			}
		}
	}
	if (!ms->envp[i])
		export_add(ms, ms->envp);
}
