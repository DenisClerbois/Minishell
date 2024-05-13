/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:14:23 by abaccari          #+#    #+#             */
/*   Updated: 2024/02/13 11:04:38 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	no_nwline(char *cmd)
{
	if (!cmd || *cmd != '-')
		return (0);
	while (*(++cmd))
	{
		if (*cmd != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(t_data *data, char **cmd)
{
	int	nwline;
	int	i;

	(void)data;
	nwline = no_nwline(cmd[1]);
	i = nwline;
	while (cmd[++i])
	{
		if (i - nwline != 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(cmd[i], 1);
	}
	if (!nwline)
		ft_putendl_fd("", 1);
	return (0);
}
