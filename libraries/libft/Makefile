# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchan <lchan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 20:57:58 by lchan             #+#    #+#              #
#    Updated: 2022/07/13 12:47:57 by lchan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_atoi.c\
			ft_atol.c\
			ft_bzero.c\
			ft_calloc.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_itoa.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_putchar_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_putstr_fd.c\
			ft_split.c\
			ft_strchr.c\
			ft_strdup.c\
			ft_striteri.c\
			ft_strjoin.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_strmapi.c\
			ft_strncmp.c\
			ft_strnstr.c\
			ft_strchr_b.c\
			ft_strrchr.c\
			ft_strtrim.c\
			ft_substr.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c\
			ft_llstnew.c\
			ft_llstadd_front.c\
			ft_llstsize.c\
			ft_llstlast.c\
			ft_llstadd_back.c\
			ft_llstdelone.c\
			ft_llstclear.c\
			ft_llstiter.c\
			ft_llstmap.c\
			ft_find_last_c_occurence.c\
			ft_puterror_exit.c\
			get_next_line.c\
			get_next_line_utils.c\
			ft_free.c

NAME		= libft.a

INC			= libft.h

OBJS		= ${SRCS:.c=.o}

CC			= gcc
RM			= rm -f

CFLAGS		= -g3 -Wall -Werror -Wextra

AR			= ar

ARFLAGS		= rcs

RAN			= ranlib

%.o: %.c
			${CC} ${CFLAGS} -c $< -o $@

all:		${NAME}

$(OBJS):	${INC}

$(NAME):	${OBJS}
			${AR} ${ARFLAGS} ${NAME} ${OBJS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		re clean fclean all bonus
