/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:06:15 by xlok              #+#    #+#             */
/*   Updated: 2024/06/17 14:01:01 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(src);
	if (size <= len)
		len = size - 1;
	if (size > 0)
	{
		i = len;
		while (i--)
		{
			if (src < dst)
				dst[i] = src[i];
			else
				dst[len - i - 1] = src[len - i - 1];
		}
		dst[len] = 0;
	}
	return (ft_strlen(src));
}
