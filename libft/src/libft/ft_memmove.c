/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:20:35 by xlok              #+#    #+#             */
/*   Updated: 2024/06/17 12:29:09 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dtemp;
	const char	*stemp;

	if (!dest && !src)
		return (0);
	dtemp = (char *) dest;
	stemp = (const char *) src;
	if (stemp < dtemp)
	{
		while (n-- > 0)
			dtemp[n] = stemp[n];
	}
	else
	{
		while (n-- > 0)
			*dtemp++ = *stemp++;
	}
	return (dest);
}
