/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:03:37 by athonda           #+#    #+#             */
/*   Updated: 2024/10/12 19:13:50 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn parser_expr(t_token *token)
 * @brief catch the symboll &&,|| and check the grammer
 * @note
	<expr>			::=  	<pip>
						| 	<pip> '&&' <expr>
						|	<pip> '||' <expr>

	<expr>			::=	<pip> ('&&' <pip> | '||' <pip>)*
 */

t_node	*parser_expr(t_token **token)
{
	t_node	*left;
	t_node	*node;

	left = parser_pip(token);
	while (1)
	{
		if ((*token)->kind == TK_AND)
		{
			node = ast_newnode(ND_AND);
			*token = (*token)->next;
			node->left = left;
			node->right = parser_pip(token);
		//	*token = (*token)->next;
			node->str = "&&";
			left = node;
		}
		else if ((*token)->kind == TK_OR)
		{
			node = ast_newnode(ND_OR);
			*token = (*token)->next;
			node->left = left;
			node->right = parser_pip(token);
		//	*token = (*token)->next;
			node->str = "||";
			left = node;
		}
		else
			return (left);
	}
}
/*
t_node	*parser_expr(t_token **token)

{
	t_node	*left;
	t_node	*node;

	left = parser_pip(token);
	if ((*token)->kind == TK_AND)
	{
		node = ast_newnode(ND_AND);
		*token = (*token)->next;
		node->left = left;
		node->right = parser_expr(token);
		*token = (*token)->next;
		node->str = "&&";
		return (node);
	}
	else if ((*token)->kind == TK_OR)
	{
		node = ast_newnode(ND_OR);
		*token = (*token)->next;
		node->left = left;
		node->right = parser_expr(token);
		*token = (*token)->next;
		node->str = "||";
		return (node);
	}
	return (left);
}
*/