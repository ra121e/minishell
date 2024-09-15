/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_fs_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:13:18 by xlok              #+#    #+#             */
/*   Updated: 2024/08/03 20:06:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	padding(t_dpf *data, char *s)
{
	if (data->minus)
	{
		data->char_written += write(data->fd, s, data->len);
		while (--data->width >= data->len)
			data->char_written += write(data->fd, " ", 1);
	}
	else
	{
		while (--data->width >= data->len)
			data->char_written += write(data->fd, " ", 1);
		data->char_written += write(data->fd, s, data->len);
	}
}

void	fs_s(t_dpf *data)
{
	char	*s;

	s = va_arg(data->ap, char *);
	if (!s && (data->precision == -1 || data->precision >= 6))
		s = "(null)";
	else if (!s && data->precision >= 0 && data->precision < 6)
		s = "";
	data->len = (int)ft_strlen(s);
	if (data->precision >= 0 && data->precision < data->len)
		data->len = data->precision;
	if (data->width > data->len)
		padding(data, s);
	else
		data->char_written += write(data->fd, s, data->len);
}
