/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:05:57 by xlok              #+#    #+#             */
/*   Updated: 2024/11/11 23:33:31 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_var(t_ms *ms)
{
	ms->end = 0;
	while (ms->var_value[ms->end])
		ms->new_str[ms->n++] = ms->var_value[ms->end++];
}

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

void	expand_var_heredoc_loop(t_ms *ms, char *str)
{
	while (str[++ms->i])
	{
		if (str[ms->i] == '\"')
		{
			ms->new_str[ms->n++] = str[ms->i];
			while (str[++ms->i] != '\"')
			{
				if (str[ms->i] == '$')
					ms->i = found_var(ms, str, ms->i);
				else
					ms->new_str[ms->n++] = str[ms->i];
			}
			ms->new_str[ms->n++] = str[ms->i];
		}
		else if (str[ms->i] == '$')
			ms->i = found_var(ms, str, ms->i);
		else
			ms->new_str[ms->n++] = str[ms->i];
	}
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
		else if (str[ms->i] == '$')
			ms->i = found_var(ms, str, ms->i);
		else
			ms->new_str[ms->n++] = str[ms->i];
	}
}

void	expand_var(t_ms *ms, char *str, int is_heredoc)
{
	ms->len = 0;
	ms->expand_var = 0;
	get_new_len(ms, str, -1, is_heredoc);
	ms->new_str = malloc(ms->len + 1);
	if (!ms->new_str)
		error_malloc(ms, "ms->new_str malloc error");
	ms->n = 0;
	ms->i = -1;
	if (is_heredoc)
		expand_var_heredoc_loop(ms, str);
	else
		expand_var_loop(ms, str);
	ms->new_str[ms->n] = 0;
}

//void	expand_var_heredoc(t_ms *ms, char *str)
//{
//	ms->len = 0;
//	ms->expand_var = 0;
//	get_new_len(ms, str, -1);
//	ms->new_str = malloc(ms->len + 1);
//	if (!ms->new_str)
//		error_malloc(ms, "ms->new_str malloc error");
//	ms->n = 0;
//	ms->i = -1;
//	expand_var_heredoc_loop(ms, str);
//	ms->new_str[ms->n] = 0;
//}
