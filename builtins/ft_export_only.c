/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_only.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:37:02 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/16 15:17:52 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	**dup_tab(char **tab)
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

static void	bubblesort(char **tab)
{
	int		i;
	int		j;
	int		ln_tab;
	int		ln;
	char	*tmp;

	ln = tablen(tab) - 1;
	ln_tab = tablen(tab) - 1;
	j = 0;
	while (j < ln)
	{
		i = 0;
		while (i < ln_tab)
		{
			if (ft_strncmp(tab[i], tab[i + 1], -1) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
			}
			i++;
		}
		ln_tab--;
		j++;
	}
}

int	show_export(t_data *data)
{
	int		i;
	char	**tmp_tab;
	char	*tmp;

	tmp_tab = dup_tab(data->env);
	if (!tmp_tab)
		return (set_ec(EO_PROG, NULL));
	bubblesort(tmp_tab);
	i = -1;
	while (tmp_tab && tmp_tab[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		tmp = env_getkey(tmp_tab[i]);
		ft_putstr_fd(tmp, 1);
		free(tmp);
		if (ft_memchr(tmp_tab[i], '=', ft_strlen(tmp_tab[i])))
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env_getvalue(tmp_tab[i]), 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putendl_fd("", 1);
	}
	freetab(tmp_tab);
	return (0);
}
