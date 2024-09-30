/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:14:02 by xlok              #+#    #+#             */
/*   Updated: 2024/10/10 21:57:38 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_quote(t_ms *ms, char *str, char c)
{
	ms->start = ++ms->end;
	while (str[ms->end] && str[ms->end] != c)
	{
		if (!str[ms->end])
		{
			ft_dprintf(2, "Syntax error\n");
			ms->start = ++ms->end;
			return ;//should free & exit
		}
		else if (str[ms->end] == c)
			break ;
		else if (str[ms->end] == '$')
		{
			lexer_word(ms, str);
			lexer_var(ms, str);
			if (str[ms->end] == c)
				ms->start = ms->end + 1;
		}
		ms->end++;
	}
//	if (ms->end > ms->start)
//		lexer_word(ms, str);
//	ms->end++;
}

void	lexer_quote(t_ms *ms, char *str)
{
	if (str[ms->end] == '\'')
		tokenize_quote(ms, str, '\'');
	else
		tokenize_quote(ms, str, '\"');
}
