/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:00:04 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/13 11:21:09 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define SUCCESS 0
# define EO_PROG -1

# include <stdlib.h>
# include <stdio.h>
# include "../../libft/libft.h"
# include "../../node/node.h"
# include <readline/readline.h>
# include <readline/history.h>

# define PIPE 5

typedef struct s_quotes
{
	int	s;
	int	d;
}	t_quotes;

typedef struct s_data
{
	char	*prompt;
	t_node	*heaxnode;
	t_node	*heapnode;
	char	**env;
}	t_data;

typedef struct s_signal
{
	int		ec;
	pid_t	pid;
}	t_signal;

extern t_signal	g_sgn;

int	set_ec(int ec, char *s);
int	updotes(t_quotes *quotes, int c);
int	lexproof(t_data *data);
int	lexer(t_data *data);
int	tkn_gndr(t_node *node);

#endif