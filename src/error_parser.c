/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:17:10 by athonda           #+#    #+#             */
/*   Updated: 2024/11/15 19:54:58 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_error_and_or(t_token *token)
{
	if (token->kind == TK_AND)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `&&'\n", 2);
		return (1);
	}
	else if (token->kind == TK_OR)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
		return (1);
	}
	else
		return (0);
}

int	is_error_eof(t_token *token)
{
	if (token->kind == TK_EOF)
	{
		ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
		return (1);
	}
	return (0);
}

int	is_error_and_or_eof(t_token *token, t_node **node)
{
	if (token->kind == TK_AND)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `&&'\n", 2);
		(*node)->error = true;
		return (1);
	}
	else if (token->kind == TK_OR)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
		(*node)->error = true;
		return (1);
	}
	else if (token->kind == TK_EOF)
	{
		ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
		(*node)->error = true;
		return (1);
	}
	else
		return (0);
}

int	is_error_pipe_eof(t_token *token, t_node **node)
{
	if (token->kind == TK_PIPE)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		(*node)->error = true;
		return (1);
	}
	else if (token->kind == TK_EOF)
	{
		ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
		(*node)->error = true;
		return (1);
	}
	else
		return (0);
}

int	is_error_pipe(t_token *token)
{
	if (token->kind == TK_PIPE)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}
