/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:21:57 by xlok              #+#    #+#             */
/*   Updated: 2024/08/10 13:12:34 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>

typedef struct s_data
{
	int				fd;
	const char		*fmt_str;
	const char		*base;
	va_list			ap;
	bool			hash;
	bool			zero;
	bool			minus;
	bool			space;
	bool			plus;
	int				width;
	int				precision;
	char			specifier;
	int				char_written;
	int				len;
	char			*pnum;
	int				plen;
	int				i;
	int				di;
	int				temp_di;
	unsigned int	ux;
	unsigned int	temp_ux;
}	t_dpf;

int		ft_dprintf(int fd, const char *str, ...);
void	dpf_init(t_dpf *data);
void	parse(t_dpf *data);
void	fs_padding(t_dpf *data);
void	fs_putnbr(t_dpf *data);
void	fs_c(t_dpf *data);
void	fs_s(t_dpf *data);
void	fs_p(t_dpf *data);
void	fs_di(t_dpf *data);
void	fs_di_printnum(t_dpf *data);
void	fs_u(t_dpf *data);
void	fs_u_printnum(t_dpf *data);
void	fs_x(t_dpf *data);
void	fs_x_printnum(t_dpf *data);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);

#endif
