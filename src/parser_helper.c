/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:54 by athonda           #+#    #+#             */
/*   Updated: 2024/10/13 17:23:49 by xlok             ###   ########.fr       */
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

//bool	consume(t_token *token, char op)
//{
//	if (token->kind != TK_AND || token->kind != TK_OR || token->str[0] != op)
//		return (false);
//	token = token->next;
//	return (true);
//}
