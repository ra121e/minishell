/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:17:23 by xlok              #+#    #+#             */
/*   Updated: 2024/07/21 16:57:39 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c, int count)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((!i || s[i - 1] == c) && s[i] != c)
			count++;
	}
	return (count);
}

static void	free_all(char **res, int w)
{
	while (--w >= 0)
	{
		free(res[w]);
		res[w] = 0;
	}
}

static void	get_word(char *word, const char *s, int start, int end)
{
	while (start < end)
		*word++ = s[start++];
	*word = 0;
}

static int	get_words(const char *s, char c, char **res, int w)
{
	int	start;
	int	i;

	start = 0;
	i = -1;
	while (s[++i])
	{
		if ((!i || s[i - 1] == c) && s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			res[w] = malloc(i - start + 1);
			if (!res[w])
				return (free_all(res, w), 0);
			get_word(res[w++], s, start, i);
		}
		if (!s[i])
			break ;
	}
	res[w] = 0;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	int		wc;

	wc = word_count(s, c, 0);
	if (!wc)
		return (0);
	res = malloc(sizeof(char *) * (wc + 1));
	if (!res)
		return (0);
	if (!get_words(s, c, res, 0))
		return (free(res), NULL);
	return (res);
}
