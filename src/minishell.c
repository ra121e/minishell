/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/11/04 21:36:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_flow(t_ms *ms)
{
		add_history(ms->input);
		lexer(ms, ms->input);
		free(ms->input);
//		print_token(ms);
		ms->start_node = parser(&ms->head);
//		printAST(ms->start_node, 0, 0);
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
		init(ms);
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
	init_envp(ms, envp);
	ms->prompt = ft_strsjoin(3, "\001\033[35m\002" \
			, "minishell~Powered by Honda:$", "\001\033[0m\002");
	if (!ms->prompt)
		perror("ms->prompt malloc error");
	loop(ms);
	cleanup_final(ms);
}
