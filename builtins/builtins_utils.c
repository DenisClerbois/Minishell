/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:01:32 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/19 12:01:29 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env_getint(t_data *data, char *needle)
{
	int	i;
	int	j;

	i = -1;
	while (data->env[++i])
	{
		j = 0;
		while (data->env[i][j] != '=' && needle[j]
			&& data->env[i][j] == needle[j])
			j++;
		if (!needle[j] && (data->env[i][j] == '=' || !data->env[i][j]))
			return (i);
	}
	return (-1);
}

char	*env_getstr(t_data *data, char *needle)
{
	int	i;
	int	j;

	i = -1;
	while (data->env[++i])
	{
		j = 0;
		while (data->env[i][j] != '=' && needle[j]
			&& data->env[i][j] == needle[j])
			j++;
		if (!needle[j] && (data->env[i][j] == '=' || !data->env[i][j]))
			return (data->env[i]);
	}
	return (NULL);
}

char	*env_getvalue(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	return (&str[++i]);
}

char	*env_getkey(char *str)
{
	int		i;
	int		j;
	char	*nw_str;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	nw_str = malloc(sizeof(char) * (i + 1));
	if (!nw_str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		nw_str[j] = str[j];
		j++;
	}
	nw_str[j] = '\0';
	return (nw_str);
}
