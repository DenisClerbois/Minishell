/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:03:27 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/19 12:02:10 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	init(t_data *data)
{
	signal(SIGINT, sa_int);
	signal(SIGQUIT, SIG_IGN);
	g_sgn.here_doc = 0;
	g_sgn.signal = 0;
	data->heaxnode = NULL;
	data->heapnode = NULL;
	data->prompt = NULL;
	return (SUCCESS);
}

void	loop(t_data *data)
{
	while (TRUE)
	{
		init(data);
		data->prompt = readline("mini42-5.2$ ");
		if (!data->prompt)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (*data->prompt)
		{
			add_history(data->prompt);
			(lexx(data) || parsing(data) || execute(data, data->heapnode));
			theend(data);
			if (g_sgn.ec == EO_PROG)
				break ;
		}
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_data	data;

	if (argc != 1)
		return (1);
	(void)argv;
	data.env = dup_tab(envp);
	if (!data.env)
		return (set_ec(EO_PROG, NULL));
	if (init_env(&data))
		return (freetab(data.env), g_sgn.ec);
	loop(&data);
	freetab(data.env);
	return (1);
}
