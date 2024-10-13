/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:03:23 by xlok              #+#    #+#             */
/*   Updated: 2024/10/13 10:29:22 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_invalid(t_ms *ms, int i)
{
	int	invalid;

	invalid = 0;
	if (!ms->key || (ms->key[0] != '_' && !ft_isalpha(ms->key[0])))
		invalid = 1;
	else
	{
		i = -1;
		while (ms->key[++i])
		{
			if (ms->key[i] != '_' && !ft_isalnum(ms->key[i]))
				invalid = 1;
		}
	}
	if (invalid)
	{
		ft_dprintf(2, "export: `%s': not a valid identifier\n", ms->pair);
		free(ms->key);
		free(ms->value);
		free(ms->pair);
		return (1);
	}
	return (0);
}

int	end_of_quote(t_ms *ms, char *str, int s, int i)
{
	ms->eq = i;
	if (ms->eq != s)
		ms->key = ft_substr(str, s, i - s);
	i++;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
		}
		i++;
	}
	ms->value = remove_quote(ft_substr(str, ms->eq + 1, i - ms->eq - 1));
	ms->pair = ft_strjoin(ft_strjoin(ms->key, "="), ms->value);
	return (i);
}

int	update_if_valid(t_ms *ms, char *str, int i)
{
	int	s;

	s = i;
	ms->key = 0;
	ms->value = 0;
	ms->pair = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (str[i] == '=')
			i = end_of_quote(ms, str, s, i);
		else
			i++;
	}
	if (!ms->key)
		ms->key = ft_substr(str, s, i - s);
	if (is_invalid(ms, i))
		return (i);
	update_env(ms);
	return (i);
}

//	take in 1 whole str. $ should be already expanded via tokenization
//	so if testing with $ will not work
//	should code with the execve() args below...
//	otherwise strjoin all the args before running
//int execve(const char *pathname, char *const argv[], char *const envp[]);

void	b_export(t_ms *ms, char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (display_if_no_arg(ms, str[i]))
		return ;
	while (1)
	{
		if (ft_isspace(str[i]))
			i++ ;
		else if (!str[i])
			break ;
		else
			i = update_if_valid(ms, str, i);
	}
}
