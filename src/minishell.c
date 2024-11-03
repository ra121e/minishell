/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/11/03 17:03:07 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop(t_ms *ms)
{
	while (1)
	{
		init(ms);
		ft_signal();
		ms->input = readline(ms->prompt);
		if (sig)
		{
			ms->exit_status = 128 + sig;
			continue ;
		}
		if (!ms->input)
		{
			ft_dprintf(2, "exit\n");
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
		traverse_start(ms->start_node, ms, HEREDOC);
		if (!sig)
			traverse_start(ms->start_node, ms, EXECUTE);
//		cleanup(ms);
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
	init_envp(ms, envp);
	loop(ms);
	cleanup_final(ms);
}
