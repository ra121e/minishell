/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:56 by athonda           #+#    #+#             */
/*   Updated: 2024/10/19 16:43:18 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	exec_cmd(t_node *cur, t_ms *ms)
{
	char	**cmd;
	char	*file_name;
	int		i;

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
				dprintf(1, "redirect file name is %s\n", file_name);
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
			cmd[0] = cur->str;
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
						file_name = cur->right->str;
						dprintf(1, "redirect file name is %s\n", file_name);
						ms->fd = open("file_name", O_RDONLY); // make file here
						cur = cur->right;
					}
				}
				else
				{
					cmd[i++] = cur->str;
				}
			}
			cmd[i] = NULL;
		}
		cur = cur->right;
	}
}
