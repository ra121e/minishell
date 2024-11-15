/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:16:23 by athonda           #+#    #+#             */
/*   Updated: 2024/11/15 20:00:29 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn parser_pip(t_token *token)
 * @brief catch the symboll | and check the grammer
 * @note
	<pip>			::=		<command>
						|	<command> '|' <pip>

	<pip>			::=	<command> ('|' <command>)*
 */

t_node	*parser_pip(t_token **token)
{
	t_node	*left;
	t_node	*node;

	if (is_error_pipe(*token))
		return (NULL);
	left = parser_command(token);
	if (left == NULL || left->error == true)
		return (left);
	while (1)
	{
		if ((*token)->kind == TK_PIPE)
			node = ast_newnode(ND_PIPE);
		else
			return (left);
		if (ast_set_str_left(node, token, left) == 0)
			return (left);
		if (is_error_pipe_eof(*token, &node))
			return (node);
		node->right = parser_expr(token);
		if (node->right == NULL || node->right->error == true)
			node->error = true;
		left = node;
	}
}
