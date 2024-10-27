/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:17:20 by athonda           #+#    #+#             */
/*   Updated: 2024/10/27 10:30:25 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn parser_command(t_token *token)
 * @brief just junction to simple command and subshell "(....)"
 * @note
	<command>		::=		<cmd_re>
						|	<subshell>
						|	<subshell> <redirect_re>
 */

t_node	*parser_command(t_token **token)
{
	t_node	*node;
//	t_token	*next;
	t_node	*right;

	if (!*token || (*token)->kind == TK_EOF)
//	if (*token == NULL)
		return (NULL);
	if ((*token)->kind == TK_LPAREN)
	{
		node = parser_subshell(token);
		if (!node)
			return (0);
		*token = (*token)->next;
		if ((*token)->kind == TK_REDIRECT_IN || (*token)->kind == TK_REDIRECT_OUT)
		{
			right = parser_redirect_re(token);
			node->right = right;
		}
	}
	else
	{
		node = parser_cmd_re(token);
	}
	return (node);
}

/**
 * @fn parser_cmd_re(t_token *token)
 * @brief iterate word(argument for command) and redirection
 * @note
	<cmd_re>		::=		<cmd> <cmd_right>
 */

t_node	*parser_cmd_re(t_token **token)
{
	t_node	*node;
	t_node	*right;

	node = parser_cmd(token);
	right = parser_cmd_right(token);
	node->right = right;

	return (node);
}

/**
 * @fn parser_comand_right(t_token **token)
 * @brief to eliminate the left recursion
 * @note
	<cmd_right>		::=		ε
						|	<cmd> <cmd_right>
 */

t_node	*parser_cmd_right(t_token **token)
{
	t_node	*node;
	t_node	*right;

	if ((*token)->kind == TK_WORD || (*token)->kind == TK_HEREDOC_DELIMITER \
		|| (*token)->kind == TK_REDIRECT_IN || (*token)->kind == TK_REDIRECT_OUT \
	|| (*token)->kind == TK_REDIRECT_HEREDOC || (*token)->kind == TK_REDIRECT_APPEND)
	{
		node = parser_cmd(token);
		right = parser_cmd_right(token);
		node->right = right;
		return (node);
	}
	else
	{
		return (NULL);
	}
}

/**
 * @fn parser_cmd(t_token *token)
 * @brief to check redirect and command name
 * @note
	<cmd>			::=		<word>
						|	<redirect>
 */

t_node	*parser_cmd(t_token **token)
{
	t_node	*node;

	if ((*token)->kind == TK_REDIRECT_IN || (*token)->kind == TK_REDIRECT_OUT || \
		(*token)->kind == TK_REDIRECT_HEREDOC|| (*token)->kind == TK_REDIRECT_APPEND)
	{
		node = parser_redirect(token);
	}
	else
	{
		if ((*token)->kind == TK_HEREDOC_DELIMITER)
			node = ast_newnode(ND_HEREDOC_DELIMITER);
		else
			node = ast_newnode(ND_COMMAND);
		node->str = (*token)->str;
		*token = (*token)->next;
	}
	return (node);
}
