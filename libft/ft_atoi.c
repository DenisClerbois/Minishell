/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:27:08 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/19 13:50:16 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		cnt;
	int		res;

	i = 0;
	cnt = 0;
	res = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			cnt++;
		i++;
	}
	while (str[i] < 58 && str[i] > 47)
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (cnt % 2)
		res = res * -1;
	return (res);
}
