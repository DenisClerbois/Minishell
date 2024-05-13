/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:09:36 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/21 15:56:16 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_char;
	unsigned int	i;

	s_char = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_char[i] == (unsigned char)c)
			return ((void *)&s_char[i]);
		i++;
	}
	return (NULL);
}
