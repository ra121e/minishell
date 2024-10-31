/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:08:56 by xlok              #+#    #+#             */
/*   Updated: 2024/10/31 15:12:38 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_ms *ms)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		perror("minishell: ");
	ft_dprintf(ms->fd_w[1], "%s\n", cwd);
	free(cwd);
}
