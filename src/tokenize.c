/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:14:07 by athonda           #+#    #+#             */
/*   Updated: 2024/09/27 16:18:26 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenize.c
 * @brief make token from prompt text
 */

#include "minishell.h"


void	tokenize(t_token **head, char *p, t_token_kind kind)
{
	t_token	*cur;

	cur = new_token(p, kind);
	printf("token: %s\n", cur->str);
	add_back(head, cur);
	return ;
}
