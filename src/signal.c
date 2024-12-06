/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:25:44 by xlok              #+#    #+#             */
/*   Updated: 2024/12/06 17:02:50 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

int	check_rl_done(void)
{
	return (0);
}

void	handler(int signum)
{
	g_sig = signum;
	rl_done = 1;
}
//	write(1, "\n", 1);
//	rl_on_new_line();
//	rl_replace_line("", 1);
//	rl_redisplay();

void	ft_signal(void)
{
	struct sigaction	sa;

	g_sig = 0;
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, 0) == -1)
		perror("signal SIGINT handler error");
	signal(SIGQUIT, SIG_IGN);
}
