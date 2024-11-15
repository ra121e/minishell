/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:14:00 by xlok              #+#    #+#             */
/*   Updated: 2024/11/06 08:14:14 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char *str)
{
	free(str);
	str = 0;
}

void	free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
	str = 0;
}

void	free_token(t_ms *ms)
{
	t_token	*tmp;

	while (ms->head)
	{
		tmp = ms->head;
		if (ms->head->str)
			free(ms->head->str);
		ms->head = ms->head->next;
		free(tmp);
	}
}
