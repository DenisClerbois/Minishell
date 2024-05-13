/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_delone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:49:18 by declerbo          #+#    #+#             */
/*   Updated: 2024/01/13 14:49:19 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	node_delone(t_node *node, void (*del)(void*))
{
	if (!node)
		return ;
	if (node->prev)
		(node->prev)->next = node->next;
	if (node->next)
		(node->next)->prev = node->prev;
	if (del)
		del(node->content);
	node->content = NULL;
	free(node);
}
