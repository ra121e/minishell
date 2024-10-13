/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:14:07 by athonda           #+#    #+#             */
/*   Updated: 2024/10/13 19:42:33 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenize.c
 * @brief make token from prompt text
 */

#include "minishell.h"

void	expand_quote_len(t_ms *ms, char *str)
{
	char	*var;
	int		s;
	int		e;

	ms->var_len = 0;
	s = -1;
	while (str[++s])
	{
		if (str[s] == '\"')
		{
			while (str[++s] != '\"')
			{
				if (str[s] == '$')
				{
					e = ++s;
					if (!ft_isalpha(str[e]) && str[e] != '_')
					{
						dprintf(2, "Invalid variable name\n");
						exit (1);
					}
					while (ft_isalnum(str[e]) || str[e] == '_')
						e++;
					var = ft_substr(str, s, e - s);
					if (!var)
						perror("var malloc error\n");
					ms->var_len += get_var_len(ms, var);
					free(var);
				}
			}
		}
	}
	ms->var_len += s;
}

void	expand_quote(t_ms *ms, char *str)
{
	char	*new_str;
	char	*var;
	char	*var_value;
	int		s;
	int		e;
	int		n;

	new_str = malloc(ms->var_len + 1);
	if (!new_str)
		perror("new_str malloc error\n");
	n = 0;
	s = -1;
	while (str[++s])
	{
		new_str[n++] = str[s];
		if (str[s] == '\"')
		{
			while (str[++s] != '\"')
			{
				if (str[s] == '$')
				{
					e = ++s;
					while (ft_isalnum(str[e]) || str[e] == '_')
						e++;
					var = ft_substr(str, s, e - s);
					if (!var)
						perror("var malloc error\n");
					var_value = getvar(ms, var);
					while (var_value && *var_value)
						new_str[n++] = *var_value++;
					free(var);
					s = e - 1;
				}
				else
					new_str[n++] = str[s];
			}
			new_str[n++] = str[s];
		}
	}
	new_str[n] = 0;
	ms->token = new_str;
	free(str);
}

void	tokenize_word(t_ms *ms, char *str, int type)
{
	ms->token = ft_substr(str, ms->start, ms->end - ms->start);
	tokenize(ms, type);
	ms->start = ++ms->end;
}

void	tokenize_char(t_ms *ms, char *str, int type)
{
	if (type == TK_SPACE)
	{
		if (ms->start != ms->end)
		{
			tokenize_word(ms, str, TK_WORD);
			ms->start = --ms->end;
		}
		while (ft_isspace(str[ms->end]))
			ms->end++;
		ms->token = ft_substr(str, ms->start, 1);
		tokenize(ms, TK_WORD);//change to TK_SPACE but need to change AST printout
		ms->end--;
	}
	else if (!ft_isspace(str[ms->end]) && str[ms->end])
	{
		ms->token = ft_substr(str, ms->start, 1);
		tokenize(ms, TK_WORD);
	}
	ms->start = ++ms->end;
}

void	tokenize(t_ms *ms, t_token_kind kind)
{
	t_token	*cur;

	if (kind == TK_QUOTE)
	{
		if (ft_strchr(ms->token, '\"'))
		{
			expand_quote_len(ms, ms->token);
			expand_quote(ms, ms->token);
		}
	}
	cur = new_token(ms->token, kind);
	printf("\033[31mtoken: \033[0m%s, \033[34mkind: \033[0m%s\n", \
			cur->str, token_kind(kind));
	add_back(&ms->head, cur);
	return ;
}
