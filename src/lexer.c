/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:36:49 by xlok              #+#    #+#             */
/*   Updated: 2024/11/04 23:46:12 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_str_len(t_ms *ms, char *str)
{
	char	c;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			ms->len++;
			while (str[++i] != c)
				ms->len++;
		}
		else if (operator_char_count(str, i) > 20)
		{
			ms->len += 3;
			i++;
		}
		else if (operator_char_count(str, i) > 10)
			ms->len += 2;
		ms->len++;
	}
	ms->str = malloc(ms->len + 1);
	if (!ms->str)
		perror("ms->new_str malloc error");//malloc protection
}

void	optimize_str(t_ms *ms, char *str)
{
	new_str_len(ms, str);
	ms->n = 0;
	ms->i = -1;
	while (str[++ms->i])
	{
		if (str[ms->i] == '\'' || str[ms->i] == '\"')
		{
			ms->c = str[ms->i];
			ms->str[ms->n++] = str[ms->i];
			while (str[++ms->i] != ms->c)
				ms->str[ms->n++] = str[ms->i];
			ms->str[ms->n++] = str[ms->i];
		}
		else if (operator_char_count(str, ms->i) > 10)
		{
			ms->str[ms->n++] = ' ';
			if (operator_char_count(str, ms->i) > 20)
				ms->str[ms->n++] = str[ms->i++];
			ms->str[ms->n++] = str[ms->i];
			ms->str[ms->n++] = ' ';
		}
		else
			ms->str[ms->n++] = str[ms->i];
	}
	ms->str[ms->n] = 0;
}

void	quote(t_ms *ms, char c)
{
	ms->end++;
	while (ms->str[ms->end] != c)
		ms->end++;
	ms->end++;
}

void	lexer(t_ms *ms, char *str)
{
	syntax_checker(str);
	optimize_str(ms, str);
	ms->end = 0;
	while (ms->end <= ms->len)
	{
		if (ms->str[ms->end] == '\'' || ms->str[ms->end] == '\"')
			quote(ms, ms->str[ms->end]);
		else if (!ms->str[ms->end] || ft_isspace(ms->str[ms->end]))
		{
			if (!ms->end)
				ms->start = ++ms->end;
			else if (!ft_isspace(ms->str[ms->end - 1]))
				tokenize_prior_str(ms);
			else
				ms->start = ++ms->end;
		}
		else
			ms->end++;
	}
	ms->token = ft_strdup("");
	tokenize(ms, TK_EOF);
	free(ms->str);
}
