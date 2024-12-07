/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:02:22 by athonda           #+#    #+#             */
/*   Updated: 2024/12/07 11:33:03 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_value(t_ms *ms, char *key, char *new_value)
{
	char	*tmp;
	int		i;

	i = -1;
	while (ms->envp[++i])
	{
		if (!ft_strncmp(ms->envp[i]->key, key, ft_strlen(key) + 1))
		{
			tmp = ms->envp[i]->value;
			ms->envp[i]->value = new_value;
			if (!ms->envp[i]->value)
				error_malloc(ms, "cd update_value malloc error");
			free_str(tmp);
			tmp = ms->envp[i]->pair;
			ms->envp[i]->pair = ft_strsjoin(3, ms->envp[i]->key, \
					"=", new_value);
			if (!ms->envp[i]->pair)
				error_malloc(ms, "cd update_value malloc error");
			free_str(tmp);
			break ;
		}
	}
	if (!ms->envp[i])
		free_str(new_value);
}

static void	update_envp(t_ms *ms, char *oldpwd)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(0, 0);
	if (!pwd)
		error_malloc(ms, "cd pwd malloc error");
	update_value(ms, "PWD", pwd);
	if (ms->unset_pwd)
	{
		tmp = oldpwd;
		oldpwd = ft_strdup("");
		update_value(ms, "OLDPWD", oldpwd);
		free_str(tmp);
		ms->unset_pwd = 0;
	}
	else
		update_value(ms, "OLDPWD", oldpwd);
	ms->exit_status = 0;
}

static void	invalid_dir(t_ms *ms, char *arg, char *oldpwd)
{
	if (ms->cmd[2])
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		ms->exit_status = 1;
	}
	else if (chdir(arg) == -1)
	{
		if (errno == EACCES)
			ft_dprintf(2, "minishell: cd: %s: Permission denied\n", arg);
		else
			ft_dprintf(2, "minishell: cd: %s: No such file or directory\n", arg);
		ms->exit_status = 1;
	}
	else
		update_envp(ms, oldpwd);
}

void	builtin_cd(t_ms *ms)
{
	char	**homepath;
	char	*oldpwd;

	oldpwd = getcwd(0, 0);
	if (!oldpwd)
		error_malloc(ms, "cd oldpwd malloc error");
	if (ms->cmd[1] == NULL)
	{
		homepath = find_envpath(ms, "HOME=");
		if (!homepath || chdir(get_var(ms, "HOME")) == -1)
		{
			ft_dprintf(2, "minishell: cd: HOME not set\n");
			ms->exit_status = 1;
		}
		else
			update_envp(ms, oldpwd);
		if (homepath)
			free_str_array(homepath);
	}
	else
		invalid_dir(ms, ms->cmd[1], oldpwd);
	if (ms->exit_status)
		free_str(oldpwd);
}
