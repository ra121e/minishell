/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_fs_di.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:13:18 by xlok              #+#    #+#             */
/*   Updated: 2024/08/03 20:06:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	get_len(int di)
{
	int	i;

	i = 0;
	if (!di)
		return (1);
	while (di)
	{
		di /= 10;
		i++;
	}
	return (i);
}

static void	flag(t_dpf *data)
{
	if (data->minus || data->precision >= 0)
		data->zero = 0;
	if (data->plus)
		data->space = 0;
	if (data->precision > data->plen)
		data->plen = data->precision;
	if ((data->width > data->plen) && data->zero)
		data->plen = data->width;
	if (data->precision >= 0 && (data->space || data->plus || data->di < 0))
		data->plen++;
	data->pnum = malloc(data->plen);
	if (!data->pnum)
		return ;
	fs_di_printnum(data);
	free(data->pnum);
}

void	fs_di(t_dpf *data)
{
	data->di = va_arg(data->ap, int);
	if (data->di < 0)
		data->temp_di = -data->di;
	else
		data->temp_di = data->di;
	data->len = get_len(data->di);
	if (data->len >= data->width && data->len >= data->precision)
	{
		if (data->di < 0)
			data->char_written += write(data->fd, "-", 1);
		else if (data->plus)
			data->char_written += write(data->fd, "+", 1);
		else if (data->space)
			data->char_written += write(data->fd, " ", 1);
		if (!(!data->di && !data->precision))
		{
			fs_putnbr(data);
			data->char_written += data->len;
		}
		return ;
	}
	data->plen = data->len;
	flag(data);
}
