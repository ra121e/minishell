/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:14:02 by xlok              #+#    #+#             */
/*   Updated: 2024/10/13 15:14:58 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_s_quote(t_ms *ms, char *str, char c)
{
	ms->start = ++ms->end;
	while (str[ms->end] && str[ms->end] != c)
		ms->end++;
	if (!str[ms->end])
	{
		ft_dprintf(2, "Syntax error\n");
		ms->start = ++ms->end;
		return ;//should free & exit
	}
	tokenize_word(ms, str, TK_QUOTE);
}

void	tokenize_d_quote(t_ms *ms, char *str, char c)
{
	ms->start = ++ms->end;
	while (1)
	{
		if (str[ms->end] == c)
		{
			if (ms->end > ms->start)
				tokenize_word(ms, str, TK_QUOTE);
			else
				ms->start = ++ms->end;
			break ;
		}
		else if (str[ms->end] == '$')
		{
			lexer_var(ms, str, TK_VAR_QUOTE);
			continue ;
		}
		else if (!str[ms->end])
		{
			ft_dprintf(2, "Syntax error\n");
			exit(1);
			ms->start = ++ms->end;
			return ;//should free & exit
		}
		ms->end++;
	}
}

void	lexer_quote(t_ms *ms, char *str)
{
	if (ms->start != ms->end)
	{
		tokenize_word(ms, str, TK_WORD);
		ms->start = --ms->end;
	}
	if (str[ms->end] == '\'')
		tokenize_s_quote(ms, str, '\'');
	else
		tokenize_d_quote(ms, str, '\"');
}
