/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:40:48 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 13:01:51 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__built_pwd(int fd)
{
	char	buf[PATH_MAX + 2];
	int		tmp;

	if (!getcwd(buf, PATH_MAX))
	{
		perror("getcwd");
		return (errno);
	}
	else
	{
		tmp = ft_strlen(buf);
		buf[tmp] = '\n';
		buf[tmp + 1] = '\0';
		write(fd, buf, ft_strlen(buf));
		return (0);
	}
}

int	__pwd_funk(t_data *msh_data, t_splcmd *parser, int opt)
{
	int	ret;

	(void) parser;
	ret = 1;
	if (opt == 0)
	{
		if (parser->out.fd == 0)
			ret = __built_pwd(STDOUT_FILENO);
		else
			ret = __built_pwd(msh_data->fds[3]);
	}
	else if (opt)
		ret = __built_pwd(STDOUT_FILENO);
	return (ret);
}
