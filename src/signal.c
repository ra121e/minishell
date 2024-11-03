/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:25:44 by xlok              #+#    #+#             */
/*   Updated: 2024/11/03 21:11:58 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

void	handler(int signum)
{
	g_sig = signum;
	if (g_sig == SIGINT)
		rl_done = 1;
}

void	handler_cmd(int signum)
{
	g_sig = signum;
	if (g_sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_sig == SIGQUIT)
	{
		ft_dprintf(2, "Quit (core dumped)\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	rl_done = 1;
}

void	ft_signal_non(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal(void)
{
	struct sigaction	sa;

	g_sig = 0;
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, 0) == -1)
		perror("signal handler error");//
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_cmd(void)
{
	struct sigaction	sa;

	g_sig = 0;
	sa.sa_handler = handler_cmd;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, 0) == -1)
		perror("signal handler error");//
	if (sigaction(SIGQUIT, &sa, 0) == -1)
		perror("signal handler error");//
}
