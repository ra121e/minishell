/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/09/28 15:45:38 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char		*input;
	char		*prompt;
	t_token		*head;

	prompt = ft_strjoin(ft_strjoin(getenv("USER"), "@"), ":$");
//the following line affects history display due to length calculation
//	prompt = ft_strjoin(ft_strjoin("\033[35m", prompt), "\033[0m");
	if (!prompt)
		perror("prompt malloc error");//malloc protection
	head = 0;
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
//==========Print token(s)==========
		if (head)
		{
			printf("\033[32mtoken(s): \033[0m");
			while (head)
			{
				printf("%s", head->str);
				if (head->next)
					printf("\033[32m -> \033[0m");
				head = head->next;
			}
			printf("\n");
		}
//==========Print token(s)==========
	}
	free(prompt);
}
