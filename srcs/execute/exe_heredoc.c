/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: declerbo <declerbo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:41:19 by declerbo          #+#    #+#             */
/*   Updated: 2024/02/19 12:04:44 by declerbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	mread(char **prompt, char *stop_word)
{
	*prompt = readline("> ");
	if (g_sgn.signal)
		return (FAIL);
	else if (!(*prompt))
	{
		ft_putstr_fd(
			"warning: here-document delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(stop_word, 2);
		ft_putendl_fd("\')\"", 2);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	open_tmp_file(int p_n, int *fd,
	t_redirection *red_content, char **stop_word)
{
	char	*filenm;
	char	*str;

	str = ft_itoa(p_n);
	if (!str)
		return (set_ec(EO_PROG, NULL));
	filenm = ft_strjoin(".tmp", str);
	free(str);
	if (!filenm)
		return (set_ec(EO_PROG, NULL));
	*fd = open(filenm, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (free(filenm), set_ec(EO_PROG, NULL));
	*stop_word = red_content->filename;
	red_content->filename = filenm;
	red_content->num_red = SI_CHEV;
	return (SUCCESS);
}

static void	hd_free(char *tmp_prompt, char *stop_word, int fd)
{
	if (tmp_prompt)
		free(tmp_prompt);
	if (stop_word)
		free(stop_word);
	close(fd);
}

static int	read_heredoc(t_redirection *red_content, int p_n)
{
	int		fd;
	char	*stop_word;
	char	*tmp_prompt;

	fd = 0;
	g_sgn.here_doc = 1;
	open_tmp_file(p_n, &fd, red_content, &stop_word);
	if (mread(&tmp_prompt, stop_word))
		return (close(fd), free(stop_word), g_sgn.ec);
	while (ft_strncmp(tmp_prompt, stop_word, ft_strlen(stop_word) + 1))
	{
		if (write(fd, tmp_prompt, ft_strlen(tmp_prompt)) < 0
			|| write(fd, "\n", 1) < 0)
		{
			set_ec(EO_PROG, NULL);
			break ;
		}
		free(tmp_prompt);
		if (mread(&tmp_prompt, stop_word))
			break ;
	}
	hd_free(tmp_prompt, stop_word, fd);
	return (g_sgn.ec);
}

int	here_doc(t_node *heapnode)
{
	t_redirection	*r_content;
	t_node			*node;
	int				p_n;

	p_n = 0;
	while (heapnode)
	{
		node = ((t_parse *)(heapnode->content))->red_head;
		while (node)
		{
			r_content = (t_redirection *)node->content;
			if (r_content->num_red == HERE_DOC)
			{
				if (read_heredoc(r_content, p_n))
					return (EO_PROG);
			}
			node = node->next;
		}
		heapnode = heapnode->next;
		p_n++;
	}
	return (SUCCESS);
}
