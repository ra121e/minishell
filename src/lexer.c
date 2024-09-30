/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:36:49 by xlok              #+#    #+#             */
/*   Updated: 2024/10/11 08:23:05 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//tokenize prior
void	lexer_word(t_ms *ms, char *str, int type)
{
	ms->token = ft_substr(str, ms->start, ms->end - ms->start);
	tokenize(ms, type);
	ms->start = ++ms->end;
}

//tokenize current char
void	lexer_single(t_ms *ms, char *str)
{
	if (!ft_isspace(str[ms->end]) && str[ms->end])
	{
		ms->token = ft_substr(str, ms->start, 1);
		tokenize(ms, TK_WORD);
	}
	ms->start = ++ms->end;
}

void	lexer(t_ms *ms, char *str)
{
	ms->len = (int)(ft_strlen(str));
	while (ms->end <= ms->len)
	{
		if (str[ms->end] == '\'' || str[ms->end] == '\"')
			lexer_quote(ms, str);
//TODO:Handle asterisk * for current directory
		else if (str[ms->end] == '&' || str[ms->end] == '|')
			lexer_operator(ms, str);
		else if (str[ms->end] == '<' || str[ms->end] == '>')
			lexer_redirection(ms, str);
		else if (str[ms->end] == '(' || str[ms->end] == ')')
			lexer_parenthesis(ms, str);
		else if (str[ms->end] == '$')
			lexer_var(ms, str, TK_VAR);
		else if (!ft_isspace(str[ms->end]) && str[ms->end])
			ms->end++;
		else if (ms->start == ms->end)
			lexer_single(ms, str);
		else
			lexer_word(ms, str, TK_WORD);
	}
}
