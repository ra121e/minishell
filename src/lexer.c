/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:36:49 by xlok              #+#    #+#             */
/*   Updated: 2024/10/13 19:37:31 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_ms *ms, char *str)
{
	ms->len = (int)(ft_strlen(str));
	while (ms->end <= ms->len)
	{
		if (str[ms->end] == '\'' || str[ms->end] == '\"')
			lexer_quote(ms, str);
		else if (str[ms->end] == '&' || str[ms->end] == '|')
			lexer_operator(ms, str);
		else if (str[ms->end] == '<' || str[ms->end] == '>')
			lexer_redirection(ms, str);
		else if (str[ms->end] == '(' || str[ms->end] == ')')
			lexer_parenthesis(ms, str);
		else if (str[ms->end] == '*')
			lexer_wildcard(ms, str);
		else if (str[ms->end] == '$')
			lexer_var(ms, str, TK_VAR);
		else if (ft_isspace(str[ms->end]))
			tokenize_char(ms, str, TK_SPACE);
		else if (!ft_isspace(str[ms->end]) && str[ms->end])
			ms->end++;
		else if (ms->start == ms->end)
			tokenize_char(ms, str, TK_WORD);
		else
			tokenize_word(ms, str, TK_WORD);
	}
	ms->token = ft_strdup("");
	tokenize(ms, TK_EOF);
}
