/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:23:13 by declerbo          #+#    #+#             */
/*   Updated: 2024/01/13 15:13:14 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

typedef struct s_node {
	void			*content;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

t_node	*node_new(void *content);
t_node	*node_last(t_node *node);
t_node	*node_getn(t_node *node, int n);
void	node_clear(t_node **node, void (*del)(void*));
void	node_delone(t_node *node, void (*del)(void*));
void	node_iter(t_node *node, void (*f)(void *));
void	node_addback(t_node **node, t_node *new);
int		node_nb(t_node *node);

#endif