/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:12:42 by xlok              #+#    #+#             */
/*   Updated: 2024/11/09 21:46:40 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reslen(int count, va_list ap)
{
	char	*str;
	int		res_len;
	int		len;
	int		i;

	res_len = 0;
	i = -1;
	while (++i < count)
	{
		str = va_arg(ap, char *);
		len = -1;
		while (str && str[++len])
			res_len++;
	}
	return (res_len);
}

char	*ft_strsjoin(int count, ...)
{
	va_list	args;
	char	*res;
	char	*str;
	int		res_len;
	int		i;

	va_start(args, count);
	res_len = reslen(count, args);
	res = malloc(res_len + 1);
	if (!res)
		return (0);
	va_start(args, count);
	res_len = 0;
	i = -1;
	while (++i < count)
	{
		str = va_arg(args, char *);
		while (*str)
			res[res_len++] = *str++;
	}
	res[res_len] = 0;
	va_end(args);
	return (res);
}
