/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:24:39 by xlok              #+#    #+#             */
/*   Updated: 2024/10/20 13:28:34 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup(t_ms *ms)
{
//	free envp
//	free cmd
//	free cmd_envp
//	free tokens

	free(ms->prompt);
	free(ms);
}
