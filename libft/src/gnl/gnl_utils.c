/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:25:04 by xlok              #+#    #+#             */
/*   Updated: 2024/08/06 19:13:13 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

void	ft_free(char **p)
{
	if (p && *p)
	{
		free(*p);
		*p = 0;
	}
}

int	eof_nl(char *buf)
{
	ssize_t	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		return (1);
	return (0);
}

char	*strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1len;
	size_t	s2len;

	if (!s1)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
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
