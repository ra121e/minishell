/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:25:04 by xlok              #+#    #+#             */
/*   Updated: 2024/06/17 13:09:37 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	sslen;
	size_t	i;

	if (!s)
		return (0);
	if (!ft_strlen(s) || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		sslen = ft_strlen(s) - start;
	else
		sslen = len;
	ss = malloc(sslen + 1);
	if (!ss)
		return (0);
	i = sslen;
	while (i--)
	{
		if (s < ss)
			ss[i] = s[start + i];
		else
			ss[sslen - i - 1] = s[start + (sslen - i - 1)];
	}
	ss[sslen] = 0;
	return (ss);
}
