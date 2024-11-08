/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:49:37 by xlok              #+#    #+#             */
/*   Updated: 2024/11/08 19:54:44 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_new_len_found_var(t_ms *ms, char *str, int i)
{
	ms->start = ++i;
	while (str[i] == '_' || ft_isalnum(str[i]))
		i++;
	if (i == ms->start)
		return (--i);
	ms->var = ft_substr(str, ms->start, i - ms->start);
	if (!ms->var)
		perror("ms->var malloc error\n");
	ms->len += get_var_len(ms, ms->var);
	free(ms->var);
	return (--i);
}

void	get_new_len(t_ms *ms, char *str, int i)
{
	while (str[++i])
	{
		if (str[i] == '$')
			i = get_new_len_found_var(ms, str, i);
		else
			ms->len++;
	}
}
