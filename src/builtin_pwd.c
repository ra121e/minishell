/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:08:56 by xlok              #+#    #+#             */
/*   Updated: 2024/11/22 00:24:09 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_ms *ms)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		error_malloc(ms, "getcwd malloc error");
	ft_dprintf(STDOUT_FILENO, "%s\n", cwd);
	free(cwd);
	ms->exit_status = 0;
}
