/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:08:56 by xlok              #+#    #+#             */
/*   Updated: 2024/10/30 18:05:01 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_node *cur)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		perror("minishell: ");
	dprintf(cur->fd_w[1], "%s\n", cwd);
	free(cwd);
}
