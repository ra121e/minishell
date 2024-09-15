/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_fs_di_printnum.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:03:57 by xlok              #+#    #+#             */
/*   Updated: 2024/08/03 20:06:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	non_minus(t_dpf *data)
{
	while (++data->i < data->width - data->len)
		data->char_written += write(data->fd, " ", 1);
	if (data->di < 0)
		data->char_written += write(data->fd, "-", 1);
	else if (data->plus)
		data->char_written += write(data->fd, "+", 1);
	else if (data->space)
		data->char_written += write(data->fd, " ", 1);
	else
		data->char_written += write(data->fd, " ", 1);
	fs_putnbr(data);
	data->char_written += data->len;
}

static void	minus(t_dpf *data)
{
	if (data->di >= 0)
		data->i--;
	else if (data->di < 0)
		data->char_written += write(data->fd, "-", 1);
	else if (data->plus)
		data->char_written += write(data->fd, "+", 1);
	else if (data->space)
		data->char_written += write(data->fd, " ", 1);
	fs_putnbr(data);
	data->char_written += data->len;
	while (++data->i < data->width - data->len)
		data->char_written += write(data->fd, " ", 1);
}

static void	zero(t_dpf *data)
{
	if (data->di >= 0 && data->plus)
		data->pnum[data->i++] = '+';
	else if (data->di >= 0 && data->space)
		data->pnum[data->i++] = ' ';
	else if (data->di >= 0)
		data->pnum[data->i++] = '0';
	else if (data->di < 0)
		data->pnum[data->i++] = '-';
	while (data->i < data->plen - data->len)
		data->pnum[data->i++] = '0';
	if (!data->di)
		data->pnum[data->plen - 1] = '0';
}

static void	precision(t_dpf *data)
{
	if (data->di >= 0 && data->plus)
		data->pnum[data->i++] = '+';
	else if (data->di >= 0 && data->space)
		data->pnum[data->i++] = ' ';
	else if (data->di < 0)
		data->pnum[data->i++] = '-';
	while (data->i < data->plen - data->len)
		data->pnum[data->i++] = '0';
	if (!data->di)
		data->pnum[data->plen - 1] = '0';
}

void	fs_di_printnum(t_dpf *data)
{
	if (data->precision >= 0)
		precision(data);
	else if (data->zero)
		zero(data);
	else
	{
		if (data->minus)
			minus(data);
		else
			non_minus(data);
		return ;
	}
	data->i = data->plen;
	while (data->temp_di)
	{
		data->pnum[--data->i] = (data->temp_di % 10) + 48;
		data->temp_di /= 10;
	}
	if (!data->di && !data->precision)
		data->plen--;
	fs_padding(data);
}
