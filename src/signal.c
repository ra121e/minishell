/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:25:44 by xlok              #+#    #+#             */
/*   Updated: 2024/10/20 17:14:11 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig;

void	handler(int signum)
{
	sig = signum;
	if (sig == SIGQUIT)
	{
//		write(1, "\n", 1);
		rl_on_new_line();
//		rl_replace_line("", 0);
		rl_redisplay();
//		return ;
	}
	else if (sig == SIGINT)
		write(1, "SIGINT\n", 7);
//		code;

//	rl_on_new_line();
//	rl_replace_line("hello", 0);
//	rl_redisplay();
}

void	ft_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
//	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	signal(SIGQUIT, SIG_IGN);
//	if (sigaction(SIGQUIT, &sa, 0) == -1)
//		perror("signal handler error");//
//	if (sigaction(SIGINT, &sa, 0) == -1)
//		perror("signal handler error");//
}
