/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:51:21 by xlok              #+#    #+#             */
/*   Updated: 2024/06/17 13:43:59 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (0);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!s1len && !s2len)
		return (ft_strdup(""));
	else if (!s1len && s2len)
		return (ft_strdup(s2));
	else if (s1len && !s2len)
		return (ft_strdup(s1));
	res = malloc(s1len + s2len + 1);
	if (!res)
		return (0);
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = 0;
	return (res - s1len - s2len);
}
