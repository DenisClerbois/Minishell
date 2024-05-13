/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:29:46 by abaccari          #+#    #+#             */
/*   Updated: 2024/02/13 11:07:48 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_data *data, char **cmd)
{
	char	pwd[1024];

	(void)cmd;
	(void)data;
	if (!getcwd(pwd, 1024))
		return (-1);
	ft_putendl_fd(pwd, 1);
	return (0);
}
