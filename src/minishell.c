/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/10/19 16:54:12 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_sig;

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

void	strjoin_loop(t_ms *ms, char *str)
{
	char	*tmp;

	tmp = ms->prompt;
	if (!tmp)
		tmp = ft_strdup("");
	ms->prompt = ft_strjoin(tmp, str); 
	if (!ms->prompt)
		perror("ms->prompt malloc error");//malloc protection
	free(tmp);
}

void	get_prompt(t_ms *ms)
{
	ms->prompt = 0;
	strjoin_loop(ms, "\001\033[35m\002");
	strjoin_loop(ms, getvar(ms, "USER"));
	strjoin_loop(ms, "@");
	strjoin_loop(ms, "minishell:$");
	strjoin_loop(ms, "\001\033[0m\002");
}

void	init(t_ms *ms)
{
	ms->head = 0;
	ms->start = 0;
	ms->len = 0;
	ms->end = 0;
	ms->key = 0;
	get_prompt(ms);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_ms		*ms;
	t_token		*tokens;
	t_node		*node;

	if (argc != 1)
		return (ft_dprintf(2, "No arguments allowed...\n"), 1);
	(void)argv;
//	ft_signal();
	ms = malloc(sizeof(t_ms));
	if (!ms)
		perror("ms malloc error");//malloc protection
	init_env(ms, envp);
	while (1)
	{
		init(ms);
		input = readline(ms->prompt);
		if (!input)
			break ;
		else if (*input)
		{
			add_history(input);
			lexer(ms, input);
		}
		free(input);
		tokens = ms->head;
		print_token(ms);
		node = parser(&tokens);
		printAST(node, 0, 0);
//TODO:free tokens here or in init()
	}
	free(ms->prompt);
	free(ms);
}
