/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:24:39 by xlok              #+#    #+#             */
/*   Updated: 2024/11/04 23:49:12 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char *str)
{
	free(str);
	str = 0;
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

void	free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i] && *str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
	str = 0;
}

void	free_token(t_ms *ms)
{
	t_token	*tmp;

	while (ms->head)
	{
		tmp = ms->head;
		if (ms->head->str)
			free(ms->head->str);
		ms->head = ms->head->next;
		free(tmp);
	}
}
void	cleanup(t_ms *ms)
{
//	t_token	*head;
//	char	*token;
	if (ms->head)
		free_token(ms);
	if (ms->start_node)
		ast_free(ms->start_node);
}

void	cleanup_final(t_ms *ms)
{
//	cleanup(ms);
	cleanup_envp(ms);
	free(ms->prompt);
	free(ms);
}
