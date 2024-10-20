/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:17:59 by athonda           #+#    #+#             */
/*   Updated: 2024/10/20 18:09:00 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	main_stream(int pipfd[3], int argc, int i)
{
	if (i > 2)
		close(pipfd[2]);
	close(pipfd[1]);
	pipfd[2] = pipfd[0];
	if (i >= argc - 2)
		close(pipfd[2]);
}

int	*exec_pip(t_ms *ms)
{
	int		pipfd[2];

	if (pipe(pipfd) == -1)
		error_exit("pip creation error");
	return (pipfd);
}
