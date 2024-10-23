/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:25:17 by xlok              #+#    #+#             */
/*   Updated: 2024/10/24 20:46:26 by xlok             ###   ########.fr       */
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
	node->av = NULL;
	node->left = NULL;
	node->right = NULL;
	node->red_symbol = NULL;
	node->file_name = NULL;
	return (node);
}

void	word_split(t_ms *ms, t_node *cur)
{
	char	**split;
	int		i;

	split = ft_split(cur->str, ' ');
	if (!split[1])
		return ;
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
	free(split);
}

void	expansion(t_ms *ms, t_node *cur)
{
	t_node *tmp;

	while (cur)
	{
		expansion_var(ms, cur);
		tmp = cur->right;
		if (ms->expand_var && cur)
			word_split(ms, cur);
		cur = tmp;
	}
}
