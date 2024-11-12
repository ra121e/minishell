/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:11:36 by athonda           #+#    #+#             */
/*   Updated: 2024/11/12 19:15:57 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parserr.c
 * @brief make AST from token series
 * @param[in]	token
 * @param[out]	node of AST
 */

#include "minishell.h"

/*	BNF
1.	<expr>			::=  	<pip>
						| 	<pip> '&&' <expr>
						|	<pip> '||' <expr>
	EBNF
	<expr>			::=	<pip> ('&&' <pip> | '||' <pip>)*


2.	<pip>			::=		<command>
						|	<command> '|' <pip>
	EBNF
	<pip>			::=	<command> ('|' <command>)*

3.	<command>		::=		<cmd_re>
						|	<subshell>
						|	<subshell> <redirect_re>

4.	<subshell>		::=		'(' <expr> ')'

5.	<redirect_re>	::=		<redirect>
						|	<redirect_re> <redirect>

	<redirect>		::=		'<' <file>
						|	'>' <file>
						|	'<<' <file>
						|	'>>' <file>

6.	<cmd_re>		::=		<cmd>
						|	<cmd_re> <cmd>

	<cmd>			::=		<word>
						|	<redirect>

*	delete the left recursion in redirect_re adn command_re

5.	<redirect_re>	::=		<redirect> <redirect_right>

	<redirect_right>::=		ε
						|	<redirect> <redirect_right>

6.	<cmd_re>		::=		<cmd> <cmd_right>

	<cmd_right>		::=		ε
						|	<cmd> <cmd_right>

*/

t_node	*parser(t_token **token)
{
	t_node	*node;
	t_token	*cur;

	if (!*token || (*token)->kind == TK_EOF)
		return (0);
	node = NULL;
	cur = *token;
	node = parser_expr(&cur);
	if (!node)
		return (NULL);
	if ((node && node->error == true) || \
			(node->left && node->left->error == true) || \
			(node->right && node->right->error == true))
	{
		ast_free(node);
		return (NULL);
	}
	return (node);
}
