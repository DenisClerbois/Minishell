/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:50:42 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/25 15:50:42 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*nw_s;
	int		i;

	if (!s || !f)
		return (NULL);
	nw_s = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!nw_s)
		return (NULL);
	i = -1;
	while (s[++i])
		nw_s[i] = (*f)(i, s[i]);
	nw_s[i] = '\0';
	return (nw_s);
}
