/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:50:53 by declerbo          #+#    #+#             */
/*   Updated: 2023/04/25 15:50:53 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;

	if (!s1 || !set)
		return (NULL);
	else if (!ft_strlen(s1))
		return (ft_strdup(""));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > 0 && end < ft_strlen(s1) && ft_strchr(set, s1[end]))
		end--;
	if (start <= end)
		return (ft_substr(s1, start, end - start + 1));
	else
		return (ft_strdup(""));
}
