/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:58:26 by xlok              #+#    #+#             */
/*   Updated: 2024/11/22 00:23:58 by xlok             ###   ########.fr       */
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
				ft_dprintf(STDOUT_FILENO, "declare -x %s\n", ms->envp[i]->key);
			else if (ft_strncmp(ms->envp[i]->key, "_", 2))
				ft_dprintf(STDOUT_FILENO, "declare -x %s=\"%s\"\n", \
						ms->envp[i]->key, ms->envp[i]->value);
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
		error_malloc(ms, "malloc error for export_add");
	i = -1;
	while (envp[++i])
		ms->envp[i] = envp[i];
	ms->envp[i] = malloc(sizeof(t_envp));
	if (!ms->envp[i])
		error_malloc(ms, "malloc error for export_add");
	ms->envp[i]->key = ms->key;
	ms->envp[i]->value = ms->value;
	ms->envp[i]->pair = ms->pair;
	ms->envp[++i] = 0;
	free(envp);
	envp = 0;
}

void	update_env_value(t_ms *ms, int i)
{
	char	*tmp;

	free_str(ms->key);
	tmp = ms->envp[i]->value;
	ms->envp[i]->value = ms->value;
	free_str(tmp);
	tmp = ms->envp[i]->pair;
	ms->envp[i]->pair = ms->pair;
	free_str(tmp);
}

static void	free_cur(t_ms *ms)
{
	free_str(ms->key);
	free_str(ms->value);
	free_str(ms->pair);
}

void	update_env(t_ms *ms)
{
	int		i;

	ms->len = ft_strlen(ms->key);
	i = -1;
	while (ms->envp[++i])
	{
		if (!ft_strncmp(ms->envp[i]->key, ms->key, ms->len + 1))
		{
			if (!ft_strncmp(ms->key, "_", 2))
			{
				free_cur(ms);
				i++;
			}
			else if (!ms->envp[i]->value || ms->value)
				update_env_value(ms, i);
			else
				free_cur(ms);
			return ;
		}
	}
	if (!ms->envp[i])
		export_add(ms, ms->envp);
}
