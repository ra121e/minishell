/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:28:53 by xlok              #+#    #+#             */
/*   Updated: 2024/12/07 12:06:07 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	envp_len(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->envp[i])
		i++;
	return (i);
}

static void	update_envp(t_ms *ms, t_envp **envp, char *var)
{
	int	i;
	int	n;

	ms->envp = malloc(sizeof(t_envp) * envp_len(ms));
	if (!ms->envp)
		error_malloc(ms, "malloc error for update_envp after unset");
	n = 0;
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i]->key, var, ft_strlen(var) + 1))
		{
			free_str(envp[i]->key);
			free_str(envp[i]->value);
			free_str(envp[i]->pair);
			free(envp[i]);
			envp[i] = 0;
		}
		if (envp[i])
			ms->envp[n++] = envp[i];
	}
	ms->envp[n] = 0;
	free(envp);
	envp = 0;
}

static void	update(t_ms *ms, char *var)
{
	int	i;

	i = -1;
	while (ms->envp[++i])
	{
		if (!ft_strncmp(ms->envp[i]->key, var, ft_strlen(var) + 1))
			break ;
	}
	if (!ms->envp[i])
		return ;
	update_envp(ms, ms->envp, var);
}

void	builtin_unset(t_ms *ms)
{
	int	i;

	i = -1;
	while (ms->cmd[++i])
	{
		if (!ft_strncmp(ms->cmd[i], "PWD", 4))
			ms->unset_pwd = 1;
		if (ft_strncmp(ms->cmd[i], "_", 2))
			update(ms, ms->cmd[i]);
	}
	ms->exit_status = 0;
}
