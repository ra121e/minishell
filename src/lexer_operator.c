/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:26:33 by xlok              #+#    #+#             */
/*   Updated: 2024/10/11 08:07:36 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	op_and_or_pipe(t_ms *ms, char *str)
{
	int	type;
	int	len;

	len = 2;
	if (str[ms->end] == '&' && str[ms->end + 1] == '&')
		type = TK_AND;
	else if (str[ms->end] == '|' && str[ms->end + 1] == '|')
		type = TK_OR;
	else
		type = TK_PIPE;
	if (type == TK_PIPE)
		len = 1;
	ms->token = ft_substr(str, ms->start, len);
	if (!ms->token)
		perror("token malloc error");//malloc protection
	tokenize(ms, type);
	ms->end += len;
	ms->start = ms->end;
}

void	lexer_operator(t_ms *ms, char *str)
{
	if (str[ms->end] == '&' && str[ms->end + 1] != '&')
	{
		ms->end++;
		return ;
	}
	else if (ms->start != ms->end)
	{
		lexer_word(ms, str, TK_WORD);
		ms->start = --ms->end;
	}
	op_and_or_pipe(ms, str);
}
//	if (str[ms->end] == '&' && str[ms->end + 1] == '&')
//	{
//		ms->token = ft_substr(str, ms->start, 2);
//		if (!ms->token)
//			perror("token malloc error");//malloc protection
//		tokenize(ms, TK_AND);
//		ms->end++;
//	}
//	else if (str[ms->end] == '|' && str[ms->end + 1] == '|')
//	{
//		ms->token = ft_substr(str, ms->start, 2);
//		if (!ms->token)
//			perror("token malloc error");//malloc protection
//		tokenize(ms, TK_OR);
//		ms->end++;
//	}
//	else
//	{
//		ms->token = ft_substr(str, ms->start, 1);
//		if (!ms->token)
//			perror("token malloc error");//malloc protection
//		tokenize(ms, TK_PIPE);
//	}
//	ms->start = ++ms->end;
