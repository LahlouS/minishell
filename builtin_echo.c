/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:39:48 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 16:16:06 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option(char *str)
{
	if (*str == '-')
	{
		str++;
		while (*str && *str == 'n')
			str++;
		if (!(*str))
			return (1);
	}
	return (0);
}

int	check_arg(char ***arg, int *opt_arg)
{
	int	i;

	i = 1;
	while (*((*arg) + i) && (*((*arg) + i))[0] == '-')
	{
		if (!check_option(*((*arg) + i)))
			break ;
		i++;
		(*opt_arg) = 1;
	}
	*arg += i;
	return (1);
}

void	ft_print_args(char **arg, int opt_arg, int fd)
{
	int	i;

	i = 0;
	if (!*(arg + i) && !opt_arg)
		write(fd, "\n", 1);
	while (*(arg + i))
	{
		write(fd, *(arg + i), ft_strlen(*(arg + i)));
		if (*(arg + (i + 1)))
			write(fd, " ", 1);
		else if (!(*(arg + (i + 1))) && !opt_arg)
			write(fd, "\n", 1);
		i++;
	}
}

int	__built_echo(char **args, int fd)
{
	int		opt_arg;
	char	**arg_tmp;

	opt_arg = 0;
	arg_tmp = args;
	if (!(ft_strncmp(*(arg_tmp), "echo", ft_strlen(*arg_tmp))) \
	&& check_arg(&arg_tmp, &opt_arg))
		ft_print_args(arg_tmp, opt_arg, fd);
	else
		return (1);
	return (0);
}

int	__echo_funk(t_data *msh_data, t_splcmd *parser, int opt)
{
	int		ret;

	(void) msh_data;
	ret = 1;
	if (parser->cmd.cmd_words)
	{
		if (opt == 0)
		{
			if (parser->out.fd == 0)
				ret = __built_echo(parser->cmd.cmd_words, 1);
			else
				ret = __built_echo(parser->cmd.cmd_words, msh_data->fds[3]);
		}
		else if (opt)
			ret = __built_echo(parser->cmd.cmd_words, 1);
	}
	return (ret);
}
