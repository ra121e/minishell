/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:14:02 by xlok              #+#    #+#             */
/*   Updated: 2024/10/11 08:12:38 by xlok             ###   ########.fr       */
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
	lexer_word(ms, str, TK_QUOTE);
	ms->start = ++ms->end;
}

void	tokenize_d_quote(t_ms *ms, char *str, char c)
{
	ms->start = ++ms->end;
	while (1)
	{
		if (str[ms->end] == c)
		{
			if (ms->end > ms->start)
				lexer_word(ms, str, TK_QUOTE);
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
		lexer_word(ms, str, TK_QUOTE);
		ms->start = --ms->end;
	}
	if (str[ms->end] == '\'')
		tokenize_s_quote(ms, str, '\'');
	else
		tokenize_d_quote(ms, str, '\"');
}
