/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:41:36 by xlok              #+#    #+#             */
/*   Updated: 2024/05/25 18:33:48 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		biglen;
	size_t		littlelen;
	size_t		i;
	size_t		j;

	biglen = ft_strlen(big);
	littlelen = ft_strlen(little);
	if (!littlelen)
		return ((char *)big);
	i = 0;
	while (i < len && i < biglen)
	{
		j = 0;
		while (i < len && i < biglen && \
			(unsigned char) big[i] != (unsigned char) little[j])
			i++;
		if (len - i < littlelen)
			return (0);
		if (!ft_strncmp(big + i, little, littlelen))
			return ((char *)big + i);
		i++;
	}
	return (0);
}
