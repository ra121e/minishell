/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:21:55 by xlok              #+#    #+#             */
/*   Updated: 2024/08/06 19:13:59 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef FD_SIZE
#  define FD_SIZE 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

char	*gnl(int fd);
void	ft_free(char **p);
int		eof_nl(char *buf);
char	*strjoin(char const *s1, char const *s2);

#endif
