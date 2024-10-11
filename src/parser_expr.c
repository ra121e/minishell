/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:03:37 by athonda           #+#    #+#             */
/*   Updated: 2024/10/10 21:41:10 by athonda          ###   ########.fr       */
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
	t_token	*next;

	left = parse_pip(token);
	next = next_token(*token);
	if (next->kind == TK_AND)
	{
		node = ast_newnode(ND_AND);
		node->left = left;
		node->right = parse_expr(token);
		node->str = "&&";
		return (node);
	}
	else if (next->kind == TK_OR)
	{
		node = ast_newnode(ND_OR);
		node->left = left;
		node->right = parse_expr(token);
		node->str = "||";
		return (node);
	}
	return (left);
}