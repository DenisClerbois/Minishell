/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:59:53 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/08 14:58:13 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	waiting_room(t_dpipex p_data, int nb_process)
{
	int		status;
	int		process_idx;
	int		flag;

	process_idx = -1;
	flag = 0;
	while (++process_idx <= nb_process)
	{
		waitpid(p_data.pid[process_idx], &status, 0);
		if (WEXITSTATUS(status) == EO_PROG)
			flag = 1;
	}
	if (!g_sgn.signal)
		g_sgn.ec = WEXITSTATUS(status);
	if (flag)
		g_sgn.ec = EO_PROG;
	return (free(p_data.pid), 
		freetab_int(p_data.pipe_fd, p_data.n_pipe), g_sgn.ec);
}

int	set_p_data(t_dpipex	*p_data, int nb_p)
{
	int	i;

	p_data->n_process = nb_p;
	p_data->n_pipe = nb_p - 1;
	p_data->pid = malloc(sizeof(pid_t) * p_data->n_process);
	if (!p_data->pid)
		return (FAIL);
	p_data->pipe_fd = malloc(sizeof(int *) * p_data->n_process - 1);
	if (!p_data->pipe_fd)
		return (free(p_data->pid), FAIL);
	i = 0;
	while (i < p_data->n_pipe)
	{
		p_data->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!p_data->pipe_fd[i])
			return (freetab_int(p_data->pipe_fd, i), free(p_data->pid), FAIL);
		i++;
	}
	return (SUCCESS);
}
