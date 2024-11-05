/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:03:23 by xlok              #+#    #+#             */
/*   Updated: 2024/11/06 07:50:54 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid(t_ms *ms)
{
	int	invalid;
	int	i;

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
		ms->exit_status = 1;
		free_str(ms->key);
		free_str(ms->value);
		free_str(ms->pair);
	}
	return (invalid);
}

void	init_export(t_ms *ms)
{
	ms->eq = 0;
	ms->key = 0;
	ms->value = 0;
	ms->pair = 0;
}

int	update_if_valid(t_ms *ms, char *str)
{
	int	i;

	init_export(ms);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			ms->eq = i;
	}
	if (ms->eq)
	{
		ms->key = ft_substr(str, 0, ms->eq);
		ms->value = ft_strdup(str + ms->eq + 1);
		ms->pair = ft_strsjoin(3, ms->key, "=", ms->value);
	}
	else
	{
		ms->key = ft_strdup(str);
		ms->value = 0;
		ms->pair = ft_strdup(str);
	}
	if (invalid(ms))
		return (1);
	update_env(ms);
	return (0);
}

void	builtin_export(t_ms *ms)
{
	int	exit_status;
	int	i;

	if (display_if_no_arg(ms))
	{
		ms->exit_status = 0;
		return ;
	}
	i = 0;
	while (ms->cmd[++i])
		exit_status = update_if_valid(ms, ms->cmd[i]);
	ms->exit_status = exit_status;
}
