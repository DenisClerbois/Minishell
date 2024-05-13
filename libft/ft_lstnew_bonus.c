/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:35:59 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/24 15:35:59 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nw_node;

	nw_node = malloc(sizeof(t_list));
	if (!nw_node)
		return (0);
	nw_node->content = content;
	nw_node->next = 0;
	return (nw_node);
}
