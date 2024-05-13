/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:12:46 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:18:40 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	init_parsed(t_parse **parsed, int n)
{
	if (!*parsed)
	{
		*parsed = malloc(sizeof(t_parse));
		if (!*parsed)
			return (set_ec(EO_PROG, NULL));
		(*parsed)->cmd = NULL;
		(*parsed)->red_head = NULL;
		(*parsed)->builtin = NULL;
		(*parsed)->p_i = n;
	}
	return (SUCCESS);
}

int	tkn_gndr(t_node *node)
{
	int		ln;
	int		add;
	char	*token;

	if (!node)
		return (-1);
	add = 0;
	token = (char *)node->content;
	ln = ft_strlen(node->content);
	if (ln == 1 || ln == 2)
	{
		if (ln == 2 && token[0] == token[1])
			add = 2;
		if (token[0] == '|')
			return (5);
		else if (token[0] == '<')
			return (2 + add);
		else if (token[0] == '>')
			return (1 + add);
	}
	return (0);
}
