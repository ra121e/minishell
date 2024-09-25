/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:36:49 by xlok              #+#    #+#             */
/*   Updated: 2024/09/25 16:52:08 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || \
		c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

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
t_token	*lexer(char *str)
{
	int		start;
	int		end;
	int		len;
	char	*token;
	t_token	*head;

	head = NULL;
	start = 0;
	end = 0;
	len = (int)(ft_strlen(str));
	while (end <= len)
	{
		if (!is_delimiter(str[end]) && end < len)
			end++;
		else if (start == end)
		{
/*
1) few spaces at the end of str: str[end] comes to \0 and handled as delimiter
  -> add \0 condition in if	statement
2) get substr and apply tokenize() on the substr which is delimiter
*/
			if (str[end] != ' ' && str[end] != '\0')
			{
				token = ft_substr(str, start, 1);
				tokenize(&head, token, TK_RESERVED);
				printf("Delimiter A: %c\n", str[end]);
			}
			start = ++end;
		}
		else
		{
			if (is_builtin(token))
			{
				token = ft_substr(str, start, end - start);
				tokenize(&head, token, TK_BUILTIN);
				printf("Builtin: %s\n", token);
			}
			else
			{
				token = ft_substr(str, start, end - start);
				tokenize(&head, token, TK_WORD);
				printf("Word: %s\n", token);
			}
			if (end < len && str[end] != ' ')
			{
/*
get substr and apply tokenize() on the substr which is delimiter
*/
				token = ft_substr(str, end, 1);
				tokenize(&head, token, TK_RESERVED);
				printf("Delimiter B: %c\n", str[end]);
			}
			start = ++end;
		}
	}
	return (head);
}
