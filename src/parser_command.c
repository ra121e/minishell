/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:17:20 by athonda           #+#    #+#             */
/*   Updated: 2024/10/11 22:03:21 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn parse_command(t_token *token)
 * @brief just junction to simple command and subshell "(....)"
 * @note
	<command>		::=		<cmd_re>
						|	<subshell>
						|	<subshell> <redirect_re>
 */

t_node	*parse_command(t_token **token)
{
	t_node	*node;
	t_token	*next;

	if (*token == NULL)
		return (NULL);
	if ((*token)->kind == TK_LPAREN)
	{
		node = parse_subshell(token);
		next = next_token(*token);
		if (next->kind == TK_REDIRECT_IN || next->kind == TK_REDIRECT_OUT)
		{
			node = parse_redirect(token);
		}
	}
	else
	{
		node = parse_cmd_re(token);
	}
	return (node);
}

/**
 * @fn parse_cmd_re(t_token *token)
 * @brief iterate word(argument for command) and redirection
 * @note
	<cmd_re>		::=		<cmd> <cmd_right>
 */

t_node	*parse_cmd_re(t_token **token)
{
	t_node	*node;

	node = parse_cmd(token);
	node = parse_cmd_right(token);

	return (node);
}

/**
 * @fn parse_comand_right(t_token **token)
 * @brief to eliminate the left recursion
 * @note
	<cmd_right>		::=		ε
						|	<cmd> <cmd_right>
 */

t_node	*parse_cmd_right(t_token **token)
{
	t_node	*node;

	if ((*token)->kind == TK_WORD || (*token)->kind == TK_REDIRECT_IN || (*token)->kind == TK_REDIRECT_OUT \
	|| (*token)->kind == TK_REDIRECT_HEREDOC || (*token)->kind == TK_REDIRECT_APPEND)
	{
		node = parse_cmd(token);
		node = parse_cmd_right(token);
		return (node);
	}
	else
	{
		return (NULL);
	}
}

/**
 * @fn parse_cmd(t_token *token)
 * @brief to check redirect and command name
 * @note
	<cmd>			::=		<word>
						|	<redirect>
 */

t_node	*parse_cmd(t_token **token)
{
	t_node	*node;

	if ((*token)->kind == TK_REDIRECT_IN || (*token)->kind == TK_REDIRECT_OUT || \
		(*token)->kind == TK_REDIRECT_HEREDOC|| (*token)->kind == TK_REDIRECT_APPEND)
	{
		node = parse_redirect(token);
	}
	else
	{
		node = ast_newnode(ND_COMMAND);
		node->str = (*token)->str;
		*token = (*token)->next;
	}
	return (node);
}
