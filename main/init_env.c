/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaccari <abaccari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:54:59 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/18 15:26:50 by abaccari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	increase_sh_lvl(t_data *data)
{
	int		i;
	char	*val;
	int		shlvl_idx;

	i = 1;
	shlvl_idx = env_getint(data, "SHLVL");
	if (shlvl_idx < 0)
		return (addto_env(data, "SHLVL=1"));
	if (ft_atoi(env_getvalue(data->env[shlvl_idx])) >= 999)
		ft_putendl_fd("mini42: warning: shell level too high,resetting to 1",
			2);
	else
		i += ft_atoi(env_getvalue(data->env[shlvl_idx]));
	val = ft_itoa(i);
	if (!val)
		return (set_ec(EO_PROG, NULL));
	i = update_env(data, shlvl_idx, "SHLVL=", val);
	free(val);
	return (i);
}

int	set_pwd(t_data *data)
{
	char	pwd[1024];
	char	*nw_pwd;

	if (env_getstr(data, "PWD"))
		return (0);
	if (!getcwd(pwd, 1024))
		return (set_ec(EO_PROG, NULL));
	nw_pwd = ft_strjoin("PWD=", pwd);
	if (!nw_pwd)
		return (set_ec(EO_PROG, NULL));
	addto_env(data, nw_pwd);
	return (0);
}

int	init_env(t_data *data)
{
	if (set_pwd(data))
		return (g_sgn.ec);
	if (increase_sh_lvl(data))
		return (g_sgn.ec);
	if (!env_getstr(data, "_"))
		addto_env(data, "_=/usr/bin/env");
	return (0);
}
