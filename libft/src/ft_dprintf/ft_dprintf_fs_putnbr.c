/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_fs_putnbr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:37:27 by xlok              #+#    #+#             */
/*   Updated: 2024/08/03 20:06:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	di(int n)
{
	if (n / 10)
		di(n / 10);
	if (n < 0)
		ft_putchar_fd(-(n % 10) + 48, 1);
	else
		ft_putchar_fd((n % 10) + 48, 1);
}

static void	u(unsigned int n)
{
	if (n / 10)
		u(n / 10);
	ft_putchar_fd((n % 10) + 48, 1);
}

static void	x(unsigned int n, t_dpf *data)
{
	if (n / 16)
		x(n / 16, data);
	ft_putchar_fd(data->base[n % 16], 1);
}

void	fs_putnbr(t_dpf *data)
{
	if (data->specifier == 'd' || data->specifier == 'i')
		di(data->di);
	else if (data->specifier == 'u')
		u(data->ux);
	else if (data->specifier == 'x' || data->specifier == 'X')
		x(data->ux, data);
}
