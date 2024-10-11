/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:03:37 by athonda           #+#    #+#             */
/*   Updated: 2024/10/11 20:37:26 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn parse_expr(t_token *token)
 * @brief catch the symboll &&,|| and check the grammer
 * @note
	<expr>			::=  	<pip>
						| 	<pip> '&&' <expr>
						|	<pip> '||' <expr>
 */

t_node	*parse_expr(t_token **token)

{
	t_node	*left;
	t_node	*node;

	left = parse_pip(token);
	if ((*token)->kind == TK_AND)
	{
		node = ast_newnode(ND_AND);
		*token = (*token)->next;
		node->left = left;
		node->right = parse_expr(token);
		node->str = "&&";
		return (node);
	}
	else if ((*token)->kind == TK_OR)
	{
		node = ast_newnode(ND_OR);
		*token = (*token)->next;
		node->left = left;
		node->right = parse_expr(token);
		node->str = "||";
		return (node);
	}
	return (left);
}