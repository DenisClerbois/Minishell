/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:49:04 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/25 15:49:04 by declerbo         ###   ########.fr       */
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

char	*ft_itoa(int n)
{
	char	*n_str;
	int		ng;
	int		i;
	int		s;

	ng = 0;
	if (n < 0)
		ng++;
	s = size(n);
	n_str = malloc(sizeof(char) * (s + 1 + ng));
	if (!n_str)
		return (NULL);
	i = 0;
	if (n < 0)
		n_str[i++] = '-';
	while (s)
	{
		if (ng)
			n_str[i++] = -(n / ten_pw_x(s)) + '0';
		else
			n_str[i++] = (n / ten_pw_x(s)) + '0';
		n = n % ten_pw_x(s--);
	}
	n_str[i] = '\0';
	return (n_str);
}
