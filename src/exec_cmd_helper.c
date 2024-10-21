/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:41:57 by xlok              #+#    #+#             */
/*   Updated: 2024/10/21 22:47:26 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_ms *ms, t_node *cur)
{
	int	i;

	i = 0;
	while (cur)
	{
		i++;
		cur = cur->right;
	}
	ms->cmd = malloc(sizeof(char *) * (i + 1));
	if (!ms->cmd)
		perror("ms->cmd malloc error");//malloc error
}

void	dup2_and_close(pid_t old_fd, pid_t new_fd)
{
	if (dup2(old_fd, new_fd) < 0)
		error_exit("dup2 error");
	close(old_fd);
}
