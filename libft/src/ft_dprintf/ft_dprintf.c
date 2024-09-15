/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:01:48 by xlok              #+#    #+#             */
/*   Updated: 2024/08/10 13:11:39 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	print(t_dpf *data)
{
	if (data->specifier == 'c')
		fs_c(data);
	else if (data->specifier == 's')
		fs_s(data);
	else if (data->specifier == 'p')
		fs_p(data);
	else if ((data->specifier == 'd') || (data->specifier == 'i'))
		fs_di(data);
	else if (data->specifier == 'u')
		fs_u(data);
	else if (data->specifier == 'x')
		fs_x(data);
	else if (data->specifier == 'X')
		fs_x(data);
	else
		data->char_written += write(data->fd, "%", 1);
}

static void	loop(t_dpf *data)
{
	while (*data->fmt_str)
	{
		if (*data->fmt_str == '%' && *(data->fmt_str + 1))
		{
			data->fmt_str++;
			dpf_init(data);
			parse(data);
			print(data);
		}
		else if (*data->fmt_str == '%' && !*(data->fmt_str + 1))
		{
			data->char_written = -1;
			break ;
		}
		else
			data->char_written += write(data->fd, data->fmt_str++, 1);
	}
}

int	ft_dprintf(int fd, const char *str, ...)
{
	t_dpf	*data;
	int		char_written;

	data = malloc(sizeof(t_dpf));
	if (!data)
		return (0);
	data->fd = fd;
	data->fmt_str = str;
	va_start(data->ap, str);
	data->char_written = 0;
	loop(data);
	char_written = data->char_written;
	va_end(data->ap);
	free(data);
	return (char_written);
}
