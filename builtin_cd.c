/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:03:29 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/08 13:03:54 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__update_pwd(t_data *msh_data, char *oldpwd)
{
	char	buf[PATH_MAX + 2];
	char	*tmp_newpwd;
	char	*tmp_oldpwd;

	tmp_oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	msh_data->env = __add_var(tmp_oldpwd, msh_data->env, 0);
	free(tmp_oldpwd);
	if (getcwd(buf, PATH_MAX))
	{
		tmp_newpwd = ft_strjoin("PWD=", buf);
		msh_data->env = __add_var(tmp_newpwd, msh_data->env, 0);
		free(tmp_newpwd);
	}
}

int	__cd_funk(t_data *msh_data, t_splcmd *parser, int opt)
{
	int		cmd_size;
	int		err_flag;
	char	buf[PATH_MAX + 2];

	(void) opt;
	err_flag = 0;
	cmd_size = ft_strtablen(parser->cmd.cmd_words);
	if (cmd_size != 2)
	{
		write(2, "minishell: cd: invalide arguments\n", 35);
		err_flag = 1;
	}
	else
	{
		if (!getcwd(buf, PATH_MAX))
			buf[0] = '\0';
		if (chdir(*(parser->cmd.cmd_words + 1)) < 0)
		{
			perror("minishell: cd");
			err_flag = 1;
		}
		else
			__update_pwd(msh_data, buf);
	}
	return (err_flag);
}
