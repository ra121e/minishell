/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */ /*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/10/25 21:49:07 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO:To delete later; test print tokens
void	print_token(t_ms *ms)
{
	if (ms->head)
	{
		printf("\033[32mtoken(s): \033[0m");
		while (ms->head)
		{
			printf("%s", ms->head->str);
			if (ms->head->next)
				printf("\033[32m -> \033[0m");
			ms->head = ms->head->next;
		}
		printf("\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ms		*ms;

	if (argc != 1)
		return (ft_dprintf(2, "No arguments allowed...\n"), 1);
	(void)argv;
	ms = malloc(sizeof(t_ms));
	if (!ms)
		perror("ms malloc error");//malloc protection
	init_env(ms, envp);
	while (1)
	{
		ft_signal();
		init(ms);
		ms->input = readline(ms->prompt);
		if (!ms->input)
		{
			dprintf(2, "exit\n");
			break ;
		}
		else if (!*ms->input)
			continue ;
		else
		{
			add_history(ms->input);
			lexer(ms, ms->input);
		}
		free(ms->input);
//		print_token(ms);
		ms->start_node = parser(&ms->head);
//		printAST(ms->start_node, 0, 0);
		traverse_start(ms->start_node, ms);
	}
	cleanup(ms);
}
