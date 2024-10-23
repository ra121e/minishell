/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:12:57 by xlok              #+#    #+#             */
/*   Updated: 2024/10/24 22:33:35 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_check_quote(char *str)
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
				dprintf(2, "Syntax error...no closing quote\n");
				exit(1);//cleanup before exit
			}
		}
	}
}

void	syntax_check_parenthesis(char *str)
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
				dprintf(2, "Syntax error...no closing quote\n");
				exit(1);//cleanup before exit
			}
		}
	}
}

void	syntax_checker(char *str)
{
	syntax_check_quote(str);
	syntax_check_parenthesis(str);
}
