/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:29:46 by athonda           #+#    #+#             */
/*   Updated: 2024/11/03 21:37:15 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_expand_child(t_ms *ms, int fd[2], char *buf)
{
	char	**buf_split;
	int		i;

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
		ft_dprintf(fd[1], "%s\n", ms->new_str);
		free_str(buf_split[i]);
		free_str(ms->new_str);
	}
	free(buf_split);
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

int	heredoc_expand(t_ms *ms, t_node *node)
{
	char	buf[65536];
	int		pid;

	if (ft_strchr(node->right->str, '\'') || ft_strchr(node->right->str, '\"'))
		return (close(node->fd_w[1]), node->fd_w[0]);
	ft_memset(buf, 0, sizeof(buf));
	if (read(node->fd_w[0], buf, sizeof(buf)) == -1)
		perror("read error on heredoc fd");//
	pid = fork();
	if (pid == -1)
		perror("fork error for heredoc_expansion");
	if (!pid)
		heredoc_expand_child(ms, node->fd_w, buf);
	waitpid(pid, 0, 0);
	close(node->fd_w[1]);
	return (node->fd_w[0]);
}

static void	read_loop(char *delimiter, int fd[2], int len)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (g_sig == 2)
			return ;
		if (!input)
		{
			ft_dprintf(2, "minishell: warning: here-document delimited \
					by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}	
		else if (!ft_strncmp(input, delimiter, len + 1))
			break ;
		ft_dprintf(fd[1], "%s\n", input);
		free(input);
	}
	free(input);
}

void	child_loop(t_ms *ms, t_node *cur, int fd[2])
{
	char	*delimiter;

	if (pipe(fd) == -1)
		perror("pipe error for heredoc");
	delimiter = remove_quote(cur->right->str);
	ms->pid = fork();
	if (ms->pid == -1)
		perror("fork error for heredoc");
	ft_signal_non();
	if (!ms->pid)
	{
		ft_signal();
		read_loop(delimiter, fd, ft_strlen(delimiter));
		close(fd[0]);
		close(fd[1]);
		exit(128 + g_sig);
	}
	waitpid(ms->pid, &ms->pid_status, 0);
	ft_signal();
	g_sig = WEXITSTATUS(ms->pid_status) % 128;
	cur->fd_w[0] = fd[0];
	cur->fd_w[1] = fd[1];
	free(delimiter);
}

void	heredoc(t_ms *ms, t_node *cur)
{
	int		fd[2];

	while (cur && cur->kind)
	{
		if (cur->kind == ND_REDIRECT_HEREDOC)
			child_loop(ms, cur, fd);
		cur = cur->right;
	}
}
