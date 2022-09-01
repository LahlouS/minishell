/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:17:44 by lchan             #+#    #+#             */
/*   Updated: 2022/07/06 12:07:33 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_gnl
{
	int				fd;
	char			*content;
	char			buff[BUFFER_SIZE + 1];
	struct s_gnl	*next;
}t_gnl;

//get_next_line_utils.c
size_t	ft_strlen_opt_newline(char *str, int opt_newline);
char	*ft_strjoinfree_content(t_gnl *nod);
void	gnl_free_block(t_gnl **head, t_gnl *nod);
t_gnl	*ft_struct_init(int fd);
t_gnl	*ft_lst_init_addback(t_gnl **head, int fd);

//get_next_line_bonus.c
void	ft_rebuild_buff(t_gnl *nod);
void	gnl_build_content(t_gnl **nod, int fd);
char	*get_next_line(int fd);
char	*get_next_line_pipex(int fd, char *limiter);
#endif
