/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:21:07 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/06 09:36:08 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			c_char;

	c_char = c;
	while (*s)
	{
		if (*s == c_char)
			return ((char *)s);
		s++;
	}
	if (*s == c_char)
		return ((char *)s);
	return (0);
}
