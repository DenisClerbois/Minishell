/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:44:56 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/21 16:12:08 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr_uchar;
	unsigned int	i;

	ptr_uchar = (unsigned char *)b;
	i = 0;
	while (i < len)
		ptr_uchar[i++] = (unsigned char)c;
	return (b);
}
