/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:35:26 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/24 16:35:26 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode;
	t_list	*node;
	void	*nwcontent;

	if (!lst || !f || !del)
		return (0);
	node = 0;
	while (lst)
	{
		nwcontent = f(lst->content);
		newnode = ft_lstnew(nwcontent);
		if (!newnode)
		{
			ft_lstclear(&node, del);
			del(nwcontent);
			return (0);
		}
		ft_lstadd_back(&node, newnode);
		lst = lst->next;
	}
	return (node);
}
