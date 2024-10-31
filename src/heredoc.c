/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:29:46 by athonda           #+#    #+#             */
/*   Updated: 2024/10/31 16:02:06 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_expand(t_ms *ms, t_node *node)
{
	char	buf[65536];
	char	**buf_split;
	int		i;

	if (*node->str == '\"' || *node->str == '\'')
		return (node->fd_w[0]);
//	close(node->fd_w[0]);
	if (read(node->fd_w[0], buf, sizeof(buf)) == -1)
		perror("read error on heredoc fd");//
	buf_split = ft_split(buf, '\n');
	i = -1;
	while (buf_split[++i])
	{
		ms->len = 0;
		ms->expand_var = 0;
		get_new_len(ms, buf_split[i], -1);
		ms->new_str = malloc(ms->len + 1);
		if (!ms->new_str)
			perror("ms->new_str for heredoc malloc error\n");//malloc protection
		expand_var(ms, buf_split[i], -1);
		ft_dprintf(node->fd_w[1], "%s\n", ms->new_str);
		free(buf_split[i]);
		free(ms->new_str);
	}
	free(buf_split);
	close(node->fd_w[0]);
	return (node->fd_w[0]);
}

void	heredoc_loop(t_node *node, char *delimiter, int fd[2], int len)
{
	char	*input;

	while (1)
	{
		input = readline(">");
		if (sig == 2)
		{
			sig = 0;
			return ;
		}
		if (!input)
		{
			ft_dprintf(2, "minishell: warning: here-document delimited \
					by end-of-file (wanted `%s')\n", delimiter);
			return ;
		}	
		else if (!ft_strncmp(input, delimiter, len + 1))
			return ;
		ft_dprintf(fd[1], "%s\n", input);
		free(input);
	}
	node->fd_w[0] = fd[0];
	node->fd_w[1] = fd[1];
}

void	heredoc(t_node *node, char *delimiter)
{
	int		fd[2];
	int		len;

	if (pipe(fd) == -1)
		perror("pipe error for heredoc");
	delimiter = remove_quote(delimiter);
	len = ft_strlen(delimiter);
	ft_signal_heredoc();
	heredoc_loop(node, delimiter, fd, len);
	ft_signal();
}
