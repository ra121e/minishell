/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:25:15 by xlok              #+#    #+#             */
/*   Updated: 2024/05/31 18:51:56 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*clear(t_list *lst, void (*del)(void *))
{
	ft_lstclear(&lst, del);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	void	*fp;
	t_list	*new;

	if (!lst || !f || !del)
		return (0);
	res = 0;
	while (lst)
	{
		fp = f(lst->content);
		if (!fp)
			return (clear(res, del));
		new = ft_lstnew(fp);
		if (!new)
		{
			del(fp);
			return (clear(res, del));
		}
		ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}
