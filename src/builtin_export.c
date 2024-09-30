/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:03:23 by xlok              #+#    #+#             */
/*   Updated: 2024/10/07 23:46:01 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_export_add(t_ms *ms, t_envp **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	ms->envp = malloc(sizeof(t_envp) * (i + 2));
	if (!ms->envp)
		perror("malloc error for export_add\n");
	i = 0;
	while (envp[i])
	{
		ms->envp[i] = malloc(sizeof(t_envp));
		if (!ms->envp[i])
			perror("malloc error for export_add\n");
		ms->envp[i] = envp[i];
		i++;
	}
	ms->envp[i] = malloc(sizeof(t_envp));
	if (!ms->envp[i])
		perror("malloc error for export_add\n");
	ms->envp[i]->key = ms->key;
	ms->envp[i]->value = ms->value;
	ms->envp[i]->pair = ms->pair;
	ms->envp[++i] = 0;
//	free
}

int	export_quote(t_ms *ms, char *str, int eq, int i, char c)
{
	i += 2;
	while (str[i] != c)
		i++;
	ms->value = ft_substr(str, eq + 2, i - eq - 2);
	if (!ms->value)
		perror("ms->value malloc error");//malloc protection
	ms->pair = ft_strjoin(ft_strjoin(ms->key, "="), ms->value);
	if (!ms->pair)
		perror("ms->pair malloc error");//malloc protection
	return (++i);
}

//	take in 1 whole str. $ should be already expanded via tokenization
//	so if testing with $ will not work
void	b_export(t_ms *ms, char *str)
{
	int	i;
	int	j;
	int	k;
	int	eq;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (!str[i])
	{
		k = -1;
		while (ms->envp[++k])
		{
			if (!ms->envp[k]->value)
				printf("declare -x %s\n", ms->envp[k]->key);
			else if (!ft_strncmp(ms->envp[k]->value, "", 1))
				printf("declare -x %s=\"\"\n", ms->envp[k]->key);
			else
				printf("declare -x %s=\"%s\"\n", ms->envp[k]->key, ms->envp[k]->value);
		}
		return ;
	}
	while (1)//maybe a ft_strtrim would be easier
	{
		j = i;
		while (str[i] && str[i] != '=' && !ft_isspace(str[i]))
			i++;
		ms->key = ft_substr(str, j, i - j);
		if (!ms->key)
			perror("ms->key malloc error");//malloc protection
		ms->len = ft_strlen(ms->key);
		eq = i;
		if (str[i] == '=' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
			i = export_quote(ms, str, eq, i, str[i + 1]);
		else
		{
			while (str[i] && !ft_isspace(str[i]))
				i++;
			if (!str[eq] || ft_isspace(str[eq]))
				ms->value = 0;
			else if (eq + 1 < i)
			{
				ms->value = ft_substr(str, eq + 1, i - eq - 1);
				if (!ms->value)
					perror("ms->value malloc error");//malloc protection
			}
			else
				ms->value = ft_strdup("");
			ms->pair= ft_substr(str, j, i - j);
			if (!ms->pair)
				perror("ms->ms->pair malloc error");//malloc protection
		}
		if (ms->key[0] == '_' || ft_isalpha(ms->key[0]))
		{
			int	j;

			j = 0;
			while (ms->envp[j])
			{
				if (!ft_strncmp(ms->envp[j]->key, ms->key, ms->len + 1))
				{
					if (!ms->envp[j]->value || ms->value)
					{
						ms->envp[j]->key = ms->key;
						ms->envp[j]->value = ms->value;
						ms->envp[j]->pair = ms->pair;
					}
					break ;
				}
				j++;
			}
			if (!ms->envp[j])
				b_export_add(ms, ms->envp);
		}
		else
		{
			ft_dprintf(2, "export: '%s': not a valid identifier\n", ms->pair);
			free(ms->key);
			free(ms->value);
			free(ms->pair);
		}
		while (ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
	}
}
