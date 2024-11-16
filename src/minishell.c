/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/11/16 17:26:02 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_flow(t_ms *ms)
{
	if (*ms->input)
		add_history(ms->input);
	lexer(ms, ms->input);
	free(ms->input);
	if (ms->error)
		return ;
	ms->start_node = parser(&ms->head);
	if (!ms->start_node)
		ms->exit_status = 2;
	if (g_sig)
		ms->exit_status = 128 + g_sig;
	else
		traverse_start(ms->start_node, ms);
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
	t_ms	*ms;
	int		exit_status;

	if (argc != 1)
		return (ft_dprintf(2, "No arguments allowed...\n"), 1);
	(void)argv;
	ms = malloc(sizeof(t_ms));
	if (!ms)
	{
		perror("ms malloc error");
		return (1);
	}
	init(ms, envp);
	loop(ms);
	exit_status = ms->exit_status;
	cleanup_final(ms);
	return (exit_status);
}
