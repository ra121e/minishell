/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:03:37 by athonda           #+#    #+#             */
/*   Updated: 2024/11/07 18:50:28 by xlok             ###   ########.fr       */
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

	if (is_error_and_or(*token))
		return (NULL);
	left = parser_pip(token);
	if (left == NULL)
		return (NULL);
	while (1)
	{
		if ((*token)->kind == TK_AND)
			node = ast_newnode(ND_AND);
		else if ((*token)->kind == TK_OR)
			node = ast_newnode(ND_OR);
		else
			return (left);
		ast_set_str_left(node, token, left);
		if (is_error_eof(*token) || is_error_and_or(*token)) {
			ast_free(node);
			return (NULL);
		}
		node->right = parser_pip(token);
		if (node->right == NULL)
			return (NULL);
		left = node;
	}
}
