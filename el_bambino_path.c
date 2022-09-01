/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   el_bambino_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:47:53 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/08 12:49:19 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__cat_cmd_to_path(char *buf, char *path, char *cmd)
{
	int	i;

	i = 0;
	while (path && *path)
	{
		buf[i] = *path;
		i++;
		path++;
	}
	if (path != NULL)
	{
		buf[i] = '/';
		i++;
	}
	while (cmd && *cmd)
	{
		buf[i] = *cmd;
		i++;
		cmd++;
	}
	buf[i] = '\0';
}

void	__join_path(char **env, t_cmd *cmd)
{
	char	*tmp_path;
	char	**path_split;
	char	buf[BUFFER_S];
	int		i;
	int		access_ret;

	i = -1;
	tmp_path = __get_expand("PATH=", 4, env);
	if (!tmp_path || !cmd->cmd_words)
		return ;
	path_split = ft_split(tmp_path, ':');
	while (*(path_split + (++i)))
	{
		__cat_cmd_to_path(buf, *(path_split + i), *(cmd->cmd_words));
		access_ret = access(buf, X_OK);
		if ((access_ret) == 0)
			break ;
	}
	if (access_ret == 0)
	{
		errno = 0;
		free(*(cmd->cmd_words));
		*(cmd->cmd_words) = ft_strdup(buf);
	}
	ft_free_strtab(path_split);
}
