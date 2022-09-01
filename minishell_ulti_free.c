/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ulti_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:50:54 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/08 13:30:18 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__free_u_fds(t_data	*msh_data)
{
	int	fds_size;
	int	*tmp_fds;

	if (msh_data->fds)
	{
		tmp_fds = (msh_data->fds) - 1;
		fds_size = *tmp_fds;
		while (fds_size)
			close(tmp_fds[fds_size--]);
		free(tmp_fds);
		msh_data->fds = NULL;
	}
}

void	__free_u_env(t_data *msh_data)
{
	if (msh_data->env)
	{
		ft_free_strtab((msh_data->env) - 1);
		msh_data->env = NULL;
	}
}

void	__free_u_expt(t_data *msh_data)
{
	if (msh_data->expt)
	{
		ft_free_strtab((msh_data->expt) - 1);
		msh_data->env = NULL;
	}
}

void	__ultimate_free(t_data *msh_data, int free_opt, int bambinos)
{
	void	(*__u_free_funk[T_DATA_SIZE])(t_data *msh_data);

	__u_free_funk[0] = &__free_u_rl_history;
	__u_free_funk[1] = &__free_u_env;
	__u_free_funk[2] = &__free_u_expt;
	__u_free_funk[3] = &__free_u_user_input;
	__u_free_funk[4] = &__free_u_lexer;
	__u_free_funk[5] = &__free_u_parse;
	__u_free_funk[6] = &__free_u_fds;
	while (free_opt < T_DATA_SIZE)
	{
		(__u_free_funk[free_opt])(msh_data);
		free_opt++;
	}
	if (bambinos > 0)
	{
		if (bambinos == 127)
			ft_putstr_fd("minishell: command not found\n", 2);
		exit(bambinos);
	}
}
