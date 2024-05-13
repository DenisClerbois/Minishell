/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:50:31 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/25 15:50:31 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	ln_s1;
	unsigned int	ln_s2;
	char			*nw;

	ln_s1 = ft_strlen(s1);
	ln_s2 = ft_strlen(s2);
	nw = malloc(sizeof(char) * (ln_s1 + ln_s2 + 1));
	if (!nw)
		return (NULL);
	i = 0;
	while (i < ln_s1)
	{
		nw[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ln_s2)
		nw[i++] = s2[j++];
	nw[i] = '\0';
	return (nw);
}
