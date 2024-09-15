/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:04:22 by xlok              #+#    #+#             */
/*   Updated: 2024/08/10 13:18:17 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	dpf_init(t_dpf *data)
{
	data->hash = 0;
	data->zero = 0;
	data->minus = 0;
	data->space = 0;
	data->plus = 0;
	data->width = 0;
	data->precision = -1;
	data->specifier = 0;
	data->len = 0;
	data->plen = 0;
	data->i = 0;
	data->di = 0;
	data->temp_di = 0;
	data->ux = 0;
	data->temp_ux = 0;
}
