/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:02:01 by xlok              #+#    #+#             */
/*   Updated: 2024/05/25 17:32:37 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j++])
		{
			i++;
			j = 0;
		}
	}
	return (i);
}

static int	ft_end(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j++])
		{
			i--;
			j = 0;
		}
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*tstring;
	int				start;
	int				len;

	if (!ft_strlen(s1))
		return (ft_strdup(""));
	if (!ft_strlen(set))
		return (ft_strdup(s1));
	start = ft_start(s1, set);
	len = ft_end(s1, set) - start + 1;
	if (len <= 0)
		return (ft_strdup(""));
	tstring = malloc(len + 1);
	if (!tstring)
		return (0);
	ft_memmove(tstring, s1 + start, len);
	tstring[len] = 0;
	return (tstring);
}
