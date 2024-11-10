/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:52:53 by xlok              #+#    #+#             */
/*   Updated: 2024/11/10 18:01:33 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_len(t_ms *ms, char *var)
{
	int	i;

	if (!ft_strncmp(var, "?", 2))
	{
		var = ft_itoa(ms->exit_status);
		if (!var)
			perror("$? malloc error");//cleanup & return to prompt
		i = ft_strlen(var);
		free(var);
		return (i);
	}
	i = -1;
	while (ms->envp[++i])
	{
		if (ms->envp[i]->value && \
				!ft_strncmp(ms->envp[i]->key, var, ft_strlen(var) + 1))
			return (ft_strlen(ms->envp[i]->value));
	}
	return (0);
}

char	*get_var(t_ms *ms, char *var)
{
	int	i;

	if (!ft_strncmp(var, "?", 2))
	{
		var = ft_itoa(ms->exit_status);
		if (!var)
			perror("$? malloc error");//cleanup & return to prompt
		return (var);
	}
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
	return (new);
}
