/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:18:17 by athonda           #+#    #+#             */
/*   Updated: 2024/10/11 10:26:18 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn parse_subshell(t_token *token)
 * @brief check the grammer parenthesis expr parenthesis
 * @note
	<subshell>		::=		'(' <expr> ')'
 */

t_node	*parse_subshell(t_token **token)
{
	t_node	*expr_node;
	t_node	*node;
	t_token	*next;

	next = next_token(*token);
	if (next->kind != TK_LPAREN)
	{
		ft_dprintf(2, "Syntax error: expected '('\n");
		return (NULL);
	}
	expr_node = parse_expr(token);
	if (expr_node == NULL)
	{
		ft_dprintf(2, "Syntax error: invalid expression inside '()'\n");
		return (NULL);
	}
	next = next_token(*token);
	if (next->kind != TK_RPAREN)
	{
		ft_dprintf(2, "Syntax error: expected ')'\n");
		return (NULL);
	}
	node = ast_newnode(ND_SUBSHELL);
	node->left = expr_node;
	node->str = "()";
	return (node);
}