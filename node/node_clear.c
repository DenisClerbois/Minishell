/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:49:08 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:17:19 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	node_clear(t_node **node, void (*del)(void*))
{
	t_node	*tmp_node;

	if (!node || !del || !(*node))
		return ;
	while ((*node)->next)
	{
		tmp_node = (*node)->next;
		node_delone(*node, del);
		*node = tmp_node;
	}
	node_delone(*node, del);
	*node = NULL;
}
