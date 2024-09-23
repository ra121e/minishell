/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/09/23 19:44:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char		*input;
	char		*prompt;
	prompt = ft_strjoin(ft_strjoin(getenv("USER"), "@"), ":$");//TODO:free
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		else if (*input)
		{
			add_history(input);
			lexer(input);
		}
		free(input);
	}
}
