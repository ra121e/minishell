/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:52:53 by xlok              #+#    #+#             */
/*   Updated: 2024/10/11 07:36:04 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *str)
{
	return (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3) || \
			!ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 7) || \
			!ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4) || \
			!ft_strncmp(str, "exit", 5));
}

//For printing out during testing only; to remove before submission
char	*token_kind(int k)
{
	if (k == TK_AND)
		return ("AND");
	else if (k == TK_OR)
		return ("OR");
	else if (k == TK_LPAREN)
		return ("open parenthesis");
	else if (k == TK_RPAREN)
		return ("close parenthesis");
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
	else if (k == TK_VAR)
		return ("var");
	else if (k == TK_VAR_QUOTE)
		return ("var quote");
	else if (k == TK_QUOTE)
		return ("quote");
	else if (k == TK_WORD)
		return ("word");
	return (0);
}

int	get_var_len(t_ms *ms, char *var)
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

char	*remove_quote(char *old)
{
	char	*new;
	char	quote;
	int		i;
	int		j;

	i = 0;
	while (old[i])
		i++;
	new = malloc(i + 1);
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
