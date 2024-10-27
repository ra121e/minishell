/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:19:55 by xlok              #+#    #+#             */
/*   Updated: 2024/10/27 11:55:24 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_ms *ms)
{
	ms->head = 0;
	ms->start = 0;
	ms->len = 0;
	ms->end = 0;
	ms->key = 0;
	ms->heredoc_tmp = 0;
	ms->fd_r = 0;
	ms->pid = 0;
	ms->prompt = ft_strsjoin(5, "\001\033[35m\002", get_var(ms, "USER"), \
			"@", "minishell:$", "\001\033[0m\002");
	if (!ms->prompt)
		perror("ms->prompt malloc error");//malloc protection
}
