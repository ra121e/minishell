/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:56:30 by athonda           #+#    #+#             */
/*   Updated: 2024/10/17 10:32:38 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;
	char	*input_heredoc;
	char	*prompt;
	char	*prompt_heredoc;

	prompt = " ";
	input = readline(prompt);
	prompt_heredoc = ">";
	while (1)
	input_heredoc = readline(prompt_heredoc);

	printf("commamnd line: %s\n", input);
	printf("here doc: %s\n", input_heredoc);

	return (0);
}