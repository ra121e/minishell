/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_fs_padding.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:26:34 by xlok              #+#    #+#             */
/*   Updated: 2024/08/03 20:06:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	fs_padding(t_dpf *data)
{
	if (data->hash && data->ux)
		data->width -= 2;
	if (data->minus)
	{
		if (data->hash && data->ux && data->specifier == 'x')
			data->char_written += write(data->fd, "0x", 2);
		if (data->hash && data->ux && data->specifier == 'X')
			data->char_written += write(data->fd, "0X", 2);
		data->char_written += write(data->fd, data->pnum, data->plen);
		while (data->width-- - data->plen > 0)
			data->char_written += write(data->fd, " ", 1);
	}
	else
	{
		while (data->width-- - data->plen > 0)
			data->char_written += write(data->fd, " ", 1);
		if (data->hash && data->ux && data->specifier == 'x')
			data->char_written += write(data->fd, "0x", 2);
		if (data->hash && data->ux && data->specifier == 'X')
			data->char_written += write(data->fd, "0X", 2);
		data->char_written += write(data->fd, data->pnum, data->plen);
	}
}
