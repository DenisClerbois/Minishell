/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:50:07 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/25 15:50:07 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_words(char const *s, char c)
{
	int		nb_w;
	int		ln_w;
	int		i;

	nb_w = 0;
	ln_w = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] != c)
			ln_w++;
		else if (ln_w)
		{
			nb_w++;
			ln_w = 0;
		}
	}
	if (ln_w)
		nb_w++;
	return (nb_w);
}

static int	allocate(char **nw_tab, int nb_w, int ln_w)
{
	nw_tab[nb_w] = malloc(sizeof(char) * (ln_w + 1));
	if (!nw_tab[nb_w])
	{
		while (--nb_w >= 0)
			free(nw_tab[nb_w]);
		free(nw_tab);
		return (0);
	}
	return (1);
}

static int	malloc_ln_w(char const *s, char c, char **nw_tab)
{
	int		nb_w;
	int		ln_w;
	int		i;

	nb_w = 0;
	ln_w = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] != c)
			ln_w++;
		else if (ln_w)
		{
			if (!allocate(nw_tab, nb_w, ln_w))
				return (0);
			nb_w++;
			ln_w = 0;
		}
	}
	if (ln_w)
	{
		if (!allocate(nw_tab, nb_w, ln_w))
			return (0);
	}
	return (1);
}

static void	spliting(char **nw_tab, char const *s, char c)
{
	int		nb_w;
	int		ln_w;
	int		i;

	nb_w = 0;
	ln_w = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			nw_tab[nb_w][ln_w++] = s[i];
		else if (ln_w)
		{
			nw_tab[nb_w][ln_w] = '\0';
			nb_w++;
			ln_w = 0;
		}
		i++;
	}
	if (ln_w)
		nw_tab[nb_w][ln_w] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char	**nw_tab;

	if (!s)
		return (NULL);
	nw_tab = malloc(sizeof(char *) * (nb_words(s, c) + 1));
	if (!nw_tab)
		return (NULL);
	if (malloc_ln_w(s, c, nw_tab))
		spliting(nw_tab, s, c);
	else
		return (NULL);
	nw_tab[nb_words(s, c)] = NULL;
	return (nw_tab);
}
