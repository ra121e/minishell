/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:36:22 by xlok              #+#    #+#             */
/*   Updated: 2024/05/25 13:38:27 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*stemp;
	unsigned char	uc;

	stemp = (char *) s;
	uc = (unsigned char) c;
	if (!uc)
		return (stemp + ft_strlen(s));
	while (*stemp)
	{
		if (*stemp++ == uc)
			return (stemp - 1);
	}
	return (0);
}
