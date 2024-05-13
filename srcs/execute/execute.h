/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:22:49 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/19 13:31:27 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# include <sys/stat.h>

# include <sys/errno.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../../libft/libft.h"
# include "../../node/node.h"

# define FAIL 1
# define SUCCESS 0

# define EO_PROG -1
# define EC_127	127

# define SO_CHEV 1
# define SI_CHEV 2
# define DO_CHEV 3
# define HERE_DOC 4
# define PIPE 5

# define READ 0
# define WRITE 1

# define CHILD 0

# define STDIN  0
# define STDOUT 1

typedef struct s_data
{
	char		*prompt;
	t_node		*heaxnode;
	t_node		*heapnode;
	char		**env;
}	t_data;

typedef struct s_fd
{
	int	in;
	int	out;
}	t_fd;

typedef struct t_redirection
{
	char	*filename;
	int		num_red;
}	t_redirection;

typedef struct s_parse
{
	int		(*builtin)(t_data *data, char **cmd);
	char	**cmd;
	t_node	*red_head;
	int		p_i;
}	t_parse;

typedef struct s_dpipex {
	pid_t	*pid;
	int		**pipe_fd;
	int		n_process;
	int		n_pipe;
}	t_dpipex;

typedef struct s_signal
{
	int		ec;
	int		here_doc;
	int		signal;
}	t_signal;

extern t_signal	g_sgn;

void	f_parser(void *par);
void	f_lexer(void *token);
void	f_red(void *content);

void	freetab(char **tab);

int		exp_cmd(t_data *data, t_parse *parsed);
int		exp_red(t_node *rnode);
int		here_doc(t_node *heapnode);
int		pipe_tubes(t_dpipex *p_data, t_parse *parsed, t_fd *fd);
int		duplicate(t_fd *fd);
int		open_file(t_node *red_node, t_fd *fd);
int		get_path(t_data *data, char *cmd, char **path);
int		set_p_data(t_dpipex	*p_data, int nb_p);
int		waiting_room(t_dpipex p_data, int nb_process);
void	process(t_data *data, t_dpipex *p_data, t_parse *parsed);
int		set_ec(int ec, char *s);
void	freetab_int(int **tab, int size);
void	sa_quit(int sig);
void	sa_out(int sig);
int		execute(t_data *data, t_node *heapnode);
int		exp_isdir(char *cmd);
char	*env_getstr(t_data *data, char *needle);
char	*env_getvalue(char *str);

#endif
