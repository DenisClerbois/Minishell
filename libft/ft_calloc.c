/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:16:40 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/24 13:37:55 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*nw_memory;

	nw_memory = malloc(count * size);
	if (!nw_memory)
		return (NULL);
	ft_bzero(nw_memory, count * size);
	return (nw_memory);
}
