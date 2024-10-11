/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:19:23 by athonda           #+#    #+#             */
/*   Updated: 2024/10/11 21:26:17 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn parse_redirect_re(t_token *token)
 * @brief iterate redirections
 * @note
	<redirect_re>	::=		<redirect> <redirect_right>

	<redirect_right>::=		ε
						|	<redirect> <redirect_right>

	<redirect>		::=		'<' <file>
						|	'>' <file>
						|	'<<' <file>
						|	'>>' <file>
 */

t_node	*parse_redirect_re(t_token **token)
{
	t_node	*node;

	node = parse_redirect(token);
	node = parse_redirect_right(token);
	return (node);
}

/**
 * @fn parse_redirect_right(t_token *token)
 * @brief iterate redirections
 * @note
	<redirect_right>::=		ε
						|	<redirect> <redirect_right>
 */

t_node	*parse_redirect_right(t_token **token)
{
	t_node	*node;

	if (token == NULL)
	{
		return (NULL);
	}
	else
	{
		parse_redirect(token);
		*token = next_token(*token);
		node = parse_redirect_right(token);
	}
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

t_node	*parse_redirect(t_token **token)
{
	t_node	*node;

	if ((*token)->str[0] == '<')
	{
		node = ast_newnode(ND_REDIRECT_IN);
		*token = (*token)->next;
		if ((*token)->kind != TK_WORD)
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		node->str = "<";
		return (node);
	}
	else if ((*token)->str[0] == '>')
	{
		node = ast_newnode(ND_REDIRECT_OUT);
		*token = (*token)->next;
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		node->str = ">";
		return (node);
	}
	else if ((*token)->str[0] == '>' && (*token)->str[1] == '>')
	{
		node = ast_newnode(ND_REDIRECT_APPEND);
		*token = (*token)->next;
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		node->str = ">>";
		return (node);
	}
	else if ((*token)->str[0] == '<' && (*token)->str[1] == '<')
	{
		node = ast_newnode(ND_REDIRECT_HEREDOC);
		*token = (*token)->next;
		{
			ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
			return (NULL);
		}
		node->str = "<<";
		return (node);
	}
	ft_dprintf(2, "Syntax error: Expected file name after redirect\n");
	return (NULL);
}
