/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:17:10 by athonda           #+#    #+#             */
/*   Updated: 2024/11/04 19:16:15 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_and(void)
{
	ft_putstr_fd("bash: syntax error near unexpected token `&&'\n", 2);
}

void	error_or(void)
{
	ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
}

int	is_error_and_or(t_token *token)
{
	if (token->kind == TK_AND)
	{
		error_and();
		return (1);
	}
	else if (token->kind == TK_OR)
	{
		error_or();
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

int	is_error_pipe(t_token *token)
{
	if (token->kind == TK_PIPE)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

/*
void	error_expr(t_token *token)
{
	if (token->kind == TK_AND)
		ft_putstr_fd("bash: syntax error near unexpected token `&&'\n", 2);
	else if (token->kind == TK_OR)
		ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
}

void	error_right(t_token *token)
{
	if (token->kind == TK_EOF)
		ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
}

void	error_pip(t_token *token)
{
	if (token->kind == TK_PIPE)
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
}
*/
void	error_subshell(t_token *token)
{
	if (token->kind == TK_PIPE)
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
}