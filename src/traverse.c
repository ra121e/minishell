/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:16:22 by athonda           #+#    #+#             */
/*   Updated: 2024/10/29 21:04:33 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	traverse_cmd(t_node *cur, t_ms *ms, int fd_w[2], int action)
{
	if (action == INFO)
		cmd_info(ms, cur, fd_w);
	else
		exec_cmd(ms, cur);

//	if (ms->heredoc_tmp)
//	{
//		if (unlink("tmp") == -1)
//			dprintf(2, "error deleting heredoc tmp file\n");
//		ms->heredoc_tmp = 0;
//	}
}

void	traverse(t_node *cur, t_ms *ms, int fd_w[2], int action)
{
	int		pipfd[2];

	if (cur->kind == ND_PIPE)
	{
		if (action == INFO)
		{
			if (pipe(pipfd) == -1)
				error_exit("pip creation error");
			traverse(cur->left, ms, pipfd, action);
		}
		else
			traverse(cur->left, ms, 0, action);
		if (ms->sig == 0)
			traverse(cur->right, ms, fd_w, action);
	}
	else if (cur->kind == ND_AND)
	{
		traverse(cur->left, ms, fd_w, action);
		if (!ms->exit_status && ms->sig == 0)
			traverse(cur->right, ms, fd_w, action);
	}
	else if (cur->kind == ND_OR)
	{
		traverse(cur->left, ms, fd_w, action);
		if (ms->exit_status && ms->sig == 0)
			traverse(cur->right, ms, fd_w, action);
	}
	else
		traverse_cmd(cur, ms, fd_w, action);
}

void	traverse_start(t_node *head, t_ms *ms, int action)
{
	if (!head)
		return ;
	traverse(head, ms, 0, action);
}
