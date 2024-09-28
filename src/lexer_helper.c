/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:52:53 by xlok              #+#    #+#             */
/*   Updated: 2024/09/28 19:18:19 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_delimiter(char c)
{
	char	delimiter[] = " =-()[]{}";
	int		i;

	i = -1;
	while (delimiter[++i])
	{
		if (c == delimiter[i])
			return (1);
	}
	return (0);
}

bool	is_builtin(char *str)
{
	return (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3) || \
			!ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 7) || \
			!ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4) || \
			!ft_strncmp(str, "exit", 5));
}
