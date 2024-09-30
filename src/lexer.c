/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:36:49 by xlok              #+#    #+#             */
/*   Updated: 2024/09/30 20:17:49 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
//TODO:expand $ inside "" -> tokenize separately
		if (str[ms->end] == '\'' || str[ms->end] == '\"')
			lexer_quote(ms, str, &head);//add str and head to struct ms?
//	Handle redirections
//TODO:AND &&/OR ||/asterisk *
		else if (str[ms->end] == '<' || str[ms->end] == '>')
			lexer_redirection(ms, str, &head);
//	Handle pipes
		else if (str[ms->end] == '|')
			lexer_pipe(ms, str, &head);
//	Handle others
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
				if (str[ms->end] == '|')
					tokenize(&head, ms->token, TK_PIPE);
				else
					tokenize(&head, ms->token, TK_RESERVED);
			}
			ms->start = ++ms->end;
		}
		else
		{
			ms->token = ft_substr(str, ms->start, ms->end - ms->start);
			if (is_builtin(ms->token))
				tokenize(&head, ms->token, TK_BUILTIN);
			else
				tokenize(&head, ms->token, TK_WORD);
			if (ms->end < ms->len && str[ms->end] != ' ')
			{
/*
get substr and apply tokenize() on the substr which is delimiter
*/
				ms->token = ft_substr(str, ms->end, 1);
				if (str[ms->end] == '|')
					tokenize(&head, ms->token, TK_PIPE);
				else
					tokenize(&head, ms->token, TK_RESERVED);
			}
			ms->start = ++ms->end;
		}
	}
	return (head);
}
