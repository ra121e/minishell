/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:36:22 by xlok              #+#    #+#             */
/*   Updated: 2024/05/25 13:39:57 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*stemp;
	unsigned char	uc;
	int				slen;
	int				i;

	slen = (int) ft_strlen(s);
	stemp = (char *) s;
	uc = (unsigned char) c;
	if (!uc)
		return (stemp + slen);
	i = slen;
	while (i >= 0)
	{
		if (stemp[i] == uc)
			return (stemp + i);
		i--;
	}
	return (0);
}
