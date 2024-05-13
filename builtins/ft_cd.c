/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:32:06 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/19 12:24:24 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_user_path(t_data *data)
{
	char	*env_val;
	char	*str;
	int		i;
	int		j;

	env_val = env_getvalue(env_getstr(data, "PWD"));
	i = -1;
	j = 0;
	while (env_val[++i] && j < 3)
	{
		if (env_val[i] == '/')
			j++;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (free(env_val), NULL);
	j = 0;
	i--;
	while (j < i)
	{
		str[j] = env_val[j];
		j++;
	}
	str[j] = '\0';
	return (free(env_val), str);
}

static int	find_and_move(t_data *data, char *dest)
{
	char	*env_val;

	env_val = env_getstr(data, dest);
	if (!env_val)
	{
		ft_putstr_fd("mini42: cd: ", 2);
		ft_putstr_fd(dest, 2);
		ft_putendl_fd(" not set", 2);
		return (1);
	}
	else if (!*env_getvalue(env_val))
		return (0);
	return (chdir(env_getvalue(env_val)));
}

static int	update_path(t_data *data)
{
	char	*pwd;
	char	tmp[1024];

	pwd = env_getstr(data, "PWD");
	if (pwd && env_getstr(data, "OLDPWD")
		&& update_env(data, env_getint(data, "OLDPWD"),
			"OLDPWD=", env_getvalue(pwd)))
		return (-1);
	if (pwd)
	{
		if (!getcwd(tmp, 1024))
			return (-1);
		if (update_env(data, env_getint(data, "PWD"), "PWD=", tmp))
			return (-1);
	}
	return (0);
}

static int	cd_mngmt(t_data *data, int ret, char *cmd)
{
	if (ret < 0)
	{
		ft_putstr_fd("mini42: cd: ", 2);
		if (!cmd)
			ft_putstr_fd(env_getvalue(env_getstr(data, "HOME")), 2);
		else if (!ft_strncmp(cmd, "-\0", 2))
			ft_putstr_fd(env_getvalue(env_getstr(data, "OLDPWD")), 2);
		else
			ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		ret = -ret;
	}
	else
	{
		if (update_path(data))
			return (-1);
	}
	return (ret);
}

int	ft_cd(t_data *data, char **cmd)
{
	char	*path;
	int		ret;

	if (!cmd[1])
		ret = find_and_move(data, "HOME");
	else if (cmd[2])
		return (ft_putendl_fd("mini42: cd: too many arguments", 2), 1);
	else
	{
		if (!ft_strncmp(cmd[1], "-\0", 2))
			ret = find_and_move(data, "OLDPWD");
		else if (!ft_strncmp(cmd[1], "~\0", 2))
		{
			path = get_user_path(data);
			if (!path)
				return (set_ec(EO_PROG, NULL));
			ret = chdir(path);
			free(path);
		}
		else
			ret = chdir(cmd[1]);
	}
	return (cd_mngmt(data, ret, cmd[1]));
}
