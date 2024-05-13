/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:52:52 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/18 20:37:55 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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

static int	update_token(t_data *data, char **token, int beg, int end)
{
	char	*var_name;
	char	*subs;

	if ((*token)[beg + 1] == '?')
	{
		end++;
		subs = ft_itoa(g_sgn.ec);
	}
	else
	{
		var_name = ft_substr(*token, beg + 1, end - beg);
		if (!var_name)
			return (EO_PROG);
		subs = ft_strdup(env_getvalue(env_getstr(data, var_name)));
		free(var_name);
	}
	if (!subs)
		return (EO_PROG);
	if (replace(token, subs, beg, end))
		return (free(subs), EO_PROG);
	free(subs);
	return (SUCCESS);
}

static int	expand(t_data *data, char **token)
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
			while (ft_isalnum((*token)[j + 1]) || (*token)[j + 1] == '_')
				j++;
			if (j != i || ((*token)[j] && (*token)[j + 1] == '?'))
			{
				if (update_token(data, token, i, j))
					return (EO_PROG);
				s_quote = 0;
				i = -1;
			}
		}
	}
	return (SUCCESS);
}

int	exp_cmd(t_data *data, t_parse *parsed)
{
	int	i;

	i = -1;
	while (parsed->cmd && parsed->cmd[++i])
	{
		if (expand(data, &parsed->cmd[i]))
			return (set_ec(EO_PROG, NULL));
	}
	if (update_tab(parsed))
		return (set_ec(EO_PROG, NULL));
	return (SUCCESS);
}
