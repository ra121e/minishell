/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:24:39 by xlok              #+#    #+#             */
/*   Updated: 2024/11/23 07:58:16 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_cmd_before_exit(t_ms *ms, unsigned char c)
{
	if (ms->cmd)
	{
		free(ms->cmd_envp);
		if (ms->cmd && *ms->cmd)
			free_str_array(ms->cmd);
	}
	cleanup(ms);
	cleanup_final(ms);
	exit(c);
}

void	cleanup_envp(t_ms *ms)
{
	int	i;

	i = -1;
	while (ms->envp[++i])
	{
		free_str(ms->envp[i]->key);
		free_str(ms->envp[i]->value);
		free_str(ms->envp[i]->pair);
		free(ms->envp[i]);
		ms->envp[i] = 0;
	}
	free(ms->envp);
	ms->envp = 0;
}

void	cleanup(t_ms *ms)
{
	if (ms->head)
		free_token(ms);
	if (ms->start_node)
		ast_free(ms->start_node);
}

void	cleanup_final(t_ms *ms)
{
	cleanup_envp(ms);
	free(ms->prompt);
	free(ms);
}
