/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:42:17 by xlok              #+#    #+#             */
/*   Updated: 2024/05/25 14:00:29 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*stemp;

	stemp = (unsigned char *) s;
	while (n--)
	{
		if (*stemp == (unsigned char) c)
			return ((void *) stemp);
		stemp++;
	}
	return (0);
}
