/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:26:35 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/06 09:36:00 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	c_char;
	char	*tmp;

	tmp = 0;
	c_char = c;
	while (*s)
	{
		if (*s == c_char)
			tmp = (char *)s;
		s++;
	}
	if (tmp)
		return (tmp);
	if (*s == c_char)
		return ((char *)s);
	return (0);
}
