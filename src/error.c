/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:46:53 by athonda           #+#    #+#             */
/*   Updated: 2024/11/15 09:19:13 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file error_exit.c
 * @brief perror and exit with failure
 */

#include "minishell.h"

/**
 * @fn void	error_exit(char *str)
 * @brief perror and exit
 * @param[in] *str error message
 * @return none
 */

void	error_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	error_wrong_cmd(t_ms *ms)
{
	ft_putstr_fd(ms->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_split(ms->cmd);
	exit(127);
}

void	error_malloc(t_ms *ms, char *msg)
{
	perror(msg);
	ms->error = true;
}

void	error_filename(t_ms *ms, char *msg)
{
	char	*error_msg;

	error_msg = ft_strjoin("minishell: ", msg);
	perror(error_msg);
	free(error_msg);
	ms->error = true;
}
