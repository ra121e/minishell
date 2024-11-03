/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:25:44 by xlok              #+#    #+#             */
/*   Updated: 2024/11/03 15:39:47 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig;

void	handler(int signum)
{
	sig = signum;
	if (sig == SIGINT)
		rl_done = 1;
}

void	handler_cmd(int signum)
{
	sig = signum;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_dprintf(2, "Quit (core dumped)\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	rl_done = 1;
}

void	handler_heredoc(int signum)
{
	sig = signum;
	if (sig == SIGINT)
		rl_done = 1;
}

void	ft_signal(void)
{
	struct sigaction	sa;

	sig = 0;
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

	sig = 0;
	sa.sa_handler = handler_cmd;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, 0) == -1)
		perror("signal handler error");//
	if (sigaction(SIGQUIT, &sa, 0) == -1)
		perror("signal handler error");//
}

//void	ft_signal_heredoc(void)
//{
//	struct sigaction	sa;
//
//	sig = 0;
//	sa.sa_handler = handler_heredoc;
//	sa.sa_flags = 0;
//	sigemptyset(&sa.sa_mask);
//	if (sigaction(SIGINT, &sa, 0) == -1)
//		perror("signal handler heredoc error");//
//	signal(SIGQUIT, SIG_IGN);
//}
