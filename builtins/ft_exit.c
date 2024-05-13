/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:28:52 by abaccari          #+#    #+#             */
/*   Updated: 2024/02/19 12:01:46 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	only_digit(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (!i && s[i] != '+' && s[i] != '-' && !ft_isdigit(s[i]))
			return (1);
		if (i && !ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_arg(char **cmd)
{
	int	i;

	i = -1;
	if (!only_digit(cmd[0]))
	{
		if (cmd[1])
			return (ft_putendl_fd("mini42: exit: too many arguments", 2), 1);
		else
			exit(ft_atoi(cmd[0]));
	}
	else
	{
		ft_putstr_fd("mini42: exit: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": numeric argument required", 2);
		g_sgn.ec = 2;
		exit(g_sgn.ec);
	}
	return (0);
}

int	ft_exit(t_data *data, char **cmd)
{
	(void)data;
	if (!cmd)
		return (-1);
	write(1, "exit\n", 5);
	if (!cmd[1])
		return (exit(g_sgn.ec), 0);
	else
		return (check_arg(&cmd[1]));
}
