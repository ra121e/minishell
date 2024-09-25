/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:37:18 by athonda           #+#    #+#             */
/*   Updated: 2024/09/25 16:40:25 by athonda          ###   ########.fr       */
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

t_token	*new_token(char *str, t_token_kind kind)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof (t_token) * 1);
	if (node == NULL)
		return (NULL);
	node->kind = kind;
	node->str = str;
	node->next = NULL;
	return (node);
}


void	add_back(t_token **node, t_token *new)
{
	t_token	*last;

	last = token_last(*node);
	if (last == NULL)
		*node = new;
	else
		last->next = new;
}


t_token	*token_last(t_token *now)
{
	if (now == NULL)
		return (NULL);
	while (now->next != NULL)
		now = now->next;
	return (now);
}