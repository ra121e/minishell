/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:09:44 by athonda           #+#    #+#             */
/*   Updated: 2024/10/14 19:15:50 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void	handler1(int signal)
{
	write(1, "Mario!!", 7);
	alarm(1);
	write(1, "8", 1);
	alarm(6);
}

void	handler2(int signal)
{
	write(1, "6", 1);
	write(1, "7", 1);
}

int	main(void)
{
	signal(SIGINT, handler1);
	signal(SIGALRM, handler2);
	write(1, "1", 1);
	write(1, "2", 1);
	write(1, "3", 1);
	write(1, "4", 1);
	alarm(2);
	while (1)
	{

	}
	write(1, "5", 1);
	return (0);
}