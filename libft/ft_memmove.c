/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:36:32 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/25 14:04:58 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	char			*dst_char;
	const char		*src_char;

	if (!dst && !src)
		return (NULL);
	dst_char = (char *)dst;
	src_char = (const char *)src;
	i = 0;
	if (src_char < dst_char)
	{
		while (len--)
			dst_char[len] = src_char[len];
	}
	else
	{
		while (i < len)
		{
			dst_char[i] = src_char[i];
			i++;
		}
	}
	return (dst);
}
