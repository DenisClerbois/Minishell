/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_red.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:45 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:14:20 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	ambiguous(char *str, char *var_name)
{
	while (str && *str)
	{
		if (*str == ' ')
		{
			g_sgn.ec = FAIL;
			write(2, "$", 1);
			ft_putstr_fd(var_name, 2);
			ft_putendl_fd(": ambiguous redirect", 2);
			return (FAIL);
		}
		str++;
	}
	return (SUCCESS);
}

static int	replace(char **token, char *subs, int beg, int end)
{
	int		i;
	char	*nw_token;

	i = -1;
	nw_token = malloc(sizeof(char) * 
			(beg + ft_strlen(subs) + ft_strlen(&(*token)[end + 1]) + 1));
	if (!nw_token)
		return (EO_PROG);
	i = -1;
	while (++i < beg)
		nw_token[i] = (*token)[i];
	while (subs && *subs)
		nw_token[i++] = *subs++;
	while ((*token)[++end])
		nw_token[i++] = (*token)[end];
	nw_token[i] = '\0';
	free(*token);
	*token = nw_token;
	return (SUCCESS);
}

static int	update_token(char **token, int beg, int end)
{
	char	*var_name;
	char	*subs;
	int		ret_rep;

	var_name = ft_substr(*token, beg + 1, end - beg);
	if (!var_name)
		return (set_ec(EO_PROG, NULL));
	subs = ft_strdup(getenv(var_name));
	free(var_name);
	if (!subs)
		return (set_ec(EO_PROG, NULL));
	if (ambiguous(subs, var_name))
		return (FAIL);
	ret_rep = replace(token, subs, beg, end);
	free(subs);
	if (ret_rep)
		return (set_ec(EO_PROG, NULL));
	return (SUCCESS);
}

static int	expansion(char **token)
{
	int		s_quote;
	int		i;
	int		j;

	i = -1;
	s_quote = 0;
	while ((*token) && (*token)[++i])
	{
		if ((*token)[i] == '\'')
			s_quote++;
		else if (!(s_quote % 2) && (*token)[i] == '$')
		{
			j = i;
			while ((*token)[j + 1] && (ft_isalnum((*token)[j + 1])
				|| (*token)[j + 1] == '_'))
				j++;
			if (j != i && update_token(token, i, j))
				return (g_sgn.ec);
		}
	}
	return (SUCCESS);
}

int	exp_red(t_node *rnode)
{
	t_redirection	*red;

	while (rnode)
	{
		red = (t_redirection *)rnode->content;
		if (expansion(&(red->filename)))
			return (g_sgn.ec);
		rmv_q(red->filename);
		rnode = rnode->next;
	}
	return (SUCCESS);
}
