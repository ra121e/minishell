/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:25:17 by xlok              #+#    #+#             */
/*   Updated: 2024/11/01 21:38:54 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*newnode(char *str)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof (t_node) * 1);
	if (node == NULL)
		return (NULL);
	node->kind = ND_COMMAND;
	node->str = str;
	node->left = NULL;
	node->right = NULL;
	node->fd_w[2] = 0;
	return (node);
}

void	word_split_loop(t_ms *ms, t_node *cur, char **split)
{
	int		i;

	ms->tmp_node = cur->right;
	ms->front = 0;
	ms->back = 0;
	i = 0;
	while (split[++i])
	{
		if (i == 1)
		{
			cur->str = split[0];
			ms->front = cur;
		}
		else
			ms->front = ms->back;
		ms->back = newnode(split[i]);
		ms->front->right = ms->back;
	}
	ms->back->right = ms->tmp_node;
}

void	word_split(t_ms *ms, t_node *cur)
{
	char	**split;

	split = ft_split(cur->str, ' ');
	if (!split[1])
	{
		cur->str = split[0];
		return ;
	}
	word_split_loop(ms, cur, split);
	free(split);
	ms->expand_var = 0;
}

void	expansion(t_ms *ms, t_node *cur)
{
	t_node	*tmp;

	ms->expand_var = 0;
	while (cur)
	{
		if (cur->kind == ND_COMMAND || cur->kind == ND_WORD)
			expansion_var(ms, cur->str);
		tmp = cur->right;
		if (ms->expand_var && cur)
			word_split(ms, cur);
		cur = tmp;
	}
}
