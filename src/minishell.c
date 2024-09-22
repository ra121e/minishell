/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/09/22 19:43:15 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	main()
//{
//	char		*input;
//	char		*prompt;
//	prompt = ft_strjoin(ft_strjoin(getenv("USER"), "@"), ":$");//TODO:free
//	while (1)
//	{
//		input = readline(prompt);
//		if (!input)
//			break ;
//		else if (*input)
//			add_history(input);
//		free(input);
//	}
//=========================TODO: REMOVE========================================
//readline handles the up/down arrows to scroll through the in-memory
//history list so there's no need to access it using other functions like
//history_list() / history_get() which are forbidden by proj
////	prints history
//	HIST_ENTRY	**history;
//	int			i;
//
//	history = history_list();
//	i = -1;
//	while (history[++i])
//		printf("%s\n", history[i]->line);
//=========================TODO: REMOVE========================================
//}

//test lexer
int	main()
{
	lexer("4+ 2 -100 + 100 =42 < cat |echo dd");
	printf("pwd: %s\n", pwd());
}
