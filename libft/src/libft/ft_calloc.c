/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:14:04 by xlok              #+#    #+#             */
/*   Updated: 2024/05/30 21:27:57 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t ncells, size_t size)
{
	void	*temp;

	temp = malloc(ncells * size);
	if (!temp)
		return (0);
	ft_bzero(temp, ncells * size);
	return (temp);
}
