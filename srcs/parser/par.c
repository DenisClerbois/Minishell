/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:57:02 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:19:14 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	update_cmdtab(t_node *current, t_parse *parsed)
{
	int		i;
	char	**update_cmd;
	char	*tmp;

	if (!current || !parsed)
		return (set_ec(EO_PROG, WTH));
	update_cmd = malloc(sizeof(char *) * (size_tab(parsed->cmd) + 2));
	if (!update_cmd)
		return (set_ec(EO_PROG, NULL));
	tmp = ft_strdup((char *)current->content);
	if (!tmp)
		return (free(update_cmd), set_ec(EO_PROG, NULL));
	i = 0;
	while (parsed->cmd && parsed->cmd[i])
	{
		update_cmd[i] = parsed->cmd[i];
		i++;
	}
	if (parsed->cmd)
		free(parsed->cmd);
	update_cmd[i++] = tmp;
	update_cmd[i] = NULL;
	parsed->cmd = update_cmd;
	return (SUCCESS);
}

static int	nw_rnode(t_node **red_head, char *red, int gender)
{
	t_redirection	*redir_content;
	t_node			*node_red;

	redir_content = malloc(sizeof(t_redirection));
	if (!redir_content)
		return (set_ec(EO_PROG, NULL));
	redir_content->filename = ft_strdup(red);
	if (!redir_content->filename)
		return (free(redir_content), set_ec(EO_PROG, NULL));
	redir_content->num_red = gender;
	node_red = node_new(redir_content);
	if (!node_red)
		return (free(redir_content->filename), free(redir_content),
			set_ec(EO_PROG, NULL));
	node_addback(red_head, node_red);
	return (SUCCESS);
}

static int	add_pnode(t_node **heapnode, t_parse **parsed)
{
	t_node	*node_parsed;

	node_parsed = node_new((void *)*parsed);
	if (!node_parsed)
		return (f_parser(*parsed), set_ec(EO_PROG, NULL));
	node_addback(heapnode, node_parsed);
	*parsed = NULL;
	return (SUCCESS);
}

static int	parse_lxnode(t_node **hpnode, t_node **hxnode, t_parse **parsed)
{
	int	gndr;

	gndr = tkn_gndr(*hxnode);
	if (init_parsed(parsed, node_nb(*hpnode)))
		return (EO_PROG);
	if (gndr == PIPE && add_pnode(hpnode, parsed))
		return (EO_PROG);
	else if (!gndr)
	{
		if (*parsed && !(*parsed)->cmd)
			is_builtins((char *)((*hxnode)->content), parsed);
		if (update_cmdtab(*hxnode, *parsed))
			return (EO_PROG);
	}
	else if (gndr != PIPE && gndr)
	{
		if (nw_rnode(&((*parsed)->red_head), (*hxnode)->next->content, gndr))
			return (EO_PROG);
		*hxnode = (*hxnode)->next;
	}
	*hxnode = (*hxnode)->next;
	return (SUCCESS);
}

int	parsing(t_data *data)
{
	t_parse	*parsed;
	t_node	*hxnode;	

	parsed = NULL;
	hxnode = data->heaxnode;
	while (hxnode)
	{
		if (parse_lxnode(&(data->heapnode), &hxnode, &parsed))
		{
			if (parsed)
				f_parser(parsed);
			return (EO_PROG);
		}
	}
	if (parsed && add_pnode(&data->heapnode, &parsed))
		return (EO_PROG);
	return (SUCCESS);
}
