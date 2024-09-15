/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:06:15 by xlok              #+#    #+#             */
/*   Updated: 2024/08/17 19:09:39 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	len;
	size_t	i;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size <= dstlen)
		return (size + srclen);
	if (size <= dstlen + srclen)
		len = size - dstlen;
	else
		len = srclen + 1;
	i = len;
	while (i--)
		dst[dstlen + i] = src[i];
	dst[dstlen + len - 1] = 0;
	return (dstlen + srclen);
}
