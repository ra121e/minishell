/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 06:24:53 by xlok              #+#    #+#             */
/*   Updated: 2024/10/30 08:33:29 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *str)
{
	return (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3) || \
			!ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 7) || \
			!ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4) || \
			!ft_strncmp(str, "exit", 5));
}

void	builtin(t_ms *ms, t_node *cur)
{
	if (!ft_strncmp(cur->cmd[0], "echo", 5))
		builtin_echo(cur);
//	else if (!ft_strncmp(cur->cmd[0], "cd", 3))
//		builtin_cd(ms);
	else if (!ft_strncmp(cur->cmd[0], "pwd", 4))
		builtin_pwd();
	else if (!ft_strncmp(cur->cmd[0], "export", 7))
		builtin_export(ms);
	else if (!ft_strncmp(cur->cmd[0], "unset", 6))
		builtin_unset(ms);
	else if (!ft_strncmp(cur->cmd[0], "env", 4))
		builtin_env(ms);
//	else if (!ft_strncmp(cur->cmd[0], "exit", 5))
//		builtin_exit(ms);
}
