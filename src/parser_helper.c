/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:54 by athonda           #+#    #+#             */
/*   Updated: 2024/11/15 19:47:20 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*next_token(t_token *cur)
{
	if (cur == NULL)
		return (NULL);
	cur = cur->next;
	return (cur);
}

t_token	*prev_token(t_token *cur)
{
	if (cur == NULL)
		return (NULL);
	cur = cur->next;
	return (cur);
}
