/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:05:57 by xlok              #+#    #+#             */
/*   Updated: 2024/11/29 20:46:47 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	found_var(t_ms *ms, char *str, int i)
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
		error_malloc(ms, "ms->var malloc error\n");
	ms->var_value = get_var(ms, ms->var);
	if (ms->var_value)
		replace_var(ms);
	if (!ft_strncmp(ms->var, "?", 2))
		free(ms->var_value);
	free(ms->var);
	return (--i);
}

void	word_split(t_ms *ms, char *str)
{
	int	i;
	int	j;

	j = ms->n;
	ms->i = found_var(ms, str, ms->i);
	str = ms->new_str;
	i = j - 1;
	while (str[++i])
	{
		if (word_split_delimiter(str[i]))
		{
			if (i && !word_split_delimiter(str[i - 1]))
			{
				add_word_split(ms, str, ms->split_s, i);
				i++;
			}
			while (word_split_delimiter(str[i]))
				i++;
			ms->split_s = i--;
		}
	}
}

static void	add_last_word(t_ms *ms, char *str)
{
	if ((*ms->new_str && ms->split_s < (int)ft_strlen(ms->new_str)) \
			|| ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		add_word_split(ms, ms->new_str, ms->split_s, \
				ft_strlen(ms->new_str));
}

void	expand_var_loop(t_ms *ms, char *str)
{
	while (str[++ms->i])
	{
		if (str[ms->i] == '\'')
		{
			while (str[++ms->i] != '\'')
				ms->new_str[ms->n++] = str[ms->i];
		}
		else if (str[ms->i] == '\"')
		{
			while (str[++ms->i] != '\"')
			{
				if (str[ms->i] == '$')
					ms->i = found_var(ms, str, ms->i);
				else
					ms->new_str[ms->n++] = str[ms->i];
			}
		}
		else if (str[ms->i] == '$' && !ft_strchr(str, '='))
			word_split(ms, str);
		else if (str[ms->i] == '$')
			ms->i = found_var(ms, str, ms->i);
		else
			ms->new_str[ms->n++] = str[ms->i];
	}
	add_last_word(ms, str);
}

void	expand_var(t_ms *ms, char *str, int is_heredoc)
{
	ms->len = 0;
	ms->expand_var = 0;
	get_new_len(ms, str, -1, is_heredoc);
	ms->new_str = ft_calloc(ms->len + 1, 1);
	if (!ms->new_str)
		error_malloc(ms, "ms->new_str malloc error");
	ms->start = 0;
	ms->split_s = 0;
	ms->n = 0;
	ms->i = -1;
	if (is_heredoc)
	{
		while (str[++ms->i])
		{
			if (str[ms->i] == '$')
				ms->i = found_var(ms, str, ms->i);
			else
				ms->new_str[ms->n++] = str[ms->i];
		}
	}
	else
		expand_var_loop(ms, str);
}
