/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:47:33 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 12:56:29 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__check_syntax(char *var)
{
	if (!ft_isdigit(*var))
	{
		while (*var && *var != '=')
		{
			if (ft_isalnum(*var) == 0 && *var != '_')
				return (0);
			var++;
		}
		return (1);
	}
	return (0);
}

char	**__check_if_exist(char	*var, char **tab, int opt)
{
	int		arg_len;
	int		cmp;

	arg_len = ((opt == 1) * ft_strlen_p(var)) + \
	((opt == 0) * ft_strlen_c(var, '='));
	cmp = 0;
	while (*tab)
	{
		if (opt < 2)
		{
			cmp = ((opt == 1) * ft_strlen_p(*tab)) + \
			((opt == 0) * ft_strlen_c(*tab, '='));
			if (cmp == arg_len && !ft_strncmp(*tab, var, arg_len))
				return (tab);
		}
		else if (cmp == 0 && !ft_strncmp(*tab, var, ft_strlen_p(var)))
			return (tab);
		tab++;
	}
	return (tab);
}

char	**__creat_new_tab(char *var, char **tab, int size)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = ft_calloc(sizeof(char *), size + 2);
	if (new_tab)
	{
		*new_tab = ft_calloc(sizeof(char), 2);
		if (*new_tab)
		{
			*(*(new_tab + 0) + 0) |= size;
			*(*(new_tab + 0) + 1) |= size >> 8;
		}
		new_tab++;
	}
	while (*(tab + i))
		*(new_tab++) = *(tab + (i++));
	*(new_tab) = ft_strdup(var);
	new_tab++;
	*new_tab = NULL;
	free(*(tab - 1));
	free(tab - 1);
	return (new_tab - size);
}

char	**__add_var(char *var, char **tab, int opt)
{
	int		size;
	char	**exist;

	exist = __check_if_exist(var, tab, opt);
	size = __get_env_size(*(tab - 1)) + ((*exist) == NULL);
	if (*exist)
	{
		free(*exist);
		*exist = ft_strdup(var);
		return (tab);
	}
	return (__creat_new_tab(var, tab, size));
}

int	__export_var(char **args, t_data *msh_data)
{
	int		syntax;
	int		err_flag;
	char	*test;

	err_flag = 0;
	while (*args)
	{
		test = (*(__check_if_exist(*args, msh_data->env, 2)));
		syntax = __check_syntax(*args);
		if (ft_strchr(*args, '=') && syntax)
			msh_data->env = __add_var(*args, msh_data->env, 0);
		else if (syntax && !(test))
			msh_data->expt = __add_var(*args, msh_data->expt, 1);
		else if (!syntax)
		{
			write(2, "Minishell: export: not a valid identifier\n", 42);
			err_flag = 1;
		}
		args++;
	}
	return (err_flag);
}
