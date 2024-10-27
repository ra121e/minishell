/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:29:46 by athonda           #+#    #+#             */
/*   Updated: 2024/10/27 12:20:21 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_loop(t_ms *ms, char *delimiter, int quote, int len)
{
	char	*input;

	while (1)
	{
		input = readline(">");
		if (!input || !ft_strncmp(input, delimiter, len + 1))
			break ;
		if (quote == 0)
		{
			ms->len = 0;
			ms->expand_var = 0;
			get_new_len(ms, input, -1);
			ms->new_str = malloc(ms->len + 1);
			if (!ms->new_str)
				perror("ms->new_str for heredoc malloc error\n");//malloc protection
			expand_var(ms, input, -1);
			dprintf(ms->fd_r, "%s\n", ms->new_str);
			free(ms->new_str);
		}
		else
			dprintf(ms->fd_r, "%s\n", input);
		free(input);
	}
}

void	heredoc(t_ms *ms, char *delimiter)
{
	int		len;
	int		quote;

	quote = 0;
	if (*delimiter == '\"')
		quote = 1;
	delimiter = remove_quote(delimiter);
	if (ms->fd_r > 2)
		close(ms->fd_r);
	if ((ms->fd_r = open("tmp", WRITE, 0644)) == -1)
		perror("heredoc tmp file open error\n");
	ms->heredoc_tmp = 1;
	len = ft_strlen(delimiter);
	heredoc_loop(ms, delimiter, quote, len);
	close(ms->fd_r);
	ms->fd_r = open("tmp", READ);
	if (!ms->fd_r)
		perror("heredoc open error");
}
