/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:05:30 by athonda           #+#    #+#             */
/*   Updated: 2024/11/15 19:45:06 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ast_newnode(t_node_kind kind)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof (t_node) * 1);
	if (node == NULL)
		return (NULL);
	node->kind = kind;
	node->str = NULL;
	node->heredoc_str = NULL;
	node->left = NULL;
	node->right = NULL;
	node->error = false;
	return (node);
}

int	ast_set_str_left(t_node *node, t_token **token, t_node *left)
{
	if (!node)
	{
		left->error = true;
		return (0);
	}
	else
	{
		node->str = (*token)->str;
		node->left = left;
		if (left->error == true)
			node->error = true;
		*token = (*token)->next;
		return (1);
	}
}

void	ast_free(t_node *node)
{
	if (node == NULL)
		return ;
	ast_free(node->left);
	ast_free(node->right);
	free(node->heredoc_str);
	free(node);
	node = 0;
}
