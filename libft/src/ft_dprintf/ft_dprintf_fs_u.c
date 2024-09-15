/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_fs_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:13:18 by xlok              #+#    #+#             */
/*   Updated: 2024/08/03 20:06:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	get_len(unsigned int u)
{
	int	i;

	if (!u)
		return (1);
	i = 0;
	while (u)
	{
		u /= 10;
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
	fs_u_printnum(data);
	free(data->pnum);
}

void	fs_u(t_dpf *data)
{
	if (data->hash || data->space || data->plus)
		return ;
	data->ux = va_arg(data->ap, int);
	data->temp_ux = data->ux;
	data->len = get_len(data->ux);
	if (data->len >= data->width && data->len >= data->precision)
	{
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
