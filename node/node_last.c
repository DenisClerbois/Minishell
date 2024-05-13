/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_last.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:49:35 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:17:29 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

t_node	*node_last(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}
