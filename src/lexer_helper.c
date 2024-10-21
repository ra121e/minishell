/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:52:53 by xlok              #+#    #+#             */
/*   Updated: 2024/10/23 06:51:34 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//For printing out during testing only; to remove before submission
char	*token_kind(int k)
{
	if (k == TK_AND)
		return ("AND");
	else if (k == TK_OR)
		return ("OR");
	else if (k == TK_PIPE)
		return ("pipe");
	else if (k == TK_REDIRECT_IN)
		return ("redirect input");
	else if (k == TK_REDIRECT_OUT)
		return ("redirect output");
	else if (k == TK_REDIRECT_HEREDOC)
		return ("HEREDOC");
	else if (k == TK_REDIRECT_APPEND)
		return ("append output");
	else if (k == TK_LPAREN)
		return ("open parenthesis");
	else if (k == TK_RPAREN)
		return ("close parenthesis");
	else if (k == TK_WORD)
		return ("word");
	else if (k == TK_EOF)
		return ("EOF");
	return (0);
}

int	getvar_len(t_ms *ms, char *var)
{
	int	i;

	i = -1;
	while (ms->envp[++i])
	{
		if (!ft_strncmp(ms->envp[i]->key, var, ft_strlen(var) + 1))
			return (ft_strlen(ms->envp[i]->value));
	}
	return (0);
}

char	*getvar(t_ms *ms, char *var)
{
	int	i;

	i = -1;
	while (ms->envp[++i])
	{
		if (!ft_strncmp(ms->envp[i]->key, var, ft_strlen(var) + 1))
			return (ms->envp[i]->value);
	}
	return (0);
}

char	*add_quote(char *old)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(ft_strlen(old) + 1);
	if (!new)
		perror("remove quote malloc error");//malloc protection
	j = 0;
	new[j++] = 0;
	i = -1;
	while (old[++i])
		new[j++] = old[i];
	new[j] = 0;
	free(old);
	return (new);
}

char	*remove_quote(char *old)
{
	char	*new;
	char	quote;
	int		i;
	int		j;

	new = malloc(ft_strlen(old) + 1);
	if (!new)
		perror("remove quote malloc error");//malloc protection
	quote = 0;
	j = 0;
	i = -1;
	while (old[++i])
	{
		if (!quote && (old[i] == '\'' || old[i] == '\"'))
			quote = old[i];
		else if (quote && old[i] == quote)
			quote = 0;
		else if (old[i] != quote)
			new[j++] = old[i];
	}
	new[j] = 0;
	free(old);
	return (new);
}

//void	expand_quote_len(t_ms *ms, char *str)
//{
//	char	*var;
//	int		s;
//	int		e;
//
//	ms->var_len = 0;
//	s = -1;
//	while (str[++s])
//	{
//		if (str[s] == '\"')
//		{
//			while (str[++s] != '\"')
//			{
//				if (str[s] == '$')
//				{
//					e = ++s;
//					if (!ft_isalpha(str[e]) && str[e] != '_')
//					{
//						dprintf(2, "Invalid variable name\n");
//						exit (1);
//					}
//					while (ft_isalnum(str[e]) || str[e] == '_')
//						e++;
//					var = ft_substr(str, s, e - s);
//					if (!var)
//						perror("var malloc error\n");
//					ms->var_len += getvar_len(ms, var);
//					free(var);
//				}
//			}
//		}
//	}
//	ms->var_len += s;
//}
//
//void	expand_quote(t_ms *ms, char *str)
//{
//	char	*new_str;
//	char	*var;
//	char	*var_value;
//	int		s;
//	int		e;
//	int		n;
//
//	new_str = malloc(ms->var_len + 1);
//	if (!new_str)
//		perror("new_str malloc error\n");
//	n = 0;
//	s = -1;
//	while (str[++s])
//	{
//		new_str[n++] = str[s];
//		if (str[s] == '\"')
//		{
//			while (str[++s] != '\"')
//			{
//				if (str[s] == '$')
//				{
//					e = ++s;
//					while (ft_isalnum(str[e]) || str[e] == '_')
//						e++;
//					var = ft_substr(str, s, e - s);
//					if (!var)
//						perror("var malloc error\n");
//					var_value = getvar(ms, var);
//					while (var_value && *var_value)
//						new_str[n++] = *var_value++;
//					free(var);
//					s = e - 1;
//				}
//				else
//					new_str[n++] = str[s];
//			}
//			new_str[n++] = str[s];
//		}
//	}
//	new_str[n] = 0;
//	ms->token = new_str;
//	free(str);
//}
