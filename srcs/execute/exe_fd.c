/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:20:54 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/19 17:54:23 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	output_chev(t_redirection *rd_stuff, t_fd *fd)
{
	int	open_settings;

	if (fd->out != 1)
		close(fd->out);
	open_settings = O_RDWR | O_CREAT | O_TRUNC;
	if (rd_stuff->num_red == DO_CHEV)
		open_settings = O_RDWR | O_CREAT | O_APPEND;
	fd->out = open(rd_stuff->filename, open_settings, 0644);
	if (fd->out < 0)
		return (FAIL);
	return (SUCCESS);
}

int	open_file(t_node *red_node, t_fd *fd)
{
	t_redirection	*rd_stuff;

	while (red_node)
	{
		rd_stuff = (t_redirection *)red_node->content;
		if (rd_stuff->num_red == SI_CHEV)
		{
			if (fd->in)
				close(fd->in);
			fd->in = open(rd_stuff->filename, O_RDONLY, 0644);
			if (fd->in < 0)
				return (set_ec(FAIL, rd_stuff->filename));
		}
		else if (output_chev(rd_stuff, fd))
			return (set_ec(FAIL, rd_stuff->filename));
		red_node = red_node->next;
	}
	return (SUCCESS);
}

int	duplicate(t_fd *fd)
{
	if (dup2(fd->in, STDIN) < 0 || dup2(fd->out, STDOUT) < 0)
	{
		if (fd->in != STDIN)
			close(fd->in);
		if (fd->out != STDOUT)
			close(fd->out);
		return (set_ec(EO_PROG, NULL));
	}
	return (SUCCESS);
}

int	pipe_tubes(t_dpipex *p_data, t_parse *parsed, t_fd *fd)
{
	if (parsed->p_i < p_data->n_pipe)
		close(p_data->pipe_fd[parsed->p_i][READ]);
	if (parsed->p_i)
	{
		if (fd->in == STDIN)
			fd->in = p_data->pipe_fd[parsed->p_i - 1][READ];
		else
			close(p_data->pipe_fd[parsed->p_i - 1][READ]);
	}
	if (parsed->p_i != p_data->n_pipe)
	{
		if (fd->out == STDOUT)
			fd->out = p_data->pipe_fd[parsed->p_i][WRITE];
		else
			close(p_data->pipe_fd[parsed->p_i][WRITE]);
	}
	if (duplicate(fd))
		return (EO_PROG);
	return (SUCCESS);
}
