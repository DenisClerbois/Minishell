/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:19:46 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/16 12:12:49 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

char	**dup_tab(char **tab)
{
	char	**tab_dup;
	char	*sub_str;
	int		i;

	tab_dup = malloc(sizeof(char *) * (tablen(tab) + 1));
	if (!tab_dup)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		sub_str = ft_strdup(tab[i]);
		if (!sub_str)
		{
			while (--i >= 0)
				free(tab_dup[i]);
			return (free(tab_dup), NULL);
		}
		tab_dup[i] = sub_str;
		i++;
	}
	tab_dup[i] = NULL;
	return (tab_dup);
}

int	size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int	set_ec(int ec, char *s)
{
	g_sgn.ec = ec;
	if (g_sgn.ec == 127)
	{
		ft_putstr_fd("mini42: ", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else
		perror(s);
	return (ec);
}

void	theend(t_data *data)
{
	if (data->heaxnode)
		node_clear(&data->heaxnode, f_lexer);
	if (data->heapnode)
		node_clear(&data->heapnode, f_parser);
	if (data->prompt)
		free(data->prompt);
}
