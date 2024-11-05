/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/11/05 07:53:43 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_flow(t_ms *ms)
{
	add_history(ms->input);
	lexer(ms, ms->input);
	free(ms->input);
	ms->start_node = parser(&ms->head);
	if (ms->start_node == NULL)
		return ;
	traverse_start(ms->start_node, ms, HEREDOC);
	if (g_sig)
		ms->exit_status = 128 + g_sig;
	else
		traverse_start(ms->start_node, ms, EXECUTE);
}

static void	loop(t_ms *ms)
{
	while (1)
	{
		init_loop(ms);
		ft_signal();
		ms->input = readline(ms->prompt);
		if (g_sig)
		{
			ms->exit_status = 128 + g_sig;
			continue ;
		}
		if (!ms->input)
		{
			ft_dprintf(2, "exit\n");
			break ;
		}
		else
			process_flow(ms);
		cleanup(ms);
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
	init(ms, envp);
	loop(ms);
	cleanup_final(ms);
}
