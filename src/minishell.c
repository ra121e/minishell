/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/09/27 18:57:46 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char		*input;
	char		*prompt;
	t_token		*head;
	prompt = ft_strjoin(ft_strjoin(getenv("USER"), "@"), ":$");//TODO:free
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		else if (*input)
		{
			add_history(input);
			head = lexer(input);
		}
		free(input);
//		printf("tokens: %s -> %s -> %s...", head->str, head->next->str, head->next->next->str);
	}
}
