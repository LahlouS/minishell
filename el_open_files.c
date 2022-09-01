/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   el_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:28:15 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 11:01:34 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__get_file_mode(char *filename, int *fd_type)
{
	if (filename[ft_strlen(filename) + 1] == 'A')
	{
		*fd_type = 1;
		return (O_APPEND | O_CREAT | O_WRONLY);
	}
	else if (filename[ft_strlen(filename) + 1] == 'T')
	{
		*fd_type = 1;
		return (O_TRUNC | O_CREAT | O_WRONLY);
	}
	else
	{
		*fd_type = 2;
		return (O_RDONLY);
	}
}

static void	__closeif_useless(
	t_list *stock, int fd_type, int in_fd, int out_fd)
{
	char	*content;
	int		fd_type_tmp;

	while (stock && stock->content)
	{
		content = (char *)stock->content;
		__get_file_mode(content, &fd_type_tmp);
		if (fd_type == fd_type_tmp)
		{
			if (fd_type == 1)
				if (close (out_fd) == -1)
					perror("Minishell close");
			if (fd_type == 2)
				if (close (in_fd))
					perror("Minishell close");
			return ;
		}
		stock = stock->next;
	}
}

static int	__cut_useless_files(t_splcmd *parser, t_list *files)
{
	t_list	*tmp;
	t_list	*save;

	perror("minishell");
	parser->cmd.type = CMD_ERR;
	save = parser->in.stock;
	if (files != save)
	{
		while (save->next != files && files != save)
			save = save->next;
		save->next = NULL;
	}
	else
	{
		parser->in.stock = NULL;
		parser->out.stock = NULL;
	}
	while (files)
	{
		tmp = files;
		files = files->next;
		free(tmp->content);
		free(tmp);
	}
	return (0);
}

int	__imperial_open_files(t_splcmd *parser, int *in_fd, int *out_fd)
{
	t_list	*files;
	char	*file_name;
	int		mode;
	int		fd_type;

	files = parser->in.stock;
	while (files)
	{
		file_name = (char *)files->content;
		if (file_name)
		{
			mode = __get_file_mode(file_name, &fd_type);
			if (fd_type == 2)
				*in_fd = open(file_name, mode, 0644);
			if (fd_type == 1)
				*out_fd = open(file_name, mode, 0644);
			if (*out_fd < 0 || *in_fd < 0)
				return (__cut_useless_files(parser, files));
			__closeif_useless(files->next, fd_type, *in_fd, *out_fd);
		}
		files = files->next;
	}
	return (1);
}

void	__imperial_open_heredoc(t_io *in, int *fds)
{
	t_list	*tmp;
	char	*tmp_content;
	int		hd_fd[2];

	if (in->type == HERE_D)
	{
		pipe(hd_fd);
		tmp = in->here_buffer->next;
		while (tmp)
		{
			tmp_content = (char *)(tmp->content);
			write(hd_fd[1], tmp_content, ft_strlen_p(tmp_content));
			tmp = tmp->next;
		}
		__t_list_free(&(in->here_buffer));
		close(fds[1]);
		dup2(hd_fd[0], fds[0]);
		close(hd_fd[0]);
		close(hd_fd[1]);
	}
}
