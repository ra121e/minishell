/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:33:50 by xlok              #+#    #+#             */
/*   Updated: 2024/10/30 08:33:59 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_node *cur)
{
	if (cur->fd_r > 2)
		close(cur->fd_r);
	if (cur->fd_w[1] > 2)
		close(cur->fd_w[1]);
}

void	free_cmd(t_node *cur)
{
	int	i;

	i = 0;
	while (cur->cmd[i])
		free(cur->cmd[i++]);
	free(cur->cmd);
}

void	free_cmd_envp(char **cmd_envp)
{
	int	i;

	i = 0;
	while (cmd_envp[i])
		free(cmd_envp[i++]);
	free(cmd_envp);
}

