/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:17:20 by athonda           #+#    #+#             */
/*   Updated: 2024/11/13 22:27:22 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn parser_command(t_token *token)
 * @brief just junction to simple command and subshell "(....)"
 * @note subshell does not accept redirect after ')'
	<command>		::=		<cmd_re>
						|	<subshell>
						|	<subshell> <redirect_re> <- no use
 */

t_node	*parser_command(t_token **token)
{
	t_node	*node;

	if (!*token || (*token)->kind == TK_EOF)
		return (NULL);
	if ((*token)->kind == TK_LPAREN || (*token)->kind == TK_RPAREN)
	{
		node = parser_subshell(token);
		if (!node)
			return (0);
		if ((*token)->kind == TK_WORD || (*token)->kind IS_REDIRECT)
		{
			ft_dprintf(2, "Syntax error near unexpected token `)'\n");
			node->error = true;
			return (node);
		}
	}
	else
		node = parser_cmd_re(token);
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
	if (node == NULL)
		return (NULL);
	if (node->kind == ND_REDIRECT_HEREDOC && (*token)->kind == TK_WORD)
		heredoc(node, (*token)->str);
	if (g_sig)
	{
		node->error = true;
		return (node);
	}
	right = parser_cmd_right(token);
	if (right && right->error == true)
		node->error = true;
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

	if ((*token)->kind == TK_WORD || (*token)->kind IS_REDIRECT)
	{
		node = parser_cmd(token);
		if (node == NULL)
			return (NULL);
		if (node->kind == ND_REDIRECT_HEREDOC && (*token)->kind == TK_WORD)
			heredoc(node, (*token)->str);
		if (g_sig)
		{
			node->error = true;
			return (node);
		}
		right = parser_cmd_right(token);
		if (right && right->error == true)
			node->error = true;
		node->right = right;
		return (node);
	}
	else
		return (NULL);
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

	if ((*token)->kind > 100)
		node = parser_redirect(token);
	else
	{
		node = ast_newnode(ND_COMMAND);
		node->str = (*token)->str;
		*token = (*token)->next;
		if ((*token)->kind == TK_LPAREN)
		{
			ft_dprintf(2, "bash: Syntax error near unexpected token `");
			ft_dprintf(2, "%s' \n", (*token)->str);
			node->error = true;
			return (node);
		}
	}
	return (node);
}
