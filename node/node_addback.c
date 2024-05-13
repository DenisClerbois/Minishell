/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_addback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:24:06 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:17:17 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	node_addback(t_node **node, t_node *new)
{
	if (!node)
		return ;
	else if (!(*node))
		*node = new;
	else
	{
		new->prev = node_last(*node);
		node_last(*node)->next = new;
	}
}
