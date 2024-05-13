/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:26:17 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:21:13 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include "../../libft/libft.h"
# include "../../node/node.h"

# define WTH "How the hell did you arrive there ?"
# define EO_PROG -1
# define SUCCESS 0

# define PIPE 5

typedef struct t_redirection
{
	char	*filename;
	int		num_red;
}	t_redirection;

typedef struct s_data
{
	char	*prompt;
	t_node	*heaxnode;
	t_node	*heapnode;
	char	**env;
}	t_data;

typedef struct s_parse
{
	int		(*builtin)(t_data *data, char **cmd);
	char	**cmd;
	t_node	*red_head;
	int		p_i;
}	t_parse;

typedef struct s_signal
{
	int		ec;
	pid_t	pid;
}	t_signal;

extern t_signal	g_sgn;

int		tkn_gndr(t_node *node);
int		init_parsed(t_parse **parsed, int n);

int		size_tab(char **tab);
void	freetab(char **tab);
void	f_parser(void *par);
void	f_red(void *content);
int		set_ec(int ec, char *s);

void	*is_builtins(char *cmd, t_parse **parsed);

#endif