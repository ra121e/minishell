/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:13:31 by xlok              #+#    #+#             */
/*   Updated: 2024/05/25 17:05:27 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1temp;
	unsigned char	*s2temp;
	size_t			i;

	if (!n)
		return ((int)0);
	s1temp = (unsigned char *) s1;
	s2temp = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (s1temp[i] != s2temp[i])
			break ;
		i++;
	}
	if (i == n)
		return ((int)0);
	return (s1temp[i] - s2temp[i]);
}
