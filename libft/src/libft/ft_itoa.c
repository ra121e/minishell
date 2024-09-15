/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:16:53 by xlok              #+#    #+#             */
/*   Updated: 2024/08/21 19:26:03 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;

	if (!n)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	result(int num, int len, char *res, int base)
{
	if (num >= base || num <= -base)
		result(num / base, len, res, base);
	if (num < 0 && num > -base)
		*res = '-';
	if (num < 0)
		res[ft_len(num) - 1] = -(num % base) + '0';
	else
		res[ft_len(num) - 1] = num % base + '0';
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = ft_len(n);
	res = malloc(len + 1);
	if (!res)
		return (0);
	result(n, len, res, 10);
	res[len] = 0;
	return (res);
}
