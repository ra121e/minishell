/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:24:39 by xlok              #+#    #+#             */
/*   Updated: 2024/11/03 22:07:02 by xlok             ###   ########.fr       */
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

void	cleanup_str(char *str)
{
	if (str)
	{
		free(str);
		str = 0;
	}
}

void	cleanup_str2(char **str)
{
	if (*str)
	{
		free(*str);
		str = 0;
	}
}

void	cleanup_str_array(char **str)
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

void	cleanup(t_ms *ms)
{
	(void)ms;
//	t_token	*head;
//	char	*token;
	cleanup_str_array(ms->cmd);
	cleanup_str2(&ms->str);
	cleanup_str2(&ms->old_str);
//	t_node	*start_node;
//	t_node	*tmp_node;
//	t_node	*front;
//	t_node	*back;
}

void	cleanup_final(t_ms *ms)
{
//	cleanup(ms);
	cleanup_envp(ms);
	free(ms->prompt);
	free(ms);
}
