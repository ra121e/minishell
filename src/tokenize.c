/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:14:07 by athonda           #+#    #+#             */
/*   Updated: 2024/09/28 19:39:39 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenize.c
 * @brief make token from prompt text
 */

#include "minishell.h"

char	*token_kind(int k)
{
	if (k == TK_REDIRECTION)
		return ("redirection");
	else if (k == TK_PIPE)
		return ("pipe");
	else if (k == TK_WORD)
		return ("word");
	else if (k == TK_RESERVED)
		return ("reserved");
	else if (k == TK_BUILTIN)
		return ("builtin");
	else if (k == TK_NUM)
		return ("num");
	return (0);
}

void	tokenize(t_token **head, char *p, t_token_kind kind)
{
	t_token	*cur;

	cur = new_token(p, kind);
	printf("\033[31mtoken: \033[0m%s, \033[34mkind: \033[0m%s\n", \
			cur->str, token_kind(kind));
	add_back(head, cur);
	return ;
}
