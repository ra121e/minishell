/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:49:37 by xlok              #+#    #+#             */
/*   Updated: 2024/11/29 20:44:21 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_new_len_found_var(t_ms *ms, char *str, int i)
{
	ms->start = ++i;
	while (str[i] == '_' || ft_isalnum(str[i]))
		i++;
	if (str[i] == '?')
		i++;
	else if (i == ms->start)
	{
		ms->len++;
		return (--i);
	}
	ms->var = ft_substr(str, ms->start, i - ms->start);
	if (!ms->var)
		error_malloc(ms, "ms->var malloc error\n");
	ms->len += get_var_len(ms, ms->var);
	free(ms->var);
	return (--i);
}

void	get_new_len(t_ms *ms, char *str, int i, int is_heredoc)
{
	while (str[++i])
	{
		if (!is_heredoc && str[i] == '\"')
		{
			while (str[++i] != '\"')
			{
				if (str[i] == '$')
					i = get_new_len_found_var(ms, str, i);
				else
					ms->len++;
			}
			ms->len += 2;
		}
		else if (!is_heredoc && str[i] == '\'')
		{
			while (str[++i] != '\'')
				ms->len++;
			ms->len += 2;
		}
		else if (str[i] == '$')
			i = get_new_len_found_var(ms, str, i);
		else
			ms->len++;
	}
}

void	replace_var(t_ms *ms)
{
	ms->end = 0;
	while (ms->var_value[ms->end])
		ms->new_str[ms->n++] = ms->var_value[ms->end++];
	ms->expand_var = 1;
}

static void	add_word_split2(t_ms *ms, char *new_str)
{
	char	**tmp;
	int		i;

	tmp = ms->word_split;
	i = 0;
	while (tmp && tmp[i])
		i++;
	ms->word_split = malloc(sizeof(char *) * (i + 2));
	if (!ms->word_split)
		error_malloc(ms, "malloc error for ms->cmd");
	i = 0;
	while (tmp && tmp[i])
	{
		ms->word_split[i] = tmp[i];
		i++;
	}
	ms->word_split[i++] = new_str;
	ms->word_split[i] = 0;
	free(tmp);
}

void	add_word_split(t_ms *ms, char *str, int s, int i)
{
	char	*new_str;

	new_str = ft_substr(str, s, i - s);
	if (!new_str)
	{
		error_malloc(ms, "add_cmd_arg malloc error");
		free_str(ms->new_str);
		cleanup(ms);
		cleanup_final(ms);
		exit(EXIT_FAILURE);
	}
	if (!*str || i - s > 0)
		add_word_split2(ms, new_str);
	else
		free(new_str);
}
