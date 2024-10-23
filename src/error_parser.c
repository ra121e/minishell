/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:17:10 by athonda           #+#    #+#             */
/*   Updated: 2024/10/23 11:00:14 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	error_subshell(t_token *token)
{
	if (token->kind == TK_PIPE)
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
}