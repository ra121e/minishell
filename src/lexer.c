/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:36:49 by xlok              #+#    #+#             */
/*   Updated: 2024/09/27 19:57:29 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quotes(t_ms *ms, char *str, t_token **head)
{
	ms->end++;
	while (str[ms->end] && str[ms->end] != '\'')
		ms->end++;
	if (!str[ms->end])
	{
		ms->token = ft_substr(str, ms->start, ms->end - ms->start);
		if (!ms->token)
			perror("token malloc error");//malloc protection
		tokenize(head, ms->token, TK_WORD);
		printf("Word\n");
		ms->start = ms->end;
		return ;
	}
	ms->start++;
	ms->token = ft_substr(str, ms->start, ms->end - ms->start);
	if (!ms->token)
		perror("token malloc error");//malloc protection
	tokenize(head, ms->token, TK_SINGLE_QUOTES);
	printf("Single Quotes\n");
	ms->end++;
	ms->start = ms->end;
}

bool	is_delimiter(char c)
{
	char	delimiter[] = " =+-*/%()[]{}|&";
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
	return (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2) || \
			!ft_strncmp(str, "pwd", 3) || !ft_strncmp(str, "export", 6) || \
			!ft_strncmp(str, "unset", 5) || !ft_strncmp(str, "env", 3) || \
			!ft_strncmp(str, "exit", 4));
}

//TODO:operator/assignment etc.? what word to choose apart from builtin, word etc.
t_token	*lexer(char *str)
{
	t_ms	*ms;
	t_token	*head;

	ms = malloc(sizeof(t_ms));
	if (!ms)
		perror("ms malloc error");//malloc protection
	head = NULL;
	ms->start = 0;
	ms->end = 0;
	ms->len = (int)(ft_strlen(str));
	while (ms->end <= ms->len)
	{
//	Handle quotes
//	Handle redirections & AND/OR/asterisk
//	Handle others
//	Handle EOF
		if (str[ms->end] == '\'')
		{
			single_quotes(ms, str, &head);//add str and head to struct ms?
			continue ;
		}
		else if (!is_delimiter(str[ms->end]) && ms->end < ms->len)
			ms->end++;
		else if (ms->start == ms->end)
		{
/*
1) few spaces at the end of str: str[end] comes to \0 and handled as delimiter
  -> add \0 condition in if	statement
2) get substr and apply tokenize() on the substr which is delimiter
*/
			if (str[ms->end] != ' ' && str[ms->end] != '\0')
			{
				ms->token = ft_substr(str, ms->start, 1);
				tokenize(&head, ms->token, TK_RESERVED);
				printf("Delimiter A\n");
			}
			ms->start = ++ms->end;
		}
		else
		{
			ms->token = ft_substr(str, ms->start, ms->end - ms->start);
			if (is_builtin(ms->token))
			{
				tokenize(&head, ms->token, TK_BUILTIN);
				printf("Builtin\n");
			}
			else
			{
				tokenize(&head, ms->token, TK_WORD);
				printf("Word\n");
			}
			if (ms->end < ms->len && str[ms->end] != ' ')
			{
/*
get substr and apply tokenize() on the substr which is delimiter
*/
				ms->token = ft_substr(str, ms->end, 1);
				tokenize(&head, ms->token, TK_RESERVED);
				printf("Delimiter B\n");
			}
			ms->start = ++ms->end;
		}
	}
	return (head);
}
