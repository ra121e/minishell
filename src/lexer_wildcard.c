/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:55:28 by xlok              #+#    #+#             */
/*   Updated: 2024/10/12 20:27:27 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_wildcard(t_ms *ms, char *str)
{
	if (ms->start != ms->end)
	{
		tokenize_word(ms, str, TK_WORD);
		ms->start = --ms->end;
	}
	ms->token = ft_substr(str, ms->start, 1);
	if (!ms->token)
		perror("token malloc error");//malloc protection
	tokenize(ms, TK_WILDCARD);
	ms->start = ++ms->end;
}
