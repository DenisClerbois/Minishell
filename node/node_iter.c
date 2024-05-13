/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:49:27 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:17:27 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	node_iter(t_node *node, void (*f)(void *))
{
	if (!node || !f)
		return ;
	while (node)
	{
		f((void *)node->content);
		node = node->next;
	}
}
