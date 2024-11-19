/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:12:57 by xlok              #+#    #+#             */
/*   Updated: 2024/11/19 15:48:42 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_check_quote(char *str)
{
	char	c;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
			{
				ft_dprintf(2, "Syntax error...no closing quote\n");
				return (1);
			}
		}
	}
	return (0);
}

static int	error_msg(int in_loop)
{
	if (in_loop)
		ft_dprintf(2, "bash: Syntax error near unexpected token `)'\n");
	else
		ft_dprintf(2, "bash: Syntax error: unexpected end of file\n");
	return (1);
}

int	in_quote(char *str, int i)
{
	char	c;

	c = str[i];
	while (str[++i])
	{
		if (str[i] == c || !str[i])
			break ;
	}
	if (!str[i])
		return (--i);
	return (i);
}

int	syntax_check_parenthesis(char *str)
{
	int	i;
	int	balance;

	balance = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = in_quote(str, i);
		else if (str[i] == '(')
			balance++;
		else if (str[i] == ')')
		{
			balance--;
			if (balance < 0)
				return (error_msg(1));
		}
	}
	if (balance != 0)
		return (error_msg(0));
	return (0);
}

int	syntax_checker(t_ms *ms, char *str)
{
	if (syntax_check_quote(str) || syntax_check_parenthesis(str))
	{
		ms->error = true;
		ms->exit_status = 2;
	}
	return (ms->error);
}
