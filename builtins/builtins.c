/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:56:26 by abaccari          #+#    #+#             */
/*   Updated: 2024/02/14 11:27:01 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	*is_builtins(char *cmd, t_parse **parsed)
{
	if (!cmd)
		return (NULL);
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1))
		(*parsed)->builtin = ft_echo;
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1))
		(*parsed)->builtin = ft_exit;
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1))
		(*parsed)->builtin = ft_cd;
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1))
		(*parsed)->builtin = ft_pwd;
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd) + 1))
		(*parsed)->builtin = ft_export;
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd) + 1))
		(*parsed)->builtin = ft_env;
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1))
		(*parsed)->builtin = ft_unset;
	return (NULL);
}
