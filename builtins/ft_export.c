/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:46:39 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/19 12:01:56 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	valid_cmd(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i++] != '_')
		return (FAIL);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '+')
	{
		i++;
		if (str[i] && str[i] != '=')
			return (FAIL);
		i++;
	}
	else if (str[i] && str[i] != '=')
		return (FAIL);
	return (SUCCESS);
}

int	addto_env(t_data *data, char *nw_envvar)
{
	int		n;
	char	**nw_env;
	char	*dup;

	dup = ft_strdup(nw_envvar);
	if (!dup)
		return (set_ec(EO_PROG, NULL));
	nw_env = malloc((tablen(data->env) + 2) * sizeof(char *));
	if (!nw_env)
		return (free(dup), set_ec(EO_PROG, NULL));
	n = -1;
	while (data->env[++n])
		nw_env[n] = data->env[n];
	nw_env[n++] = dup;
	nw_env[n] = NULL;
	free(data->env);
	data->env = nw_env;
	return (0);
}

int	update_env(t_data *data, int env_idx, char *env_var, char *to_exp)
{
	char	*str;

	str = ft_strjoin(env_var, to_exp);
	if (!str)
		return (set_ec(EO_PROG, NULL));
	free(data->env[env_idx]);
	data->env[env_idx] = str;
	return (0);
}

int	export_choose(t_data *data, char *to_exp)
{
	char	*str;
	int		env_idx;

	str = env_getkey(to_exp);
	if (!str)
		return (set_ec(EO_PROG, NULL));
	env_idx = env_getint(data, str);
	free(str);
	if (env_idx < 0)
		return (addto_env(data, to_exp));
	else if (ft_memchr(to_exp, '+', ft_strlen(to_exp)))
		return (update_env(data, env_idx, data->env[env_idx],
				env_getvalue(to_exp)));
	else if (ft_memchr(to_exp, '=', ft_strlen(to_exp))
		|| !ft_memchr(data->env[env_idx], '=', ft_strlen(data->env[env_idx])))
		return (update_env(data, env_idx, to_exp, NULL));
	return (0);
}

int	ft_export(t_data *data, char **cmd)
{
	int	ret;

	ret = 0;
	if (!*(cmd + 1))
		show_export(data);
	while (*(++cmd) && ret != EO_PROG)
	{
		if (valid_cmd(*cmd))
		{
			ret = 1;
			ft_putstr_fd("mini42: export: `", 2);
			ft_putstr_fd(*cmd, 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else
			ret = export_choose(data, *cmd);
	}
	g_sgn.ec = ret;
	if (g_sgn.ec < 0)
		perror(NULL);
	return (g_sgn.ec);
}
