/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:18:17 by athonda           #+#    #+#             */
/*   Updated: 2024/10/18 22:19:54 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn parser_subshell(t_token *token)
 * @brief check the grammer parenthesis expr parenthesis
 * @note
	<subshell>		::=		'(' <expr> ')'
 */

t_node	*parser_subshell(t_token **token)
{
	//t_node	*expr_node;
	t_node	*node;

	if ((*token)->kind != TK_LPAREN)
	{
		ft_dprintf(2, "Syntax error: expected '('\n");
		return (NULL);
	}
	if ((*token)->next->kind != TK_WORD)
	{
		ft_dprintf(2, "Syntax error: invalid expression inside '()'\n");
		return (NULL);
	}
	(*token) = (*token)->next;
	node = parser_expr(token);
	if (node == NULL)
	{
		ft_dprintf(2, "Syntax error: invalid expression inside '()'\n");
		return (NULL);
	}
	if ((*token)->kind != TK_RPAREN)
	{
		ft_dprintf(2, "Syntax error: expected ')'\n");
		return (NULL);
	}
	//node = ast_newnode(ND_SUBSHELL);
	//*token = (*token)->next;
	//node->left = expr_node;
	//node->str = "()";
	return (node);
}
