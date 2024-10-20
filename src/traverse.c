/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:16:22 by athonda           #+#    #+#             */
/*   Updated: 2024/10/20 21:09:17 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	traverse(t_node *head, t_ms *ms, int fd_r, int fd_w[2])
{
	t_node	*cur;
	int		left;
	int		right;
	int		pipfd[2];

	cur = head;

	if (cur->kind == ND_PIPE)
	{
		if (pipe(pipfd) == -1)
			error_exit("pip creation error");
		fd_w = pipfd;
		left = traverse(cur->left, ms, fd_r, fd_w);
		right = traverse(cur->right, ms, fd_r, fd_w);
		dprintf(2, "status of right command: %d\n", right);
	}
	else if (cur->kind == ND_AND)
	{
		left = traverse(cur->left, ms, fd_r, fd_w);
		if (left)
		{
	//		right = traverse(cur->right, ms, fd_r, fd_w);
			return (0);
		}
	}
	else if (cur->kind == ND_OR)
	{
		left = traverse(cur->left, ms, fd_r, fd_w);
		if (!left)
		{
	//		right = traverse(cur->right, ms, fd_r, fd_w);
			return (0);
		}
	}
	else
		fd_r = exec_cmd(cur, ms, fd_r, fd_w);
	return (0);
}
