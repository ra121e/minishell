/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:37:18 by athonda           #+#    #+#             */
/*   Updated: 2024/09/21 19:02:59 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file token.c
 * @brief to operate tokens
 */

#include "minishell.h"

/**
 * @fn void	new_token(char *str)
 * @brief to make new token
 * @param[in] kind: token kind
 * @param[in] str: string of token, like "command" "$"
 * @param[in] now: the end of token chane
 */

t_token	*new_token(t_token_kind kind, char *str, t_token *now)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof (t_token) * 1);
	if (node == NULL)
		return (NULL);
	node->kind = kind;
	node->str = str;
	now->next = node;
	return (node);
}