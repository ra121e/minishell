/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:37:10 by xlok              #+#    #+#             */
/*   Updated: 2024/10/11 08:12:14 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//$? - exit status, $$ - pid, $ - literal
int	is_special(t_ms *ms, char *str, int type)
{
	ms->end++;
	if (str[ms->end] == '?' || str[ms->end] == '$')
	{
		ms->token = ft_substr(str, ms->start, 2);
		if (!ms->token)
			perror("token malloc error");//malloc protection
		tokenize(ms, type);
		ms->start = ++ms->end;
		return (1);
	}
	return (0);
}

void	lexer_var(t_ms *ms, char *str, int type)
{
	if (ms->start != ms->end)
	{
		if (type == TK_VAR_QUOTE)
			lexer_word(ms, str, TK_QUOTE);
		else
			lexer_word(ms, str, TK_WORD);
		ms->start = --ms->end;
	}
	if (is_special(ms, str, type))
		return ;
	while (str[ms->end]	&& (ft_isalnum(str[ms->end]) || str[ms->end] == '_'))
		ms->end++;
	ms->token = ft_substr(str, ms->start, ms->end - ms->start);
	if (!ms->token)
		perror("token malloc error");//malloc protection
	if (ms->end - ms->start == 1)
		tokenize(ms, TK_WORD);
	else
		tokenize(ms, type);
	ms->start = ms->end;
}
