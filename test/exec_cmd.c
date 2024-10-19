/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:56 by athonda           #+#    #+#             */
/*   Updated: 2024/10/19 15:50:29 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	exec_cmd(t_node *cur)
{
	char	*cmd;
	char	*arg;
	char	*file_name;
	int		fd;

	while (!cur)
	{
		if (cur->kind == ND_REDIRECT_IN || \
			cur->kind == ND_REDIRECT_OUT || \
			cur->kind == ND_REDIRECT_HEREDOC || \
			cur->kind == ND_REDIRECT_APPEND)
		{
			if (cur->right->kind == ND_COMMAND)
			{
				file_name = cur->right->str;
				ms->fd = open("file_name", O_RDONLY); // make file here
				dprint(1, "redirect file name is %s\n", file_name);
				cur = cur->right;
			}
		}
		else
		{
			if (check_cmd == 0)
			{
				dprintf(2, "needs command\n");
				return (NULL);
			}
			cmd = cur->str;
			while (cur != NULL)
			{
				if (cur->kind == ND_REDIRECT_IN || \
					cur->kind == ND_REDIRECT_OUT || \
					cur->kind == ND_REDIRECT_HEREDOC ||
					cur->kind == ND_REDIRECT_APPEND)
				{
					if (cur->right->kind == ND_COMMAND)
					{
						file_name = cur->right->str;
						dprint(1, "redirect file name is %s\n", file_name);
						ms->fd = open("file_name", O_RDONLY); // make file here
						cur = cur->right;
					}
				}
				else
			}

		}
		cur = cur->right;
	}
}

int	check_cmd(char	*str)
{
	// TODO: check the str is shell command or not
	return (0);
}