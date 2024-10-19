/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:16:22 by athonda           #+#    #+#             */
/*   Updated: 2024/10/19 20:43:08 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	traverse(t_node *head, t_ms *ms)
{
	t_node	*cur;
	int		left;
//	int		right;

	cur = head;

	if (cur->kind == ND_PIPE)
	{
		left = traverse(cur->left, ms);
//		right = traverse(cur->right, ms);
//		exec_pip();
	}
	else if (cur->kind == ND_AND)
	{
		left = traverse(cur->left, ms);
		if (left)
		{
	//		right = traverse(cur->right, ms);
			return (0);
		}
	}
	else if (cur->kind == ND_OR)
	{
		left = traverse(cur->left, ms);
		if (!left)
		{
	//		right = traverse(cur->right, ms);
			return (0);
		}
	}
	else
		exec_cmd(cur, ms);
	return (0);
}
