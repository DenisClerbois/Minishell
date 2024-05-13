/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:51:02 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/25 15:51:02 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*test(char const *s)
{
	char	*nw_s;

	if (!s)
		return (NULL);
	nw_s = malloc(sizeof(char) * 1);
	if (!nw_s)
		return (NULL);
	nw_s[0] = '\0';
	return (nw_s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	ln;
	char			*nw_s;

	if (!s || start > ft_strlen(s) || !len)
		return (test(s));
	ln = 0;
	i = start;
	while (s[i++] && ln < len)
		ln++;
	nw_s = malloc(sizeof(char) * (ln + 1));
	if (!nw_s)
		return (NULL);
	i = 0;
	while (ln--)
		nw_s[i++] = s[start++];
	nw_s[i] = '\0';
	return (nw_s);
}
