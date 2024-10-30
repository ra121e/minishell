/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/10/31 00:08:37 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms		*ms;

	if (argc != 1)
		return (ft_dprintf(2, "No arguments allowed...\n"), 1);
	(void)argv;
	ft_signal();
	ms = malloc(sizeof(t_ms));
	if (!ms)
		perror("ms malloc error");//malloc protection
	init_envp(ms, envp);
	while (1)
	{
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
		expansion(ms, ms->start_node);
		traverse_start(ms->start_node, ms, INFO);
		if (!ms->sig)
			traverse_start(ms->start_node, ms, EXECUTE);
//		cleanup(ms);
	}
	cleanup_final(ms);
}
