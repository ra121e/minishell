/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:55:28 by xlok              #+#    #+#             */
/*   Updated: 2024/10/12 20:27:27 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parenthesis(t_ms *ms, char *str)
{
	if (ms->start != ms->end)
	{
		tokenize_word(ms, str, TK_WORD);
		ms->start = --ms->end;
	}
	if (str[ms->end] == '(' && !ft_strchr(str + ms->end, ')'))
	{
		ft_dprintf(2, "Syntax error\n");
		ms->start = ++ms->end;
		return ;//should free & exit
	}
	ms->token = ft_substr(str, ms->start, 1);
	if (!ms->token)
		perror("token malloc error");//malloc protection
	if (str[ms->end] == '(')
		tokenize(ms, TK_LPAREN);
	else
		tokenize(ms, TK_RPAREN);
	ms->start = ++ms->end;
}
