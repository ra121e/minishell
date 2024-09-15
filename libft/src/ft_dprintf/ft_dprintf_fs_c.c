/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_fs_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:59:45 by xlok              #+#    #+#             */
/*   Updated: 2024/08/03 20:06:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	fs_c(t_dpf *data)
{
	int	c;

	c = va_arg(data->ap, int);
	if (!data->width)
		data->char_written += write(data->fd, &c, 1);
	else if (data->minus)
	{
		data->char_written += write(data->fd, &c, 1);
		while (--data->width)
			data->char_written += write(data->fd, " ", 1);
	}
	else
	{
		while (--data->width)
			data->char_written += write(data->fd, " ", 1);
		data->char_written += write(data->fd, &c, 1);
	}
}
