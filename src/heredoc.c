/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:29:46 by athonda           #+#    #+#             */
/*   Updated: 2024/10/26 21:44:31 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_ms *ms, char *delimiter)
{
	char	*prompt;
	char	*input;
	int		len;
	int		quote;

	quote = 0;
	if (*delimiter == '\"')
		quote = 1;
	delimiter = remove_quote(delimiter);
	if (ms->fd_r > 2)
		close(ms->fd_r);
	ms->fd_r = open("tmp", WRITE);
	prompt = ">";
	len = ft_strlen(delimiter);
	while (1)
	{
		input = readline(prompt);
		if (!input || !ft_strncmp(input, delimiter, len + 1))
			break ;
		if (quote == 0)
			expand_var(ms, input, -1);
		dprintf(ms->fd_r, "%s\n", input);
		free(input);
	}
	close(ms->fd_r);
	ms->fd_r = open("tmp", READ);
	if (!ms->fd_r)
		perror("heredoc open error");
}