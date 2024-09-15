/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:01:48 by xlok              #+#    #+#             */
/*   Updated: 2024/08/03 20:06:55 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	parse_specifier(t_dpf *data)
{
	char	*s;

	s = "cspdiuxX%";
	while (*s)
	{
		if (*data->fmt_str == *s)
		{
			data->specifier = *s;
			data->fmt_str++;
			return ;
		}
		s++;
	}
}

static int	parse_int(t_dpf *data)
{
	int	i;

	i = 0;
	while (*data->fmt_str >= '0' && *data->fmt_str <= '9')
		i = (i * 10) + (*data->fmt_str++ - '0');
	return (i);
}

static bool	parse_flag(t_dpf *data)
{
	if (*data->fmt_str == '#')
		data->hash = 1;
	else if (*data->fmt_str == '0')
		data->zero = 1;
	else if (*data->fmt_str == '-')
		data->minus = 1;
	else if (*data->fmt_str == ' ')
		data->space = 1;
	else if (*data->fmt_str == '+')
		data->plus = 1;
	else
		return (0);
	return (1);
}

void	parse(t_dpf *data)
{
	while (parse_flag(data))
		data->fmt_str++;
	data->width = parse_int(data);
	if (*data->fmt_str == '.')
	{
		data->fmt_str++;
		if (*data->fmt_str == '-')
			data->precision = -1;
		else
			data->precision = parse_int(data);
	}
	parse_specifier(data);
}
