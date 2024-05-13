/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:01:21 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:18:25 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	updotes(t_quotes *quotes, int c)
{
	if (c == '\'' && !(quotes->d % 2))
		return (++quotes->s);
	if (c == '\"' && !(quotes->s % 2))
		return (++quotes->d);
	return (SUCCESS);
}

static char	isoneof(char c, char *keys)
{
	while (keys && *keys)
	{
		if (*keys == c)
			return (*keys);
		keys++;
	}
	return (SUCCESS);
}

static int	nw_xnode(char *prompt, int beg, int ln, t_node **heaxnode)
{
	char	*token;
	t_node	*node;

	token = ft_substr(prompt, beg, ln);
	if (!token)
		return (set_ec(EO_PROG, NULL));
	node = node_new((void *)token);
	if (!node)
		return (free(token), set_ec(EO_PROG, NULL));
	node_addback(heaxnode, node);
	return (SUCCESS);
}

static int	sep_time(t_node **heaxnode, char *prompt, int *cur, int *len)
{
	if (*len && nw_xnode(prompt, *cur - *len, *len, heaxnode))
		return (EO_PROG);
	if (isoneof(prompt[*cur], "<>") && prompt[*cur] == prompt[*cur + 1])
	{
		if (nw_xnode(prompt, *cur, 2, heaxnode))
			return (EO_PROG);
		*cur += 1;
	}
	else if (prompt[*cur] != ' ' && prompt[*cur] != '\x09'
		&& nw_xnode(prompt, *cur, 1, heaxnode))
		return (EO_PROG);
	*len = -1;
	return (SUCCESS);
}

int	lexer(t_data *data)
{
	int			cur;
	int			len;
	t_quotes	quotes;

	cur = -1;
	len = 0;
	quotes = (t_quotes){0, 0};
	while (data->prompt && data->prompt[++cur])
	{
		updotes(&quotes, data->prompt[cur]);
		if (!(quotes.d % 2 || quotes.s % 2)
			&& isoneof(data->prompt[cur], "|<> \x09"))
		{
			if (sep_time(&data->heaxnode, data->prompt, &cur, &len))
				return (EO_PROG);
		}
		len++;
	}
	if (len && nw_xnode(data->prompt, cur - len, len, &data->heaxnode))
		return (EO_PROG);
	if (lexproof(data))
		return (g_sgn.ec);
	return (SUCCESS);
}
