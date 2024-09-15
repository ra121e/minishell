/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:20:35 by xlok              #+#    #+#             */
/*   Updated: 2024/05/25 15:15:35 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dtemp;
	char	*stemp;

	if (!dest && !src)
		return (0);
	dtemp = (char *) dest;
	stemp = (char *) src;
	while (n-- > 0)
		*dtemp++ = *stemp++;
	return (dest);
}
