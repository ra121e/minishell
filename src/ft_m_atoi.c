/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:01:14 by xlok              #+#    #+#             */
/*   Updated: 2024/12/06 17:15:51 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_m_atoi(const char *s)
{
	int	res;
	int	sign;

	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	sign = 1;
	if (*s == '-')
		sign = -1;
	if (*s == '+' || *s == '-')
		s++;
	res = 0;
	while (*s >= '0' && *s <= '9')
		res = (res * 10) + (*s++ - '0');
	if (*s)
		return (0);
	return (res * sign);
}
