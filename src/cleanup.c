/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:24:39 by xlok              #+#    #+#             */
/*   Updated: 2024/10/30 05:39:43 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_envp(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->envp[i])
	{
		free(ms->envp[i]->key);
		free(ms->envp[i]->value);
		free(ms->envp[i]->pair);
	}
	free(ms->envp);
}

void	cleanup(t_ms *ms)
{
//	t_token	*head;
//	char	*prompt;
//	char	*input;
//	char	*token;
//	char	*key;
//	char	*value;
//	char	*pair;
//	char	*str;
//	char	*var;
//	char	*var_value;
//	char	*new_str;
//	t_node	*start_node;
//	t_node	*cmd_node;
//	char	**cmd;
//	char	**cmd_envp;
	(void)ms;
}

void	cleanup_final(t_ms *ms)
{
	cleanup(ms);
	cleanup_envp(ms);
	free(ms->prompt);
	free(ms);
}
