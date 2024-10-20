/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:25:44 by xlok              #+#    #+#             */
/*   Updated: 2024/10/20 13:45:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig;

void	handler_quit(int signum)
{
	sig = signum;

//	rl_on_new_line();
//	rl_replace_line("hello", 0);
//	rl_redisplay();
}

void	handler_int(int signum)
{
	sig = signum;

//	rl_on_new_line();
//	rl_replace_line("hello", 0);
//	rl_redisplay();
}

void	ft_signal(void)
{
	signal(SIGQUIT, handler_quit);
//	signal(SIGINT, handler_int);
}
