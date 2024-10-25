/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:05:57 by xlok              #+#    #+#             */
/*   Updated: 2024/10/25 21:59:16 by xlok             ###   ########.fr       */
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

void	get_newlen(t_ms *ms, char *str, int i)
{
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				ms->len++;
		}
		else if (str[i] == '\"')
		{
			while (str[++i] != '\"')
			{
				if (str[i] == '$')
					i = get_new_len_found_var(ms, str, i);
				else
					ms->len++;
			}
		}
		else if (str[i] == '$')
			i = get_new_len_found_var(ms, str, i);
		else
			ms->len++;
	}
}

int	expand_var_found_var(t_ms *ms, char *str, int i, int quote)
{
	ms->start = ++i;
	while (str[i] == '_' || ft_isalnum(str[i]))
		i++;
	if (i == ms->start)
	{
		ms->new_str[ms->n++] = '$';
		return (--i);
	}
	ms->var = ft_substr(str, ms->start, i - ms->start);
	if (!ms->var)
		perror("ms->var malloc error\n");
	ms->var_value = get_var(ms, ms->var);
	free(ms->var);
	if (ms->var_value)
	{
		ms->end = 0;
		while (ms->var_value[ms->end])
			ms->new_str[ms->n++] = ms->var_value[ms->end++];
		if (!quote)
			ms->expand_var = 1;
	}
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
	get_newlen(ms, cur->str, -1);
	ms->new_str = malloc(ms->len + 1);
	if (!ms->new_str)
		perror("ms->new_str malloc error\n");//malloc protection
	expand_var(ms, cur->str, -1);
	tmp = cur->str;
	cur->str = ms->new_str;
	free(tmp);
	cur = cur->right;
}
