/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:12:57 by xlok              #+#    #+#             */
/*   Updated: 2024/11/10 19:00:04 by xlok             ###   ########.fr       */
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

int	syntax_check_parenthesis(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '(')
		{
			i++;
			while (str[i] && str[i] != ')')
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

int	syntax_checker(t_ms *ms, char *str)
{
	if (syntax_check_quote(str) || syntax_check_parenthesis(str))
		ms->error = true;
	return (ms->error);
}
