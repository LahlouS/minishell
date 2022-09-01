/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:13:55 by lchan             #+#    #+#             */
/*   Updated: 2022/07/06 12:05:06 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_rebuild_buff(t_gnl *nod)
{
	int	start;
	int	index;

	index = 0;
	start = ft_strlen_opt_newline(nod->buff, 1);
	while (nod->buff[start])
		nod->buff[index++] = nod->buff[start++];
	nod->buff[index] = '\0';
}

void	gnl_build_content(t_gnl **nod, int fd)
{
	int	ret;

	ret = -2;
	while (1)
	{
		if (!(*nod)->buff[0])
		{
			ret = read(fd, (*nod)->buff, BUFFER_SIZE);
			(*nod)->buff[ret] = '\0';
		}
		else
		{
			(*nod)->content = ft_strjoinfree_content(*nod);
			ft_rebuild_buff(*nod);
		}
		if (ft_strlen_opt_newline((*nod)->content, 2))
			break ;
		if (ret == 0 || ret == -1)
			break ;
	}
}

/***********8
 * his get_next_line has been modified the 06/06/24
 * the content is never freed
 * **/
char	*get_next_line(int fd)
{
	static t_gnl	*head;
	t_gnl			*nod;
	char			*content;

	if (fd <= -1 || BUFFER_SIZE <= 0)
		return (NULL);
	nod = ft_lst_init_addback(&head, fd);
	if (nod && nod->content)
		nod->content = NULL;
	gnl_build_content(&nod, nod->fd);
	content = nod->content;
	if (!nod->buff[0])
	{
		gnl_free_block(&head, nod);
		if (nod == head)
			head = NULL;
		nod = NULL;
	}
	if (content)
		return (content);
	else
		return (NULL);
}

static int	px_strncomp(char *lim, char *gnl, size_t lim_len)
{
	size_t	i;
	size_t	gnl_len;

	i = 0;
	gnl_len = ft_strlen_opt_newline(gnl, 0);
	while (i < lim_len)
	{
		if (lim[i] != gnl[i])
			return ((unsigned char)lim[i] - (unsigned char)gnl[i]);
		if (!lim[i] || !gnl[i])
			return ((unsigned char)lim[i] - (unsigned char)gnl[i]);
		i++;
	}
	if (gnl_len > lim_len && gnl[i] == '\n')
		return (0);
	else
		return (-1);
}

char	*get_next_line_pipex(int fd, char *limiter)
{
	static t_gnl	*head;
	t_gnl			*nod;

	if (fd <= -1 || BUFFER_SIZE <= 0)
		return (NULL);
	nod = ft_lst_init_addback(&head, fd);
	if (nod && nod->content)
		nod->content = NULL;
	gnl_build_content(&nod, nod->fd);
	if ((!nod->content && !nod->buff[0])
		|| px_strncomp(limiter, nod->content,
			ft_strlen_opt_newline(limiter, 0)) == 0)
	{
		gnl_free_block(&head, nod);
		if (nod == head)
			head = NULL;
		nod = NULL;
	}
	if (nod)
		return (nod->content);
	else
		return (NULL);
}
