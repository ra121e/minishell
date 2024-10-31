/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:16:22 by athonda           #+#    #+#             */
/*   Updated: 2024/10/31 19:46:45 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	traverse_cmd(t_node *cur, t_ms *ms, int fd_w[2], int action)
{
	if (action == HEREDOC)
		heredoc(ms, cur);
	else
	{
		redirection(ms, cur, fd_w);
		if (ms->cmd[0])
			exec_cmd(ms);
	}
}

void	traverse_continue(t_node *cur, t_ms *ms, int fd_w[2], int action)
{
	if (cur->kind == ND_AND)
	{
		ms->in_pipe = 0;
		traverse(cur->left, ms, fd_w, action);
		if (!ms->exit_status && ms->sig == 0)
			traverse(cur->right, ms, fd_w, action);
	}
	else if (cur->kind == ND_OR)
	{
		ms->in_pipe = 0;
		traverse(cur->left, ms, fd_w, action);
		if (ms->exit_status && ms->sig == 0)
			traverse(cur->right, ms, fd_w, action);
	}
	else
		traverse_cmd(cur, ms, fd_w, action);
}

void	traverse(t_node *cur, t_ms *ms, int fd_w[2], int action)
{
	int		pipfd[2];

	if (cur->kind == ND_PIPE)
	{
		ms->in_pipe = 1;
		if (pipe(pipfd) == -1)
			error_exit("pip creation error");
		traverse(cur->left, ms, pipfd, action);
		if (ms->sig == 0)
			traverse(cur->right, ms, fd_w, action);
	}
	else
		traverse_continue(cur, ms, fd_w, action);
}

void	traverse_start(t_node *head, t_ms *ms, int action)
{
	if (!head)
		return ;
	traverse(head, ms, 0, action);
}
