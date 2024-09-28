/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:14:02 by xlok              #+#    #+#             */
/*   Updated: 2024/09/28 19:45:30 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote(t_ms *ms, char *str, char c)
{
	char	*token;
	int		i;
	int		j;

	token = malloc(ms->end - ms->start + 1);
	if (!token)
		perror("remove quote malloc error");//malloc protection
	i = ms->start - 1;
	j = 0;
	while (++i < ms->end)
	{
		if (str[i] != c)
			token[j++] = str[i];
	}
	token[j] = 0;
	ms->token = token;
}

void	single_quote(t_ms *ms, char *str, t_token **head)
{
	ms->end++;
	while (str[ms->end] && str[ms->end] != '\'')
		ms->end++;
	if (!str[ms->end])
	{
		ms->token = ft_substr(str, ms->start, ms->end - ms->start);
		if (!ms->token)
			perror("token malloc error");//malloc protection
		tokenize(head, ms->token, TK_WORD);
		ms->start = ms->end;
		return ;
	}
	remove_quote(ms, str, '\'');
	if (!ms->token)
		perror("token malloc error");//malloc protection
	if (is_builtin(ms->token))
		tokenize(head, ms->token, TK_BUILTIN);
	else
		tokenize(head, ms->token, TK_WORD);
	ms->start = ++ms->end;
}

//TODO:expand $ inside "" -> tokenize separately
void	double_quote(t_ms *ms, char *str, t_token **head)
{
	ms->end++;
	while (str[ms->end] && str[ms->end] != '\"')
		ms->end++;
	if (!str[ms->end])
	{
		ms->token = ft_substr(str, ms->start, ms->end - ms->start);
		if (!ms->token)
			perror("token malloc error");//malloc protection
		tokenize(head, ms->token, TK_WORD);
		ms->start = ms->end;
		return ;
	}
	remove_quote(ms, str, '\"');
	if (!ms->token)
		perror("token malloc error");//malloc protection
	if (is_builtin(ms->token))
		tokenize(head, ms->token, TK_BUILTIN);
	else
		tokenize(head, ms->token, TK_WORD);
	ms->start = ++ms->end;
}

void	lexer_quote(t_ms *ms, char *str, t_token **head)
{
	if (str[ms->end] == '\'')
		single_quote(ms, str, head);//add str and head to struct ms?
	else
		double_quote(ms, str, head);//add str and head to struct ms?
}
