/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:05:30 by athonda           #+#    #+#             */
/*   Updated: 2024/11/06 17:56:29 by athonda          ###   ########.fr       */
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
	node->left = NULL;
	node->right = NULL;
	node->error = false;
	node->fd_w[0] = -1;
	node->fd_w[1] = -1;
	return (node);
}

void	ast_set_str_left(t_node *node, t_token **token, t_node *left)
{
	node->str = (*token)->str;
	node->left = left;
	*token = (*token)->next;
}

void	ast_free(t_node *node)
{
	if (node == NULL)
		return ;
	ast_free(node->left);
	ast_free(node->right);
	free(node);
	node = 0;
}
