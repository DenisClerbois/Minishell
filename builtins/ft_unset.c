/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:44:58 by abaccari          #+#    #+#             */
/*   Updated: 2024/02/15 14:34:35 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	delone_env(t_data *data, int rmv_idx)
{
	int		m;
	int		n;
	char	**nw_env;

	nw_env = malloc(tablen(data->env) * sizeof(char *));
	if (!nw_env)
		return (set_ec(EO_PROG, NULL));
	m = 0;
	n = 0;
	while (data->env[m])
	{
		if (rmv_idx != m)
			nw_env[n++] = data->env[m];
		m++;
	}
	nw_env[n] = NULL;
	free(data->env);
	data->env = nw_env;
	return (0);
}

int	ft_unset(t_data *data, char **cmd)
{
	int		i;
	int		rmv_idx;

	i = 0;
	while (cmd[++i])
	{
		rmv_idx = env_getint(data, cmd[i]);
		if (rmv_idx >= 0)
		{
			if (delone_env(data, rmv_idx))
				return (g_sgn.ec);
		}
	}
	return (0);
}
