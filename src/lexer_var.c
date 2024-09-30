/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:37:10 by xlok              #+#    #+#             */
/*   Updated: 2024/10/10 21:11:33 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit_status_or_pid(t_ms *ms, char *str)
{
	ms->end++;
	if (str[ms->end] == '?' || str[ms->end] == '$')
	{
		ms->token = ft_substr(str, ms->start, 2);
		if (!ms->token)
			perror("token malloc error");//malloc protection
		tokenize(ms, TK_VAR);
		ms->start = ++ms->end;
		return (1);
	}
	return (0);
}

void	lexer_var(t_ms *ms, char *str)
{
	if (ms->start != ms->end)
	{
		lexer_word(ms, str);
		ms->start = --ms->end;
	}
	if (is_exit_status_or_pid(ms, str))
		return ;
	while (str[ms->end]	&& (ft_isalnum(str[ms->end]) || str[ms->end] == '_'))
		ms->end++;
	ms->token = ft_substr(str, ms->start, ms->end - ms->start);
	if (!ms->token)
		perror("token malloc error");//malloc protection
	tokenize(ms, TK_VAR);
	ms->start = ms->end;
}
