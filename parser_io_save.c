/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_io_save.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:55:50 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/08 13:17:11 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__child_fill_pipe(int *hd_pipe, char *limiter)
{
	char	*user_imput;
	char	*tmp;

	user_imput = NULL;
	signal(SIGINT, SIG_DFL);
	close(hd_pipe[0]);
	while (1)
	{
		user_imput = readline("> ");
		if (!user_imput && write(2, "here-doc: delimited by EOF\n", 27))
			break ;
		if (!(ft_strncmp(user_imput, limiter, ft_strlen(user_imput)))
			&& ft_strlen_p(user_imput) == ft_strlen_p(limiter))
			break ;
		tmp = ft_strjoin(user_imput, "\n");
		free(user_imput);
		write(hd_pipe[1], tmp, ft_strlen_p(tmp));
		free(tmp);
	}
	close(hd_pipe[1]);
	__ultimate_free((t_data *)g_lob_ptr, 0, 0);
	free(limiter);
	exit(0);
}

int	__here_d_parent(char **arg)
{
	int		status;

	signal(SIGINT, &__signal_handler2);
	if (wait(&status) == -1 || WIFSIGNALED(status))
	{
		signal(SIGINT, &__signal_handler);
		free(*arg);
		*arg = NULL;
		return (1);
	}
	signal(SIGINT, &__signal_handler);
	return (0);
}

static void	__save_here_d(t_io *io)
{
	int		hd_pipe[2];
	int		pid;
	char	*gnl_ret;

	if (io->here_buffer)
		__t_list_free(&(io->here_buffer));
	__here_d_parse_lim(io);
	pipe(hd_pipe);
	pid = fork();
	if (pid && __here_d_parent(&io->arg))
		return ;
	if (!pid)
		__child_fill_pipe(hd_pipe, io->arg);
	close(hd_pipe[1]);
	while (1)
	{
		gnl_ret = get_next_line(hd_pipe[0]);
		if (!gnl_ret)
			break ;
		ft_lstadd_back(&(io->here_buffer), ft_lstnew(gnl_ret));
	}
	close(hd_pipe[0]);
	free(io->arg);
	io->arg = NULL;
}

static void	__init_stock_mgmt(void (*stock_mgmt[7]) (t_io *io))
{
	stock_mgmt[IN_D] = &__save_io_arg;
	stock_mgmt[HERE_D] = &__save_here_d;
	stock_mgmt[OUT_D] = &__save_io_arg;
	stock_mgmt[OUT_D_APP] = &__save_io_arg;
}

t_list	*__get_stock(t_io *io, int type)
{
	void	(*stock_mgmt[7])(t_io *io);

	__init_stock_mgmt(stock_mgmt);
	stock_mgmt[type](io);
	return (io->stock);
}
