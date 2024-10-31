/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:19:23 by athonda           #+#    #+#             */
/*   Updated: 2024/10/31 19:24:00 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_redirect.c
 * @brief to handle the redirects (<,>,<<,>>)
 * @note
	<redirect_re>	::=		<redirect> <redirect_right>

	<redirect_right>::=		ε
						|	<redirect> <redirect_right>

	<redirect>		::=		'<' <file>
						|	'>' <file>
						|	'<<' <file>
						|	'>>' <file>
 *
 */

#include "minishell.h"

/**
 * @fn parser_redirect_re(t_token *token)
 * @brief iterate redirections
 * @param[in,out]	token address
 * @param[out]		node address
 * @note
	<redirect_re>	::=		<redirect> <redirect_right>

 */

t_node	*parser_redirect_re(t_token **token)
{
	t_node	*node;
	t_node	*right;

	node = parser_redirect(token);
	if (node == NULL)
		return (NULL);
	right = parser_redirect_right(token);
	node->right = right;
	return (node);
}

/**
 * @fn parser_redirect_right(t_token *token)
 * @brief iterate redirections
 * @note
	<redirect_right>::=		ε
						|	<redirect> <redirect_right>
 */

t_node	*parser_redirect_right(t_token **token)
{
	t_node	*node;
	t_node	*right;

	if (!*token || (*token)->kind == TK_EOF)
//	if (token == NULL)
	{
		return (NULL);
	}
	else
	{
		node = parser_redirect(token);
		if (node == NULL)
			return (NULL);
		*token = next_token(*token);
		right = parser_redirect_right(token);
		node->right = right;
	}
	return (node);
}

/**
 * @fn parser_redirect(t_token *token)
 * @brief simply check grammer as redirection symbols and file
 * @note
	<redirect>		::=		'<' <file>
						|	'>' <file>
						|	'<<' <file>
						|	'>>' <file>
 */

t_node	*parser_redirect(t_token **token)
{
	t_node	*node;
	t_node	*right;

//	if ((*token)->str[0] == '<')
	if ((*token)->kind == TK_REDIRECT_IN)
	{
		node = ast_newnode(ND_REDIRECT_IN);
		node->str = (*token)->str;
		*token = (*token)->next;
		if ((*token)->kind != TK_WORD)
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		right = ast_newnode(ND_WORD);
		right->str = (*token)->str;
		node->right = right;
		return (node);
	}
//	else if ((*token)->str[0] == '>')
	else if ((*token)->kind == TK_REDIRECT_OUT)
	{
		node = ast_newnode(ND_REDIRECT_OUT);
		node->str = (*token)->str;
		*token = (*token)->next;
		if ((*token)->kind != TK_WORD)
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		right = ast_newnode(ND_WORD);
		right->str = (*token)->str;
		node->right = right;
		return (node);
	}
//	else if ((*token)->str[0] == '>' && (*token)->str[1] == '>')
	else if ((*token)->kind == TK_REDIRECT_APPEND)
	{
		node = ast_newnode(ND_REDIRECT_APPEND);
		node->str = (*token)->str;
		*token = (*token)->next;
		if ((*token)->kind != TK_WORD)
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		right = ast_newnode(ND_WORD);
		right->str = (*token)->str;
		node->right = right;
		return (node);
	}
//	else if ((*token)->str[0] == '<' && (*token)->str[1] == '<')
	else if ((*token)->kind == TK_REDIRECT_HEREDOC)
	{
		node = ast_newnode(ND_REDIRECT_HEREDOC);
		node->str = (*token)->str;
		*token = (*token)->next;
		if ((*token)->kind != TK_WORD)
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		right = ast_newnode(ND_HEREDOC_DELIMITER);
		right->str = (*token)->str;
		node->right = right;
		return (node);
	}
	ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
	return (NULL);
}
