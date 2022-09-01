/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:13:06 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/08 13:03:23 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__get_env_size(char *env_size)
{
	int	size;

	size = 0;
	size |= (int) *(env_size + 1);
	size <<= 8;
	size |= (int) *env_size;
	return (size);
}

int	__get_exit_status(char **env, char **cmd_words)
{
	char	*tmp;

	if (*(cmd_words + 1))
	{
		tmp = *(cmd_words + 1);
		while (*tmp)
		{
			if (!ft_isdigit(*(tmp)))
				return (2);
			tmp++;
		}
		return (ft_atoi(*(cmd_words + 1)));
	}
	if (env)
		return (ft_atoi((*env) + 2));
	return (-1);
}

int	__exit_funk(t_data *msh_data, t_splcmd *parser, int opt)
{
	int	exit_status;

	(void) opt;
	exit_status = __get_exit_status(msh_data->env, parser->cmd.cmd_words);
	__ultimate_free(msh_data, 0, 0);
	exit(exit_status);
}

void	__set_status_builtin(int ret, t_data *msh_data)
{
	char	*tmp;
	char	*tmp2;
	char	*old_status;

	if (!msh_data->env)
		return ;
	old_status = *(msh_data->env);
	if (old_status)
		free(old_status);
	tmp = ft_itoa(ret);
	tmp2 = tmp;
	tmp = ft_strjoin("?=", tmp2);
	free(tmp2);
	*(msh_data->env) = tmp;
}

void	__execve_builtin(t_data *msh_data, t_splcmd *parser, int opt)
{
	int	ret;
	int	(*__u___built_funk[7])(t_data *msh_data, t_splcmd *parser, int opt);

	__u___built_funk[0] = &__echo_funk;
	__u___built_funk[1] = &__cd_funk;
	__u___built_funk[2] = &__pwd_funk;
	__u___built_funk[3] = &__export_funk;
	__u___built_funk[4] = &__unset_funk;
	__u___built_funk[5] = &__env_funk;
	__u___built_funk[6] = &__exit_funk;
	ret = __u___built_funk[parser->cmd.type - 1](msh_data, parser, opt);
	if (opt)
	{
		__ultimate_free(msh_data, 0, ret);
		close(0);
		close(1);
		exit(ret);
	}
	else
		__set_status_builtin(ret, msh_data);
}
