/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:19:05 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/08 19:08:49 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__parser_update_status(t_data *msh_data, int status)
{
	char	*ret;
	char	*tmp;

	ret = ft_itoa(status);
	tmp = ret;
	ret = ft_strjoin("?=", ret);
	free(tmp);
	free(*(msh_data->env));
	*(msh_data->env) = ret;
}

void	__init_msh(t_data *msh_data)
{
	errno = 0;
	msh_data->fds = NULL;
	msh_data->env = NULL;
	msh_data->expt = NULL;
	msh_data->user_input = NULL;
	msh_data->lexer = NULL;
	msh_data->parser = NULL;
}

void	__init_expt(t_data *msh_data)
{
	msh_data->expt = ft_calloc(sizeof(char *), 2);
	if (msh_data->expt)
		*msh_data->expt = ft_calloc(sizeof(char), 2);
	msh_data->expt++;
	*(msh_data->expt) = NULL;
}

void	__init_env(t_data *msh_data, char **envp)
{
	int		envp_size;
	char	**env;

	envp_size = (ft_strtablen(envp) + 1);
	env = ft_calloc(sizeof(char *), envp_size + 2);
	if (env)
	{
		*env = ft_calloc(sizeof(char), 2);
		if (*env)
		{
			*(*(env + 0) + 0) |= envp_size;
			*(*(env + 0) + 1) |= envp_size >> 8;
		}
		env++;
		*(env) = ft_strdup("?=0");
		env++;
		while (*envp)
		{
			*(env) = ft_strdup(*(envp));
			env++;
			envp++;
		}
		*env = NULL;
	}
	msh_data->env = env - envp_size;
}

void	__set_msh_data(t_data *msh_data, char **envp)
{
	__init_msh(msh_data);
	__init_env(msh_data, envp);
	__init_expt(msh_data);
}
