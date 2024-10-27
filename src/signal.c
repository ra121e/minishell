/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:25:44 by xlok              #+#    #+#             */
/*   Updated: 2024/10/27 19:06:49 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			sig;

void	handler(int signum)
{
	sig = signum;
//	use global sig for new exit status in cases like heredoc
//	dprintf(2, "%d\n", signum + 128);
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handler_heredoc(int signum)
{
	sig = signum;
	if (sig == SIGINT)
	{
//		write(1, "\n", 1);
//		rl_on_new_line();
//		rl_replace_line("", 0);
//		rl_redisplay();
//		write(1, "^C", 2);
		rl_done = 1;
	}
}

void	ft_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
//	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
//	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, 0) == -1)
		perror("signal handler error");//
	signal(SIGQUIT, SIG_IGN);
}

int	check_rl_done(void)
{
	return (0);
}

void	ft_signal_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler_heredoc;
//	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
//	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, 0) == -1)
		perror("signal handler heredoc error");//
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = check_rl_done;
}
