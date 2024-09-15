/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:25:33 by xlok              #+#    #+#             */
/*   Updated: 2024/08/06 19:12:58 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static char	*loop(int fd, char *stash)
{
	char	*buf;
	char	*tmp;
	ssize_t	readbyte;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	while (1)
	{
		readbyte = read(fd, buf, BUFFER_SIZE);
		if (readbyte == -1)
			return (ft_free(&buf), NULL);
		if (readbyte == 0)
			break ;
		buf[readbyte] = 0;
		tmp = stash;
		stash = strjoin(tmp, buf);
		ft_free(&tmp);
		if (eof_nl(buf))
			break ;
	}
	ft_free(&buf);
	return (stash);
}

static char	*result(char **rl)
{
	char	*stash;
	char	*tmp;
	size_t	i;

	i = 0;
	while ((*rl)[i] && (*rl)[i] != '\n')
		i++;
	if (!(*rl)[i] || !(*rl)[i + 1])
		return (0);
	stash = ft_strdup(*rl + i + 1);
	if (!stash)
		return (ft_free(&stash), NULL);
	(*rl)[i + 1] = 0;
	tmp = *rl;
	*rl = ft_strdup(tmp);
	if (!*rl)
		return (ft_free(&stash), ft_free(&tmp), NULL);
	ft_free(&tmp);
	return (stash);
}

char	*gnl(int fd)
{
	static char	*stash[FD_SIZE];
	char		*rl;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= FD_SIZE)
		return (0);
	rl = loop(fd, stash[fd]);
	if (!rl)
		return (ft_free(&stash[fd]), NULL);
	stash[fd] = result(&rl);
	return (rl);
}
