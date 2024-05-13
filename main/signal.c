/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:03:31 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:16:27 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	sa_int(int sig)
{
	(void)sig;
	g_sgn.ec = EC_130;
	g_sgn.signal = 1;
	if (g_sgn.here_doc)
		ioctl(STDIN_FILENO, TIOCSTI, "\x0A");
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sgn.signal = 0;
	}
}

void	sa_out(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_sgn.signal = 1;
	g_sgn.ec = 130;
}

void	sa_quit(int sig)
{
	(void)sig;
	ft_putendl_fd("Quit: 3", 1);
	g_sgn.signal = 1;
	g_sgn.ec = 131;
}
