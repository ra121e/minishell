/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:36:49 by xlok              #+#    #+#             */
/*   Updated: 2024/09/21 22:05:05 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>//TODO:shift to minishell.h

bool	is_delimiter(char c)
{
	char	delimiter[] = " +-*/%()[]{}|&'";//TODO:minishell doesn't need arithmetic
	int		i;

	i = -1;
	while (delimiter[++i])
	{
		if (c == delimiter[i])
			return (1);
	}
	if (c == '"')
		return (1);
//TODO:redirection
	return (0);
}

bool	is_builtin(char *str)
{
	return (ft_strncmp(str, "echo", 4) || ft_strncmp(str, "cd", 2));
//TODO:add other builtin if works
}

int	lexer(char *str)
{
	int		start;
	int		end;
	char	*token;
	
	start = 0;
	end = 0;

	while (end <= (int)ft_strlen(str))
	{
		if (!is_delimiter(str[end]))
			end++;
		else if (is_delimiter(str[end]) && start != end)
		{
			token = ft_substr(str, start, end - start + 1);
			if (is_builtin(token))
				printf("Builtin: %s\n", token);
			else
				printf("Word: %s\n", token);
			end++;
		}
	}
	return (0);
}
