/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:12:17 by lchan             #+#    #+#             */
/*   Updated: 2022/07/08 17:29:19 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include "get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

// <string.h>
size_t		ft_strlen(const char *s);
size_t		ft_strlen_p(const char *s);
void		ft_bzero(void *s, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dest, const char *src, size_t destsize);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);

// <stdlib.h>
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);

// <ctype.h>
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

// part II
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fb);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

//bonus
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **alst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//own
long int	ft_atol(const char *str);
int			ft_find_last_c_occurence(char *path, char c);
int			ft_strchr_b(const char *s, int c);
void		ft_puterror_exit(char *str);
void		ft_free(void *malloc_content);
void		ft_free_char(char **malloc_elem);
void		ft_free_stdarg(int n, ...);
char		*ft_strjoin_free(char **s1, char **s2);
char		*ft_strjoin_free_s1(char **s1, char **s2);
char		*ft_strjoin_free_s2(char **s1, char **s2);
char		*ft_strjoin_free_sep(char **s1, char **s2, char sep);
#endif
