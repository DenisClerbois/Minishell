/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:49:47 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:17:34 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

t_node	*node_new(void *content)
{
	t_node	*nw_node;

	nw_node = malloc(sizeof(t_node));
	if (!nw_node)
		return (NULL);
	nw_node->content = content;
	nw_node->next = NULL;
	nw_node->prev = NULL;
	return (nw_node);
}
