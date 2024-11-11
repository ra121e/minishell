/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:29:46 by athonda           #+#    #+#             */
/*   Updated: 2024/11/11 21:30:24 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_expand_loop(t_ms *ms, t_node *node)
{
	int		file_fd;
	char	*delimiter;

	delimiter = node->right->str;
	file_fd = -1;
	if (access(ms->heredoc_filename, F_OK))
	{
		file_fd = open(ms->heredoc_filename, WRITE, 0644);
		if (file_fd == -1)
			perror("minishell");
		if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '\"'))
			ft_dprintf(file_fd, node->heredoc_str);
		else
		{
			expand_var(ms, node->heredoc_str, 1);
			ft_dprintf(file_fd, ms->new_str);
			free_str(ms->new_str);
		}
		close(file_fd);
		file_fd = open(ms->heredoc_filename, READ);
	}
	return (file_fd);
}

int	heredoc_expand(t_ms *ms, t_node *node)
{
	char	*cwd;
	char	*counter;
	int		file_fd;
	int		i;

	if (ms->fd_r > 2)
	{
		close(ms->fd_r);
		unlink(ms->heredoc_filename);
		free(ms->heredoc_filename);
	}
	i = 0;
	while (++i)
	{
		cwd = getcwd(0, 0);
		counter = ft_itoa(i);
		ms->heredoc_filename = ft_strsjoin(3, cwd, "/tmp", counter);
		free(cwd);
		free(counter);
		file_fd = heredoc_expand_loop(ms, node);
		if (file_fd > 2)
			return (file_fd);
	}
	return (-1);
}

char	*read_loop(char *delimiter, int len, char *heredoc_str, char *input)
{
	char	*tmp;

	while (1)
	{
		input = readline("> ");
		if (g_sig == 2)
			break ;
		if (!input)
		{
			ft_dprintf(2, "minishell: warning: here-document delimited ");
			ft_dprintf(2, "by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}	
		else if (!ft_strncmp(input, delimiter, len + 1))
			break ;
		tmp = heredoc_str;
		if (!heredoc_str)
			heredoc_str = ft_strdup(input);
		else
			heredoc_str = ft_strsjoin(3, heredoc_str, "\n", input);
		free(tmp);
		free(input);
	}
	free(input);
	return (heredoc_str);
}

void	heredoc(t_node *cur)
{
	char	*heredoc_str;
	char	*tmp;
	char	*delimiter;

	while (cur && cur->kind)
	{
		if (cur->kind == ND_REDIRECT_HEREDOC)
		{
			delimiter = remove_quote(cur->right->str);
			ft_signal();
			heredoc_str = read_loop(delimiter, ft_strlen(delimiter), 0, 0);
			tmp = heredoc_str;
			if (!heredoc_str)
				heredoc_str = ft_strdup("");
			else
				heredoc_str = ft_strsjoin(2, heredoc_str, "\n");
			free(tmp);
			free(delimiter);
			cur->heredoc_str = heredoc_str;
		}
		cur = cur->right;
	}
}
