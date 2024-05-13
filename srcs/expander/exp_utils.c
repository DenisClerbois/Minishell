/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:25:49 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/18 20:38:11 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	rmv_q(char *s)
{
	int			i;
	int			j;
	t_quotes	quotes;

	i = 0;
	j = 0;
	quotes = (t_quotes){0, 0};
	while (s && s[i])
	{
		if (!updotes(&quotes, s[i]))
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}

char	**tabmerge(char **tab1, char **tab2)
{
	char	**nw_tab;
	int		i;
	int		j;

	nw_tab = malloc(sizeof(char *) * (size_tab(tab1) + size_tab(tab2) + 1));
	if (!nw_tab)
		return (freetab(tab1), freetab(tab2), NULL);
	i = 0;
	while (tab1 && tab1[i])
	{
		nw_tab[i] = tab1[i];
		i++;
	}
	j = -1;
	while (tab2 && tab2[++j])
		nw_tab[i++] = tab2[j];
	nw_tab[i] = NULL;
	return (free(tab1), free(tab2), nw_tab);
}

int	update_tab(t_parse *parsed)
{
	int		i;
	char	**tmp_tab;
	char	**nw_tab;

	i = -1;
	nw_tab = NULL;
	while (parsed->cmd && parsed->cmd[++i])
	{
		tmp_tab = msplit(parsed->cmd[i], ' ');
		if (!tmp_tab)
			return (freetab(nw_tab), EO_PROG);
		nw_tab = tabmerge(nw_tab, tmp_tab);
		if (!nw_tab)
			return (EO_PROG);
	}
	freetab(parsed->cmd);
	parsed->cmd = nw_tab;
	i = -1;
	while (parsed->cmd && parsed->cmd[++i])
		rmv_q(parsed->cmd[i]);
	return (SUCCESS);
}

int	exp_isdir(char *cmd)
{
	struct stat	info;

	if (!stat(cmd, &info))
	{
		if (S_ISDIR(info.st_mode))
		{
			ft_putstr_fd("mini42: ", 2);
			ft_putstr_fd(cmd, 2);
			if (!ft_memchr(cmd, '/', ft_strlen(cmd)))
				return (ft_putstr_fd(": command not found\n", 2), 127);
			ft_putstr_fd(" is a direcotry\n ", 2);
		}
	}
	return (126);
}
