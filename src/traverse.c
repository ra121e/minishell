/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:16:22 by athonda           #+#    #+#             */
/*   Updated: 2024/10/21 18:51:59 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	traverse(t_node *cur, t_ms *ms, int fd_w[2])
{
//	t_node	*cur;
	int		left;
	int		right;
	int		pipfd[2];

//	cur = head;
	if (cur->kind == ND_PIPE)
	{
		if (pipe(pipfd) == -1)
			error_exit("pip creation error");
		left = traverse(cur->left, ms, pipfd);
		right = traverse(cur->right, ms, fd_w);
		dprintf(2, "status of right command: %d\n", right);
	}
	else if (cur->kind == ND_AND)
	{
		left = traverse(cur->left, ms, fd_w);
		if (left)
		{
	//		right = traverse(cur->right, ms, fd_w);
			return (0);
		}
	}
	else if (cur->kind == ND_OR)
	{
		left = traverse(cur->left, ms, fd_w);
		if (!left)
		{
	//		right = traverse(cur->right, ms, fd_w);
			return (0);
		}
	}
	else
		return (exec_cmd(cur, ms, fd_w));
	return (0);
}

int	traverse_start(t_node *head, t_ms *ms)
{
	int	status;

	if (!head)
		return (0);
	traverse(head, ms, 0);
	waitpid(ms->pid, &status, 0);
	while (1)
	{
		if (wait(0) == -1)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	return (WEXITSTATUS(status));
}
