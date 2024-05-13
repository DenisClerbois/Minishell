/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:43:38 by abaccari          #+#    #+#             */
/*   Updated: 2024/02/15 11:57:20 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_data *data, char **cmd)
{
	int	i;

	(void)cmd;
	i = -1;
	while (data->env && data->env[++i])
	{
		if (ft_memchr(data->env[i], '=', ft_strlen(data->env[i])))
			ft_putendl_fd(data->env[i], 1);
	}
	return (0);
}
