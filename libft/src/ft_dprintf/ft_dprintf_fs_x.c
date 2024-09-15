/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_fs_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:00:43 by xlok              #+#    #+#             */
/*   Updated: 2024/08/03 20:06:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	get_len(unsigned int x)
{
	int	i;

	if (!x)
		return (1);
	i = 0;
	while (x)
	{
		x /= 16;
		i++;
	}
	return (i);
}

static void	flag(t_dpf *data)
{
	if (data->minus || data->precision >= 0)
		data->zero = 0;
	if (data->precision > data->plen)
		data->plen = data->precision;
	if ((data->width > data->plen) && data->zero)
		data->plen = data->width;
	data->pnum = malloc(data->plen);
	if (!data->pnum)
		return ;
	fs_x_printnum(data);
	free(data->pnum);
}

void	fs_x(t_dpf *data)
{
	if (data->space || data->plus)
		return ;
	if (data->specifier == 'x')
		data->base = "0123456789abcdef";
	if (data->specifier == 'X')
		data->base = "0123456789ABCDEF";
	data->ux = va_arg(data->ap, unsigned int);
	data->temp_ux = data->ux;
	data->len = get_len(data->ux);
	if (data->len >= data->width && data->len >= data->precision)
	{
		if (data->hash && data->ux && data->specifier == 'x')
			data->char_written += write(data->fd, "0x", 2);
		else if (data->hash && data->ux && data->specifier == 'X')
			data->char_written += write(data->fd, "0X", 2);
		if (!(!data->ux && !data->precision))
		{
			fs_putnbr(data);
			data->char_written += data->len;
		}
		return ;
	}
	data->plen = data->len;
	flag(data);
}
