/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_fs_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:00:26 by xlok              #+#    #+#             */
/*   Updated: 2024/08/03 20:06:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	get_len(uintptr_t p)
{
	int	i;

	i = 0;
	while (p)
	{
		p /= 16;
		i++;
	}
	return (i);
}

static void	convert(t_dpf *data, uintptr_t p)
{
	if (p / 16 > 0)
		convert(data, p / 16);
	ft_putchar_fd(data->base[p % 16], 1);
}

static void	padding_null(t_dpf *data, uintptr_t p)
{
	data->width -= 5;
	if (data->minus)
	{
		data->char_written += write(data->fd, "(nil)", 5);
		while (--data->width >= data->len)
			data->char_written += write(data->fd, " ", 1);
	}
	else
	{
		while (--data->width >= data->len)
			data->char_written += write(data->fd, " ", 1);
		if (!p)
			data->char_written += write(data->fd, "(nil)", 5);
	}
}

static void	padding(t_dpf *data, uintptr_t p)
{
	if (data->minus)
	{
		write(data->fd, "0x", 2);
		convert(data, p);
		data->char_written += data->len;
		while (--data->width >= data->len)
			data->char_written += write(data->fd, " ", 1);
	}
	else
	{
		while (--data->width >= data->len)
			data->char_written += write(data->fd, " ", 1);
		write(data->fd, "0x", 2);
		convert(data, p);
		data->char_written += data->len;
	}
}

void	fs_p(t_dpf *data)
{
	uintptr_t	p;

	p = va_arg(data->ap, uintptr_t);
	data->base = "0123456789abcdef";
	if (p)
		data->len = get_len(p) + 2;
	if (!p && data->width <= 5)
		data->char_written += write(data->fd, "(nil)", 5);
	else if (!p && data->width > 5)
		padding_null(data, p);
	else if (data->width > data->len)
		padding(data, p);
	else
	{
		write(data->fd, "0x", 2);
		convert(data, p);
		data->char_written += data->len;
	}
}
