/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:28 by xlok              #+#    #+#             */
/*   Updated: 2024/10/13 19:48:00 by xlok             ###   ########.fr       */
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

void	init(t_ms *ms)
{
	ms->head = 0;
	ms->start = 0;
	ms->end = 0;
	ms->key = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		*prompt;
	t_ms		*ms;
	t_token		*tokens;
	t_node		*node;

	if (argc != 1)
		return (ft_dprintf(2, "No arguments allowed...\n"), 1);
	(void)argv;
	ms = malloc(sizeof(t_ms));
	if (!ms)
		perror("ms malloc error");//malloc protection
	init_env(ms, envp);
	prompt = ft_strjoin(ft_strjoin(getvar(ms, "USER"), "@"), "minishell:$");
	prompt = ft_strjoin(ft_strjoin("\001\033[35m\002", prompt), "\001\033[0m\002");
	if (!prompt)
		perror("prompt malloc error");//malloc protection
	while (1)
	{
		init(ms);
		input = readline(prompt);
		if (!input)
			break ;
		else if (*input)
		{
			add_history(input);
			lexer(ms, input);
//=====test b_env() & b_export()======
			if (!ft_strncmp(input, "env", 4))
				b_env(ms->envp);
			else if (!ft_strncmp(input, "export", 6))
				b_export(ms, input + 7);
////=====test b_env() & b_export()======
		}
		free(input);
		tokens = ms->head;
		print_token(ms);
		node = parser(&tokens);
		printAST(node, 0, 0);
	}
	free(prompt);
	free(ms);
}
