/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:56 by athonda           #+#    #+#             */
/*   Updated: 2024/10/19 18:09:11 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	init_cmd(t_ms *ms, t_node *cur)
{
	int	i;

	i = 0;
	while (cur)
	{
		i++;
		cur = cur->right;
	}
	ms->cmd = malloc(sizeof(char *) * i + 1);
	if (!ms->cmd)
		perror("");//malloc error
}

void	exec_cmd(t_node *cur, t_ms *ms)
{
	char	*file_name;
	int		i;

	while (cur->kind)
	{
		if (cur->kind == ND_REDIRECT_IN || \
			cur->kind == ND_REDIRECT_OUT || \
			cur->kind == ND_REDIRECT_HEREDOC || \
			cur->kind == ND_REDIRECT_APPEND)
		{
			if (cur->right->kind == ND_COMMAND)
			{
				file_name = malloc(1024);
//						getcwd(file_name, 1024);
				file_name = ft_strjoin(getcwd(file_name, 1024), "/");
				file_name = ft_strjoin(file_name, cur->right->str);
				dprintf(1, "redirect file name is %s\n", file_name);
				ms->fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				dprintf(1, "ms->fd: %d\n", ms->fd);
				close(ms->fd);
				cur = cur->right;
			}
		}
		else
		{
			//if (check_cmd == 0)
			//{
			//	dprintf(2, "needs command\n");
			//	return (NULL);
			//}
			init_cmd(ms, cur);
			ms->cmd[0] = cur->str;
			cur = cur->right;
			i = 1;
			while (cur != NULL)
			{
				if (cur->kind == ND_REDIRECT_IN || \
					cur->kind == ND_REDIRECT_OUT || \
					cur->kind == ND_REDIRECT_HEREDOC ||
					cur->kind == ND_REDIRECT_APPEND)
				{
					if (cur->right->kind == ND_COMMAND)
					{
						file_name = malloc(1024);
//						getcwd(file_name, 1024);
						file_name = ft_strjoin(getcwd(file_name, 1024), "/");
						file_name = ft_strjoin(file_name, cur->right->str);
						dprintf(1, "redirect file name is %s\n", file_name);
						ms->fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
						dprintf(1, "ms->fd: %d\n", ms->fd);
						close(ms->fd);
						cur = cur->right;
					}
				}
				else
				{
					ms->cmd[i++] = cur->str;
				}
				cur = cur->right;
			}
			ms->cmd[i] = NULL;
			break ;
		}
		cur = cur->right;
	}
}
