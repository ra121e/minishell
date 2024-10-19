/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:34:39 by athonda           #+#    #+#             */
/*   Updated: 2024/10/19 20:24:07 by athonda          ###   ########.fr       */
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

void	cmd_envp(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->envp[i])
		i++;
	ms->cmd_envp = malloc(sizeof (char *) * i + 1);
	if (ms->cmd_envp == NULL)
		return ;
	i = -1;
	while (ms->envp[++i])
		ms->cmd_envp[i] = ms->envp[i]->pair;
	ms->cmd_envp[i] = NULL;
}

void	init_env(t_ms *ms, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	ms->envp = malloc(sizeof(t_envp) * (i + 1));
	if (!ms->envp)
		perror("malloc error for init_env\n");
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		ms->envp[i] = malloc(sizeof(t_envp));
		if (!ms->envp[i])
			perror("malloc error for init_env\n");
		ms->envp[i]->key = ft_substr(envp[i], 0, j);
		ms->envp[i]->value= ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j);
		ms->envp[i]->pair = ft_strdup(envp[i]);
		i++;
	}
	ms->envp[i] = malloc(sizeof(t_envp));
	if (!ms->envp[i])
		perror("malloc error for init_env\n");
	ms->envp[i] = 0;
}

void	b_env(t_envp **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i]->value)
			printf("%s\n", envp[i]->pair);
		i++;
	}
}
