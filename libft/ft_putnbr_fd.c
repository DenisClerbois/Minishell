/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:49:54 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/25 15:49:54 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size(int n)
{
	int		i;

	if (!n)
		return (1);
	i = 0;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static int	ten_pw_x(int x)
{
	int		i;

	i = 1;
	if (!x)
		return (0);
	while (--x)
		i = i * 10;
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		ng;
	int		s;
	char	m;

	ng = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		ng = 1;
	}
	s = size(n);
	while (s)
	{
		if (ng)
			m = -(n / ten_pw_x(s)) + '0';
		else
			m = (n / ten_pw_x(s)) + '0';
		write(fd, &m, 1);
		n = n % ten_pw_x(s);
		s--;
	}
}
