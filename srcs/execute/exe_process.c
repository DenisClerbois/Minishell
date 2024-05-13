/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:18:58 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/19 13:32:16 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	get_path(t_data *data, char *cmd, char **path)
{
	int		i;
	char	*env_adr;
	char	**env_tab;
	char	*cmd_slh;

	env_adr = env_getvalue(env_getstr(data, "PATH"));
	if (!env_adr)
		return (set_ec(EC_127, cmd));
	env_tab = ft_split(env_adr, ':');
	if (!env_tab)
		return (set_ec(EO_PROG, NULL));
	i = -1;
	cmd_slh = ft_strjoin("/", cmd);
	if (!cmd_slh)
		return (freetab(env_tab), set_ec(EO_PROG, NULL));
	while (env_tab[++i])
	{
		*path = ft_strjoin(env_tab[i], cmd_slh);
		if (!*path)
			return (free(cmd_slh), freetab(env_tab), set_ec(EO_PROG, NULL));
		if (!access(*path, F_OK | X_OK))
			return (free(cmd_slh), SUCCESS);
		free(*path);
	}
	return (free(cmd_slh), set_ec(EC_127, cmd));
}

static int	out_process(t_data *data, t_dpipex *p_data, t_fd fd, int exitcode)
{
	node_clear(&data->heaxnode, f_lexer);
	node_clear(&data->heapnode, f_parser);
	if (fd.in != STDIN)
		close(fd.in);
	if (fd.out != STDOUT)
		close(fd.out);
	free(p_data->pid);
	freetab(data->env);
	freetab_int(p_data->pipe_fd, p_data->n_process - 1);
	exit(exitcode);
}

void	process(t_data *data, t_dpipex *p_data, t_parse *parsed)
{
	char		*path;
	t_fd		fd;

	fd = (t_fd){0, 1};
	if (exp_red(parsed->red_head) || exp_cmd(data, parsed)
		|| open_file(parsed->red_head, &fd) || pipe_tubes(p_data, parsed, &fd))
		out_process(data, p_data, fd, g_sgn.ec);
	if (!parsed->cmd || !(parsed->cmd[0]))
		out_process(data, p_data, fd, SUCCESS);
	if (parsed->builtin)
		out_process(data, p_data, fd, parsed->builtin(data, parsed->cmd));
	if (!access(parsed->cmd[0], F_OK | X_OK)
		&& execve(parsed->cmd[0], parsed->cmd, data->env) == -1)
	{
		g_sgn.ec = exp_isdir(parsed->cmd[0]);
		out_process(data, p_data, fd, g_sgn.ec);
	}
	if (get_path(data, (parsed->cmd)[0], &path))
		out_process(data, p_data, fd, g_sgn.ec);
	execve(path, parsed->cmd, data->env);
	out_process(data, p_data, fd, EO_PROG);
}
