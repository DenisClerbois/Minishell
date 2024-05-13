/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:55:44 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/16 15:34:10 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../node/node.h"
# include "../libft/libft.h"

# include <sys/ioctl.h>

# include <signal.h>
# include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <stdlib.h>
# include <unistd.h>

# include <sys/wait.h>

# include <fcntl.h>

# include <sys/errno.h>

# define TRUE 1

# define FAIL 1
# define SUCCESS 0
# define EO_PROG -1
# define EC_127	127
# define EC_130 130
# define EC_139 139

# define READ 0
# define WRITE 1

# define SO_CHEV 1
# define SI_CHEV 2
# define DO_CHEV 3
# define HERE_DOC 4
# define PIPE 5

# define NB_SIGNAL 2
# define QUIT 0
# define INT 1
# define STDIN  0
# define STDOUT 1

# define CHILD 0

typedef struct s_signal
{
	int		ec;
	int		here_doc;
	int		signal;
	pid_t	pid;
}	t_signal;

t_signal	g_sgn;

typedef struct s_data
{
	char	*prompt;
	t_node	*heaxnode;
	t_node	*heapnode;
	char	**env;
}	t_data;

typedef struct s_quotes
{
	int	s;
	int	d;
}	t_quotes;

typedef struct s_parse
{
	int		(*builtin)(t_data *data, char **cmd);
	char	**cmd;
	t_node	*red_head;
	int		p_i;
}	t_parse;

typedef struct t_redirection
{
	char	*filename;
	int		num_red;
}	t_redirection;

typedef struct s_dpipex {
	pid_t	*pid;
	int		**pipe_fd;
	int		n_process;
	int		n_pipe;
}	t_dpipex;

int		lexx(t_data *data);
int		set_ec(int ec, char *s);
int		tkn_gndr(t_node *node);
int		parsing(t_data *data);
void	sa_int(int sig);
void	sa_quit(int sig);
int		tablen(char **tab);
char	**dup_tab(char **tab);
int		ft_envv(t_data *data, char **cmd);
void	f_parser(void *par);
void	f_red(void *content);
void	f_lexer(void *token);
void	freetab(char **tab);
void	theend(t_data *data);
int		size_tab(char **tab);
void	show_parsed_content(void *content);
void	show_lexed_content(void *str);
int		execute(t_data *data, t_node *heapnode);
int		init_env(t_data *data);

int		addto_env(t_data *data, char *nw_envvar);
int		update_env(t_data *data, int env_idx, char *env_var, char *to_exp);
char	*env_getvalue(char *str);
char	*env_getstr(t_data *data, char *needle);
int		env_getint(t_data *data, char *needle);

#endif