/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:16:22 by athonda           #+#    #+#             */
/*   Updated: 2024/10/19 12:47:10 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	traverse(t_node *head)
{
	t_node	*cur;
	t_node	*left;
	t_node	*right;

	cur = head;

	if (cur->kind == ND_PIPE)
	{
		left = traverse(cur->left);
		right = traverse(cur->right);
		exec_pip();
	}
	else if (cur->kind == ND_AND)
	{
		left = traverse(cur->left);
		if (left)
			right = traverse(cur->right);
	}
	else if (cur->kind == ND_OR)
	{
		left = traverse(cur->left);
		if (!left)
			right = traverse(cur->right);
	}
	else
	{
		exec_cmd(cur);
	}
}
