/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:14:07 by athonda           #+#    #+#             */
/*   Updated: 2024/09/23 18:28:33 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenize.c
 * @brief make token from prompt text
 */

#include "minishell.h"


t_token	*tokenize(char *p)
{
	t_token	head;
	t_token	*now;

	head.next = NULL;
	now = &head;
	now = new_token(TK_RESERVED, p, now);
	printf("token: %s\n", now->str);
	return (head.next);
}