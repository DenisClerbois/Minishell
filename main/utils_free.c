/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:42:28 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:17:00 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	freetab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	freetab_int(int **tab, int size)
{
	if (!tab)
		return ;
	while (--size > 0)
		free(tab[size]);
	free(tab);
}

void	f_lexer(void *token)
{
	free((char *)token);
}

void	f_red(void *content)
{
	t_redirection	*red_content;

	red_content = (t_redirection *)content;
	free(red_content->filename);
}

void	f_parser(void *par)
{
	t_parse	*parsed;

	parsed = (t_parse *)par;
	freetab(parsed->cmd);
	node_clear(&parsed->red_head, f_red);
}
