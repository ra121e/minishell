/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:02:22 by athonda           #+#    #+#             */
/*   Updated: 2024/12/06 20:18:33 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_value(t_ms *ms, char *str, int i)
{
	char	*tmp;

	tmp = ms->envp[i]->value;
	ms->envp[i]->value = str;
	if (!ms->envp[i]->value)
		error_malloc(ms, "cd update_value malloc error");
	free_str(tmp);
	tmp = ms->envp[i]->pair;
	ms->envp[i]->pair = ft_strsjoin(3, ms->envp[i]->key, \
			"=", ms->envp[i]->value);
	if (!ms->envp[i]->pair)
		error_malloc(ms, "cd update_value malloc error");
	free_str(tmp);
}

static void	update_oldpwd(t_ms *ms, char *oldpwd)
{
	int	i;

	i = -1;
	while (ms->envp[++i])
	{
		if (!ft_strncmp(ms->envp[i]->key, "OLDPWD", 7))
		{
			update_value(ms, oldpwd, i);
			break ;
		}
	}
	if (!ms->envp[i])
	{
		ms->key = ft_strdup("OLDPWD");
		ms->value = oldpwd;
		ms->pair = ft_strsjoin(3, ms->key, "=", ms->value);
		export_add(ms, ms->envp);
	}
}

static void	update_envp(t_ms *ms, char *oldpwd)
{
	char	*pwd;
	int		i;

	pwd = getcwd(0, 0);
	if (!pwd)
		error_malloc(ms, "cd pwd malloc error");
	i = -1;
	while (ms->envp[++i])
	{
		if (!ft_strncmp(ms->envp[i]->key, "PWD", 4))
			update_value(ms, pwd, i);
	}
	update_oldpwd(ms, oldpwd);
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
