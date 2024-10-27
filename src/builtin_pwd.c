/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:08:56 by xlok              #+#    #+#             */
/*   Updated: 2024/10/27 14:46:14 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO:pwd in bash returns from PCB/fd
//if dir is rm by another process while current process is in it
//current code returns error while pwd in bash returns dir from PCB/fd
//but current code is not in a running state like bash yet so...
void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		perror("minishell: ");
	printf("%s\n", cwd);
	free(cwd);
}
