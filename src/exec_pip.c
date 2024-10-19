/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:17:59 by athonda           #+#    #+#             */
/*   Updated: 2024/10/18 19:29:57 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_stream(int pipfd[3], char **argv, int argc, int loop)
{
	if (loop == 2)
	{
		pipfd[2] = open(argv[1], O_RDONLY);
		if (pipfd[2] == -1)
		{
			ft_putstr_fd("pipex: ", 2);
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
	}
	else if (loop == (argc - 2))
		pipfd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		error_exit("dup2 error");
	close(pipfd[1]);
	if (dup2(pipfd[2], STDIN_FILENO) < 0)
		error_exit("dup2 error");
	close(pipfd[2]);
	close(pipfd[0]);
}

void	main_stream(int pipfd[3], int argc, int i)
{
	if (i > 2)
		close(pipfd[2]);
	close(pipfd[1]);
	pipfd[2] = pipfd[0];
	if (i >= argc - 2)
		close(pipfd[2]);
}

void	exec_pip()
{
	pid_t	pid;
	int		pipfd[3];
	int		i;
	int		wstatus;

	if (pipe(pipfd) == -1)
		error_exit("pip creation error");
	pid = fork();
	if (pid < 0)
		error_exit("fork error!");
	else if (pid == 0)
	{
		sub_stream(pipfd, argv, argc, i);
		exec_cmd(argv[i], envp);
	}
	else if (pid > 0)
		main_stream(pipfd, argc, i);
	waitpid(pid, &wstatus, 0);
	wait_all();
	return (WEXITSTATUS(wstatus));
}