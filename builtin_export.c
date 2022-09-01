/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:46:17 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 13:17:11 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__child_print_expt(char **tab)
{
	int		i;
	char	*tmp;
	int		var_len;

	i = -1;
	while (tab[++i])
	{
		tmp = ft_strchr(tab[i], '=');
		if (!tmp)
			printf("export %s\n", tab[i]);
		else
		{
			var_len = (tmp - tab[i]) + 1;
			printf("export %.*s\"%s\"\n", var_len, tab[i], tmp + 1);
		}
	}
}

void	__print_expt(char **tab, int fd)
{
	int		tmp_in;
	int		pid;

	if (!tab)
		return ;
	pid = fork();
	if (!pid)
	{
		if (fd != 1)
		{
			tmp_in = dup(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
		}
		__child_print_expt(tab);
		if (fd != 1)
		{
			dup2(tmp_in, STDOUT_FILENO);
			dup2(STDOUT_FILENO, fd);
			close(tmp_in);
		}
		__ultimate_free((t_data *)g_lob_ptr, 0, 0);
		exit(0);
	}
	else
		wait(NULL);
}

int	__built_export(t_data *msh_data, char **cmd_words, int fd)
{
	char	**env;
	char	**expt;

	env = (msh_data->env + 1);
	expt = msh_data->expt;
	if (!env)
		return (1);
	if (*(cmd_words + 1) == NULL)
	{
		__print_expt(env, fd);
		__print_expt(expt, fd);
	}
	else
		return (__export_var((cmd_words + 1), msh_data));
	return (0);
}

int	__export_funk(t_data *msh_data, t_splcmd *parser, int opt)
{
	int	ret;

	(void) opt;
	(void) parser;
	ret = 1;
	if (opt == 0)
	{
		if (parser->out.fd == 0)
			ret = \
			__built_export(msh_data, parser->cmd.cmd_words, STDOUT_FILENO);
		else
			ret = \
			__built_export(msh_data, parser->cmd.cmd_words, msh_data->fds[3]);
	}
	else if (opt)
		ret = __built_export(msh_data, parser->cmd.cmd_words, STDOUT_FILENO);
	return (ret);
}
