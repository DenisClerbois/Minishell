/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:30:40 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/24 13:12:34 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_uchar;
	const unsigned char	*s2_uchar;
	unsigned int		i;

	if (!n)
		return (0);
	s1_uchar = (const unsigned char *)s1;
	s2_uchar = (const unsigned char *)s2;
	i = 0;
	while (i < n && s1_uchar[i] == s2_uchar[i])
		i++;
	if (i == n)
		return (0);
	return (s1_uchar[i] - s2_uchar[i]);
}
