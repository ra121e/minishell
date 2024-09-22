/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:36:49 by xlok              #+#    #+#             */
/*   Updated: 2024/09/22 17:50:13 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_delimiter(char c)
{
	char	delimiter[] = " =+-*/%()[]{}|&'";//TODO:minishell doesn't need arithmetic
	int		i;

	i = -1;
	while (delimiter[++i])
	{
		if (c == delimiter[i])
			return (1);
	}
	if (c == '"')
		return (1);
//TODO:handle redirection char
	return (0);
}

bool	is_builtin(char *str)
{
	return (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2) || \
			!ft_strncmp(str, "pwd", 3) || !ft_strncmp(str, "export", 6) || \
			!ft_strncmp(str, "unset", 5) || !ft_strncmp(str, "env", 3) || \
			!ft_strncmp(str, "exit", 4));
}

//TODO:operator/assignment etc.? what word to choose apart from builtin, word etc.
int	lexer(char *str)
{
	int		start;
	int		end;
	int		len;
	char	*token;

	start = 0;
	end = 0;
	len = (int)(ft_strlen(str));
	while (end <= len)
	{
		if (!is_delimiter(str[end]) && end < len)
			end++;
		else if (start == end)
		{
			if (str[end] != ' ')
				printf("Delimiter: %c\n", str[end]);
			start = ++end;
		}
		else
		{
			token = ft_substr(str, start, end - start);
			if (is_builtin(token))
				printf("Builtin: %s\n", token);
			else
				printf("Word: %s\n", token);
			if (end < len && str[end] != ' ')
				printf("Delimiter: %c\n", str[end]);
			start = ++end;
		}
	}
	return (0);
}
