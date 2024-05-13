/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:22:55 by abaccari          #+#    #+#             */
/*   Updated: 2024/02/19 11:18:24 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../node/node.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define EO_PROG -1

# define FAIL 1
# define SUCCESS 0

typedef struct s_data
{
	char		*prompt;
	t_node		*heaxnode;
	t_node		*heapnode;
	char		**env;
}				t_data;

typedef struct s_parse
{
	int			(*builtin)(t_data *data, char **cmd);
	char		**cmd;
	t_node		*red_head;
	int			p_i;
}				t_parse;

typedef struct s_signal
{
	int			ec;
	int			here_doc;
	int			signal;
}				t_signal;

extern t_signal	g_sgn;

int		tablen(char **tab);
int		set_ec(int ec, char *s);
void	freetab(char **tab);
int		env_getint(t_data *data, char *needle);
char	*env_getstr(t_data *data, char *needle);
char	*env_getvalue(char *str);
char	*env_getkey(char *str);
char	*env_getvalueptr(char *str);

int		show_export(t_data *data);

int		ft_cd(t_data *data, char **cmd);
int		ft_echo(t_data *data, char **cmd);
int		ft_env(t_data *data, char **cmd);
int		ft_exit(t_data *data, char **cmd);
int		ft_export(t_data *data, char **cmd);
int		ft_pwd(t_data *data, char **cmd);
int		ft_unset(t_data *data, char **cmd);
int		update_env(t_data *data, int env_idx, char *env_var, char *to_exp);

#endif