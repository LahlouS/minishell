/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   el_bambino.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:26:23 by slahlou           #+#    #+#             */
/*   Updated: 2022/09/01 09:01:58 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__imperial_bambino(
	t_data *msh_data, t_splcmd *parser, int *fds, int left_size)
{
	dup2(fds[0], 0);
	dup2(fds[3], 1);
	while (left_size--)
		close(*(fds++));
	if (parser->cmd.type >= CMD_ECHO && parser->cmd.type <= CMD_EXIT)
		__execve_builtin(msh_data, parser, 1);
	__join_path(msh_data->env, &(parser->cmd));
	if (parser->cmd.type == CMD_ERR)
	{
		close(0);
		close(1);
		__ultimate_free(msh_data, 0, 1);
	}
	if (execve(
			*(parser->cmd.cmd_words),
			parser->cmd.cmd_words, msh_data->env + 1) < 0)
	{
		close(0);
		close(1);
		__ultimate_free(msh_data, 0, 127);
	}
}

int	__cmd_is_builtin(t_splcmd *parser)
{
	int			i;
	char		*cmd_wds;
	const char	*builtin_dico[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	if (parser && parser->cmd.cmd_words)
	{
		i = 0;
		cmd_wds = *(parser->cmd.cmd_words);
		while (*(builtin_dico + i))
		{
			if (!ft_strncmp(cmd_wds, *(builtin_dico + i), \
			ft_strlen_p(*(builtin_dico + i))))
			{
				parser->cmd.type = i + 1;
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	__lonely_builtin(t_data *msh_data, t_splcmd *parser, int *fds, int size)
{
	if (parser->cmd.type != CMD_ERR && __cmd_is_builtin(parser) && size == 4)
	{
		__execve_builtin(msh_data, parser, 0);
		close(fds[0]);
		close(fds[1]);
		close(fds[2]);
		close(fds[3]);
		return (1);
	}
	return (0);
}

int	__los_bambinos_del_imperator(
	t_data *msh_data, t_splcmd *parser, int *fds, int left_size)
{
	int	pid;

	pid = 0;
	if (!__lonely_builtin(msh_data, parser, msh_data->fds, \
	*((msh_data->fds) - 1)))
	{
		pid = fork();
		if (pid > 0)
			signal(SIGINT, &__signal_handler2);
		if (pid < 0)
			__ultimate_free(msh_data, 0, 0);
		else if (!pid)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (!parser->cmd.cmd_words)
				parser->cmd.type = CMD_ERR;
			__imperial_bambino(msh_data, parser, fds, left_size);
		}
		close(fds[1]);
		close(fds[0]);
	}
	return (pid);
}
