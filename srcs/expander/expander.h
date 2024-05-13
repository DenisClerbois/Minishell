/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:25:19 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/19 13:06:41 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# define FAIL 1
# define SUCCESS 0
# define EO_PROG -1

# include <sys/stat.h>
# include <stdlib.h>
# include "../../libft/libft.h"
# include "../../node/node.h"

typedef struct s_data
{
	char		*prompt;
	t_node		*heaxnode;
	t_node		*heapnode;
	char		**env;
}	t_data;

typedef struct t_redirection
{
	char	*filename;
	int		num_red;
}	t_redirection;

typedef struct s_parse
{
	int		(*builtin)(char **tab);
	char	**cmd;
	t_node	*red_head;
	int		p_i;
}	t_parse;

typedef struct s_quotes
{
	int	s;
	int	d;
}	t_quotes;

typedef struct s_signal
{
	int		ec;
	pid_t	pid;
}	t_signal;

extern t_signal	g_sgn;

void	rmv_q(char *s);
void	freetab(char **tab);
int		size_tab(char **tab);
int		updotes(t_quotes *quotes, int c);
char	**msplit(char const *s, char c);
int		exp_red(t_node *rnode);
int		set_ec(int ec, char *s);
void	show_tab(char **tab);
int		update_tab(t_parse *parsed);
char	*env_getstr(t_data *data, char *needle);
char	*env_getvalue(char *str);
char	**tabmerge(char **tab1, char **tab2);

#endif
