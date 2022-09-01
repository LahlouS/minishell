/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   el_imperator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:52:17 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/08 18:30:33 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*__sig_stat(int sig_id)
{
	char	*ret;
	char	*tmp;

	ret = ft_itoa(sig_id + 128);
	tmp = ret;
	ret = ft_strjoin("?=", ret);
	free(tmp);
	return (ret);
}

int	__error_pipe_gen(int **pipe_army, int i)
{
	perror("Minishell");
	while (--i >= 0)
		close((*pipe_army)[i]);
	free(*pipe_army);
	*pipe_army = NULL;
	return (0);
}

int	*__pipe_army(t_splcmd *parser)
{
	int	*pipe_army;
	int	i;
	int	nb_pipe;

	nb_pipe = 1;
	while (parser && ++nb_pipe)
		parser = parser->next;
	(nb_pipe) *= 2;
	pipe_army = ft_calloc(sizeof(int), nb_pipe + 1);
	if (pipe_army)
	{
		pipe_army[0] = nb_pipe;
		pipe_army++;
		i = 0;
		while (nb_pipe > 0)
		{
			if ((pipe(&pipe_army[i]) < 0))
				nb_pipe = __error_pipe_gen(&pipe_army, i);
			i += 2;
			nb_pipe -= 2;
		}
	}
	return (pipe_army);
}

char	*__imperial_wait(int pid, int fd_i, char *old_status)
{
	int		status;
	char	*ret;
	char	*tmp;

	ret = NULL;
	while (fd_i >= 0)
	{
		if (wait(&status) == pid)
		{
			if (old_status)
				free(old_status);
			if (!WIFSIGNALED(status))
			{
				ret = ft_itoa(status >> 8);
				tmp = ret;
				ret = ft_strjoin("?=", ret);
				free(tmp);
			}
			else
				ret = __sig_stat(WTERMSIG(status));
		}
		fd_i -= 2;
	}
	signal(SIGINT, &__signal_handler);
	return (ret);
}

int	__el_imperator(t_data *msh_data, t_splcmd *parser)
{
	int	fd_i;
	int	pid;

	if (!parser)
		return (0);
	msh_data->fds = __pipe_army(parser);
	if (!msh_data->fds)
		return (0);
	fd_i = 0;
	while (parser)
	{
		__imperial_redirect(parser, msh_data->fds, fd_i);
		pid = __los_bambinos_del_imperator(
				msh_data, parser, ((msh_data->fds) + fd_i),
				(*((msh_data->fds) - 1) - fd_i));
		parser = parser->next;
		fd_i += 2;
	}
	close((msh_data->fds)[fd_i + 1]);
	if (pid)
		*(msh_data->env) = __imperial_wait(pid, fd_i, *(msh_data->env));
	return (0);
}
