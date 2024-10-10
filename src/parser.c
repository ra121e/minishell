/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:11:36 by athonda           #+#    #+#             */
/*   Updated: 2024/10/09 21:24:18 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser.c
 * @brief make AST from token series
 * @param[in]	token
 * @param[out]	node of AST
 */

#include "minishell.h"

/*	BNF
	<expr>			::=  	<pip>
						| 	<pip> '&&' <expr>
						|	<pip> '||' <expr>

	<pip>			::=		<command>
						|	<command> '|' <pip>

	<command>		::=		<command_re>
						|	<subshell>
						|	<subshell> <redirect_re>

	<subshell>		::=		'(' <expr> ')'

	<redirect_re>	::=		<redirect>
						|	<redirect_re> <redirect>

	<redirect>		::=		'<' <file>
						|	'>' <file>
						|	'<<' <file>
						|	'>>' <file>

	<command_re>	::=		<cmd>
						|	<command_re> <cmd>

	<cmd>			::=		<word>
						|	<redirect>

*/

/**
 * @fn parse_expr(t_token *token)
 * @brief catch the symboll &&,|| and check the grammer
 * @note
	<expr>			::=  	<pip>
						| 	<pip> '&&' <expr>
						|	<pip> '||' <expr>
 */

t_node	*parse_expr(t_token *token)

{
	t_node	*left;
	t_node	*node;
	t_token	*next;

	left = parse_pip(token);
	next = next_token(token);
	if (next->kind == TK_AND)
	{
		node = ast_newnode(ND_AND);
		node->left = left;
		node->right = parse_expr(token);
		node->str = "&&";
		return (node);
	}
	else if (next->kind == TK_OR)
	{
		node = ast_newnode(ND_OR);
		node->left = left;
		node->right = parse_expr(token);
		node->str = "||";
		return (node);
	}
	return (left);
}

/**
 * @fn parse_pip(t_token *token)
 * @brief catch the symboll | and check the grammer
 * @note
	<pip>			::=		<command>
						|	<command> '|' <pip>
 */

t_node	*parse_pip(t_token *token)
{
	t_node	*left;
	t_node	*node;
	t_token	*next;

	left = parse_command(token);
	next = next_token(token);
	if (next->kind == TK_PIPE)
	{
		node = ast_newnode(ND_PIPE);
		node->left = left;
		node->right = parse_pip(token);
		node->str = "|";
		return (node);
	}
	return (left);
}

/**
 * @fn parse_command(t_token *token)
 * @brief just junction to simple command and subshell "(....)"
 * @note
	<command>		::=		<command_re>
						|	<subshell>
						|	<subshell> <redirect_re>
 */

t_node	*parse_command(t_token *token)
{
	t_node	*node;
	t_token	*next;

	if (token == NULL)
		return (NULL);
	if (token->kind == TK_LPAREN)
	{
		node = parse_subshell(token);
		next = next_token(token);
		if (next->kind == TK_REDIRECTION)
		{
			node = parse_redirect(token);
		}
	}
	else
	{
		node = parse_command_re(token);
	}
	return (node);
}

/**
 * @fn parse_subshell(t_token *token)
 * @brief check the grammer parenthesis expr parenthesis
 * @note
	<subshell>		::=		'(' <expr> ')'
 */

t_node	*parse_subshell(t_token *token)
{
	t_node	*expr_node;
	t_node	*node;
	t_token	*next;

	next = next_token(token);
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
	next = next_token(token);
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

/**
 * @fn parse_redirect_re(t_token *token)
 * @brief iterate redirections
 * @note
	<redirect_re>	::=		<redirect>
						|	<redirect_re> <redirect>

	<redirect>		::=		'<' <file>
						|	'>' <file>
						|	'<<' <file>
						|	'>>' <file>
 */

t_node	*parse_redirect_re(t_token *token)
{
	t_token	*next;
	t_node	*node;

	next = next_token(token);
	if (next->kind == TK_REDIRECTION)
	{
		parse_redirect_re(token);
	}
	node = parse_redirect(token);
	return (node);
}

/**
 * @fn parse_redirect(t_token *token)
 * @brief simply check grammer as redirection symbols and file
 * @note
	<redirect>		::=		'<' <file>
						|	'>' <file>
						|	'<<' <file>
						|	'>>' <file>
 */

t_node	*parse_redirect(t_token *token)
{
	t_node	*node;

	if (token->str[0] == '<')
	{
		node = ast_newnode(ND_REDIRECT_IN);
		node->str = "<";
		return (node);
	}
	else if (token->str[0] == '>')
	{
		node = ast_newnode(ND_REDIRECT_OUT);
		node->str = ">";
		return (node);
	}
	else if (token->str[0] == '>' && token->str[1] == '>')
	{
		node = ast_newnode(ND_REDIRECT_APPEND);
		node->str = ">>";
		return (node);
	}
	else if (token->str[0] == '<' && token->str[1] == '<')
	{
		node = ast_newnode(ND_REDIRECT_HEREDOC);
		node->str = "<<";
		return (node);
	}
	ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
	return (NULL);
}

/**
 * @fn parse_comand_re(t_token *token)
 * @brief iterate word(argument for command) and redirection
 * @note
	<command_re>	::=		<cmd>
						|	<command_re> <cmd>
 */

t_node	*parse_command_re(t_token *token)
{
	t_token	*next;
	t_node	*node;

	next = next_token(token);
	if (next->kind == TK_WORD || next->kind == TK_REDIRECTION)
	{
		parse_command_re(token);
	}
	else
	{
		node = parse_cmd(token);
	}
	return (node);
}

/**
 * @fn parse_cmd(t_token *token)
 * @brief to check redirect and command name
 * @note
	<cmd>			::=		<word>
						|	<redirect>
 */

t_node	*parse_cmd(t_token *token)
{
	t_node	*node;

	if (token->kind == TK_REDIRECTION)
	{
		node = parse_redirect(token);
	}
	else
	{
		node = ast_newnode(ND_COMMAND);
		node->str = token->str;
	}
	return (node);
}

/*
t_node	*parse_cmd2(t_token *token)
{
	t_node	*node;
	t_token	*next;

	node = ast_newnode(ND_COMMAND);
	if (token->kind != TK_WORD)
	{
		ft_dprintf(2, "Syntax error: need command\n");
		exit(1);
	}
	node->cmd_name = ft_strdup(token->str);
	next = next_token(token);
	while (next->kind == TK_WORD)
	{

	}
}
*/