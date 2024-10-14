/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:14:07 by athonda           #+#    #+#             */
/*   Updated: 2024/10/14 22:44:49 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenize.c
 * @brief make token from prompt text
 */

#include "minishell.h"

int	operator_char_count(char *str, int i)
{
	if (str[i] == '&' && str[i + 1] == '&')
		return (21);
	else if (str[i] == '|' && str[i + 1] == '|')
		return (22);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (23);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (24);
	else if (str[i] == '|')
		return (11);
	else if (str[i] == '<')
		return (12);
	else if (str[i] == '>')
		return (13);
	else if (str[i] == '(')
		return (14);
	else if (str[i] == ')')
		return (15);
	else
		return (0);
}

void	tokenize_prior_str(t_ms *ms)
{
	if (operator_char_count(ms->str, ms->start) == 21)
		tokenize_word(ms, ms->str, TK_AND);
	else if (operator_char_count(ms->str, ms->start) == 22)
		tokenize_word(ms, ms->str, TK_OR);
	else if (operator_char_count(ms->str, ms->start) == 23)
		tokenize_word(ms, ms->str, TK_REDIRECT_HEREDOC);
	else if (operator_char_count(ms->str, ms->start) == 24)
		tokenize_word(ms, ms->str, TK_REDIRECT_APPEND);
	else if (operator_char_count(ms->str, ms->start) == 11)
		tokenize_word(ms, ms->str, TK_PIPE);
	else if (operator_char_count(ms->str, ms->start) == 12)
		tokenize_word(ms, ms->str, TK_REDIRECT_IN);
	else if (operator_char_count(ms->str, ms->start) == 13)
		tokenize_word(ms, ms->str, TK_REDIRECT_OUT);
	else if (operator_char_count(ms->str, ms->start) == 14)
		tokenize_word(ms, ms->str, TK_LPAREN);
	else if (operator_char_count(ms->str, ms->start) == 15)
		tokenize_word(ms, ms->str, TK_RPAREN);
	else
		tokenize_word(ms, ms->str, TK_WORD);
}

void	tokenize_word(t_ms *ms, char *str, int type)
{
	ms->token = ft_substr(str, ms->start, ms->end - ms->start);
	tokenize(ms, type);
	ms->start = ++ms->end;
}

void	tokenize(t_ms *ms, t_token_kind kind)
{
	t_token	*cur;

	cur = new_token(ms->token, kind);
	printf("\033[31mtoken: \033[0m%s, \033[34mkind: \033[0m%s\n", \
			cur->str, token_kind(kind));
	add_back(&ms->head, cur);
	return ;
}
