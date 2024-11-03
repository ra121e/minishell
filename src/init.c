/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:19:55 by xlok              #+#    #+#             */
/*   Updated: 2024/11/03 18:48:26 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_rl_done(void)
{
	return (0);
}

void	init(t_ms *ms)
{
	ms->head = 0;
	ms->start = 0;
	ms->len = 0;
	ms->end = 0;
	ms->key = 0;
	ms->pid = 0;
	ms->prompt = ft_strsjoin(3, "\001\033[35m\002" \
			, "minishell~Powered by Honda:$", "\001\033[0m\002");
	if (!ms->prompt)
		perror("ms->prompt malloc error");
	rl_event_hook = check_rl_done;
}

void	init_envp(t_ms *ms, char **envp)
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
		ms->envp[i]->value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j);
		ms->envp[i]->pair = ft_strdup(envp[i]);
		i++;
	}
	ms->envp[i] = 0;
}
