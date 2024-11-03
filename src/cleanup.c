/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:24:39 by xlok              #+#    #+#             */
/*   Updated: 2024/11/03 19:09:44 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_envp(t_ms *ms)
{
	int	i;

	i = -1;
	while (ms->envp[++i])
	{
		free(ms->envp[i]->key);
		free(ms->envp[i]->value);
		free(ms->envp[i]->pair);
		free(ms->envp[i]);
	}
	free(ms->envp);
}

void	cleanup_string(char *str)
{
	if (str)
	{
		free(str);
		str = 0;
	}
}

void	cleanup_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
	str = 0;
}

void	cleanup(t_ms *ms)
{
	(void)ms;
//	t_token	*head;
//	char	*token;
	cleanup_string(ms->str);
	cleanup_string(ms->var);
	cleanup_string(ms->var_value);
	cleanup_string(ms->old_str);
	cleanup_string(ms->new_str);
//	t_node	*start_node;
//	t_node	*tmp_node;
//	t_node	*front;
//	t_node	*back;
	cleanup_string_array(ms->cmd);
}

void	cleanup_final(t_ms *ms)
{
//	cleanup(ms);
	cleanup_envp(ms);
	free(ms->prompt);
	free(ms);
}
