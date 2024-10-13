/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:47:42 by xlok              #+#    #+#             */
/*   Updated: 2024/10/13 15:15:17 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_type(t_ms *ms, char *str)
{
	int	type;

	type = 0;
	if (str[ms->end] == '<' && str[ms->end + 1] != '<')
		type = TK_REDIRECT_IN;
	else if (str[ms->end] == '>' && str[ms->end + 1] != '>')
		type = TK_REDIRECT_OUT;
	else if (str[ms->end] == '<' && str[ms->end + 1] == '<')
		type = TK_REDIRECT_HEREDOC;
	else if (str[ms->end] == '>' && str[ms->end + 1] == '>')
		type = TK_REDIRECT_APPEND;
	return (type);
}

void	lexer_redirection(t_ms *ms, char *str)
{
	int	type;

	if (ms->start != ms->end)
	{
		tokenize_word(ms, str, TK_WORD);
		ms->start = --ms->end;
	}
	type = redirection_type(ms, str);
	if (type == TK_REDIRECT_IN || type == TK_REDIRECT_OUT)
		ms->token = ft_substr(str, ms->start, 1);
	else
		ms->token = ft_substr(str, ms->start, 2);
	if (!ms->token)
		perror("token malloc error");//malloc protection
	tokenize(ms, type);
	if (type == TK_REDIRECT_HEREDOC || type == TK_REDIRECT_APPEND)
		ms->end++;
	ms->start = ++ms->end;
}
