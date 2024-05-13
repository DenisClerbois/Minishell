/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_more.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:25:37 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/16 12:13:18 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lexproof(t_data *data)
{
	t_node	*node;
	int		red;

	node = data->heaxnode;
	while (node)
	{
		red = tkn_gndr(node);
		if (red && red != PIPE)
		{
			if (!node->next || tkn_gndr(node->next))
			{
				ft_putstr_fd("mini42: syntax error near unexpected token `", 2);
				if (!node->next)
					ft_putstr_fd("newline", 2);
				else
					ft_putstr_fd((char *)(node->next)->content, 2);
				ft_putendl_fd("'", 2);
				g_sgn.ec = 2;
				return (g_sgn.ec);
			}
		}
		node = node->next;
	}
	return (SUCCESS);
}

int	lexx(t_data *data)
{
	int	p;

	if (lexer(data))
		return (g_sgn.ec);
	if (!data->heaxnode)
		return (SUCCESS);
	p = tkn_gndr(node_last(data->heaxnode));
	while (p == PIPE)
	{
		free(data->prompt);
		data->prompt = readline("> ");
		if (lexer(data))
			return (g_sgn.ec);
		p = tkn_gndr(node_last(data->heaxnode));
	}
	return (SUCCESS);
}
