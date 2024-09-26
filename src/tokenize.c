/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:14:07 by athonda           #+#    #+#             */
/*   Updated: 2024/09/25 15:55:52 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenize.c
 * @brief make token from prompt text
 */

#include "minishell.h"


void	tokenize(t_token **head, char *p, t_token_kind kind)
{
	t_token	*now;

	now = new_token(p, kind);
	printf("token: %s\n", now->str);
	add_back(head, now);
	return ;
}
