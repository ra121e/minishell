/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:19:23 by athonda           #+#    #+#             */
/*   Updated: 2024/10/13 18:49:20 by xlok             ###   ########.fr       */
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

	if (token == NULL)
	{
		return (NULL);
	}
	else
	{
		node = parser_redirect(token);
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

	if ((*token)->str[0] == '<')
	{
		node = ast_newnode(ND_REDIRECT_IN);
		*token = (*token)->next;
		if ((*token)->kind != TK_WORD && (*token)->kind != TK_QUOTE && \
			(*token)->kind == TK_VAR && (*token)->kind == TK_VAR_QUOTE)
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		right = ast_newnode(ND_WORD);
		right->str = (*token)->str;
		node->right = right;
		node->str = "<";
		return (node);
	}
	else if ((*token)->str[0] == '>')
	{
		node = ast_newnode(ND_REDIRECT_OUT);
		*token = (*token)->next;
		if ((*token)->kind != TK_WORD && (*token)->kind != TK_QUOTE && \
			(*token)->kind == TK_VAR && (*token)->kind == TK_VAR_QUOTE)
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		right = ast_newnode(ND_WORD);
		right->str = (*token)->str;
		node->right = right;
		node->str = ">";
		return (node);
	}
	else if ((*token)->str[0] == '>' && (*token)->str[1] == '>')
	{
		node = ast_newnode(ND_REDIRECT_APPEND);
		*token = (*token)->next;
		if ((*token)->kind != TK_WORD)
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		right = ast_newnode(ND_WORD);
		right->str = (*token)->str;
		node->right = right;
		node->str = ">>";
		return (node);
	}
	else if ((*token)->str[0] == '<' && (*token)->str[1] == '<')
	{
		node = ast_newnode(ND_REDIRECT_HEREDOC);
		*token = (*token)->next;
		if ((*token)->kind != TK_WORD)
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		right = ast_newnode(ND_WORD);
		right->str = (*token)->str;
		node->right = right;
		node->str = "<<";
		return (node);
	}
	ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
	return (NULL);
}
