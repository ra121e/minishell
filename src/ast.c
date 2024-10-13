/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:05:30 by athonda           #+#    #+#             */
/*   Updated: 2024/10/09 21:07:10 by athonda          ###   ########.fr       */
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
	node->av = NULL;
	node->left = NULL;
	node->right = NULL;
	node->red_symbol = NULL;
	node->file_name = NULL;
	return (node);
}