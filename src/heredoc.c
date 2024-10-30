/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:29:46 by athonda           #+#    #+#             */
/*   Updated: 2024/10/31 00:07:31 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_if_unquoted(t_ms *ms, char *input, int quote, int fd[2])
{
	if (quote == 0)
	{
		ms->len = 0;
		ms->expand_var = 0;
		get_new_len(ms, input, -1);
		ms->new_str = malloc(ms->len + 1);
		if (!ms->new_str)
			perror("ms->new_str for heredoc malloc error\n");//malloc protection
		expand_var(ms, input, -1);
		dprintf(fd[1], "%s\n", ms->new_str);
		free(ms->new_str);
	}
	else
		dprintf(fd[1], "%s\n", input);
}

void	heredoc_loop(t_ms *ms, char *delimiter, int quote, int fd[2])
{
	char	*input;

	while (1)
	{
		input = readline(">");
		if (sig == 2)
		{
			ms->sig = sig;
			sig = 0;
			break ;
		}
		if (!input)
		{
			dprintf(2, "minishell: warning: here-document delimited \
					by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}	
		else if (!ft_strncmp(input, delimiter, ms->len + 1))
			break ;
		expand_if_unquoted(ms, input, quote, fd);
		free(input);
	}
}

void	heredoc(t_ms *ms, char *delimiter)
{
	int	quote;
	int	fd[2];

	quote = 0;
	if (*delimiter == '\"' || *delimiter == '\'')
		quote = 1;
	delimiter = remove_quote(delimiter);
	if (ms->fd_r > 2)
		close(ms->fd_r);
	if (pipe(fd) == -1)
		perror("pipe error for heredoc");
	ms->len = ft_strlen(delimiter);
	ft_signal_heredoc();
	heredoc_loop(ms, delimiter, quote, fd);
	ft_signal();
	ms->fd_r = fd[0];
	close(fd[1]);
}
