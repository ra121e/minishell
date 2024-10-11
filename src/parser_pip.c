/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:16:23 by athonda           #+#    #+#             */
/*   Updated: 2024/10/11 20:42:14 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn parse_pip(t_token *token)
 * @brief catch the symboll | and check the grammer
 * @note
	<pip>			::=		<command>
						|	<command> '|' <pip>
 */

t_node	*parse_pip(t_token **token)
{
	t_node	*left;
	t_node	*node;

	left = parse_command(token);
	if ((*token)->kind == TK_PIPE)
	{
		node = ast_newnode(ND_PIPE);
		*token = (*token)->next;
		node->left = left;
		node->right = parse_pip(token);
		node->str = "|";
		return (node);
	}
	return (left);
}