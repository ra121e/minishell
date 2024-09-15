/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/09/15 14:38:57 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char		*input;
	char		*prompt;
	HIST_ENTRY	**history;
	int			i;

	prompt = ft_strjoin(ft_strjoin(getenv("USER"), "@"), ":$");//TODO:free
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		else if (*input)
			add_history(input);
		free(input);
	}
//	prints history
	history = history_list();//TODO:history_list() cannot be used
	i = -1;
	while (history[++i])
		printf("%s\n", history[i]->line);
}
