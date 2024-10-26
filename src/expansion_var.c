/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:05:57 by xlok              #+#    #+#             */
/*   Updated: 2024/10/25 22:53:05 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var_replace(t_ms *ms, int quote)
{
	ms->end = 0;
	while (ms->var_value[ms->end])
		ms->new_str[ms->n++] = ms->var_value[ms->end++];
	if (!ft_strncmp(ms->var, "$?", 3))
		free(ms->var_value);
	if (!quote)
		ms->expand_var = 1;
}

int	expand_var_found_var(t_ms *ms, char *str, int i, int quote)
{
	ms->start = ++i;
	if (str[i] == '?')
		i++;
	else
	{
		while (str[i] == '_' || ft_isalnum(str[i]))
			i++;
	}
	if (i == ms->start)
	{
		ms->new_str[ms->n++] = '$';
		return (--i);
	}
	ms->var = ft_substr(str, ms->start, i - ms->start);
	if (!ms->var)
		perror("ms->var malloc error\n");
	ms->var_value = get_var(ms, ms->var);
	if (ms->var_value)
		expand_var_replace(ms, quote);
	free(ms->var);
	return (--i);
}

void	expand_var(t_ms *ms, char *str, int i)
{
	ms->n = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				ms->new_str[ms->n++] = str[i];
		}
		else if (str[i] == '\"')
		{
			while (str[++i] != '\"')
			{
				if (str[i] == '$')
					i = expand_var_found_var(ms, str, i, 1);
				else
					ms->new_str[ms->n++] = str[i];
			}
		}
		else if (str[i] == '$')
			i = expand_var_found_var(ms, str, i, 0);
		else
			ms->new_str[ms->n++] = str[i];
	}
	ms->new_str[ms->n] = 0;
}

void	expansion_var(t_ms *ms, t_node *cur)
{
	char	*tmp;

	ms->len = 0;
	ms->expand_var = 0;
	get_new_len(ms, cur->str, -1);
	ms->new_str = malloc(ms->len + 1);
	if (!ms->new_str)
		perror("ms->new_str malloc error\n");//malloc protection
	expand_var(ms, cur->str, -1);
	tmp = cur->str;
	cur->str = ms->new_str;
	free(tmp);
	cur = cur->right;
}