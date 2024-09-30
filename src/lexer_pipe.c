/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:26:33 by xlok              #+#    #+#             */
/*   Updated: 2024/09/28 19:36:59 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_pipe(t_ms *ms, char *str, t_token **head)
{
	if (ms->start != ms->end)
	{
		ms->token = ft_substr(str, ms->start, ms->end - ms->start);
		if (!ms->token)
			perror("token malloc error");//malloc protection
		if (is_builtin(ms->token))
			tokenize(head, ms->token, TK_BUILTIN);
		else
			tokenize(head, ms->token, TK_WORD);
		ms->start = ms->end;
	}
	ms->token = ft_substr(str, ms->start, 1);
	if (!ms->token)
		perror("token malloc error");//malloc protection
	tokenize(head, ms->token, TK_PIPE);
	ms->start = ++ms->end;


/*
//TODO:|| and && for bonus??
	if ((str[ms->end] == '<' && str[ms->end + 1] != '<') || \
			(str[ms->end] == '>' && str[ms->end + 1] != '>'))
	{
		ms->token = ft_substr(str, ms->start, 1);
		if (!ms->token)
			perror("token malloc error");//malloc protection
		tokenize(head, ms->token, TK_REDIRECTION);
		ms->start = ++ms->end;
	}
	else if ((str[ms->end] == '<' && str[ms->end + 1] == '<') || \
		(str[ms->end] == '>' && str[ms->end + 1] == '>'))
	{
		ms->token = ft_substr(str, ms->start, 2);
		if (!ms->token)
			perror("token malloc error");//malloc protection
		tokenize(head, ms->token, TK_REDIRECTION);
		ms->end += 2;
		ms->start = ms->end;
	}
*/
}
