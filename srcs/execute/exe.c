/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 08:09:32 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/19 12:02:51 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	exe_mainpr(t_data *data, t_parse *parsed)
{
	t_fd	fd;
	int		og_infd;
	int		og_outfd;

	og_infd = dup(STDIN_FILENO);
	og_outfd = dup(STDOUT_FILENO);
	fd = (t_fd){0, 1};
	if (exp_red(parsed->red_head) || exp_cmd(data, parsed)
		|| open_file(parsed->red_head, &fd) || duplicate(&fd))
		return (g_sgn.ec);
	g_sgn.ec = parsed->builtin(data, parsed->cmd);
	dup2(og_infd, STDIN_FILENO);
	close(og_infd);
	dup2(og_outfd, STDOUT_FILENO);
	close(og_outfd);
	return (g_sgn.ec);
}

static int	multi_process(t_data *data, t_node *heapnode)
{
	t_dpipex	p_data;
	t_parse		*parsed;

	signal(SIGQUIT, sa_quit);
	signal(SIGINT, sa_out);
	if (set_p_data(&p_data, node_nb(heapnode)))
		return (set_ec(EO_PROG, NULL));
	while (heapnode)
	{
		parsed = (t_parse *)(heapnode->content);
		if (parsed->p_i < p_data.n_pipe
			&& pipe(p_data.pipe_fd[parsed->p_i]) < 0)
			return (waiting_room(p_data, parsed->p_i - 1));
		p_data.pid[parsed->p_i] = fork();
		if (p_data.pid[parsed->p_i] < 0)
			return (waiting_room(p_data, parsed->p_i - 1));
		else if (p_data.pid[parsed->p_i] == CHILD)
			process(data, &p_data, parsed);
		if (parsed->p_i < p_data.n_pipe)
			close(p_data.pipe_fd[parsed->p_i][WRITE]);
		if (parsed->p_i > 0)
			close(p_data.pipe_fd[parsed->p_i - 1][READ]);
		heapnode = heapnode->next;
	}
	return (waiting_room(p_data, parsed->p_i));
}

int	execute(t_data *data, t_node *heapnode)
{
	t_parse		*parsed;

	if (!heapnode)
		return (FAIL);
	parsed = (t_parse *)(heapnode->content);
	if (here_doc(heapnode) == EO_PROG)
		return (g_sgn.ec);
	if (parsed->builtin && !heapnode->next)
		return (exe_mainpr(data, parsed));
	else
		return (multi_process(data, data->heapnode));
}
