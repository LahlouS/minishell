/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:27:33 by lchan             #+#    #+#             */
/*   Updated: 2022/05/31 18:47:58 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
/*
void	ft_puterror_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
*/
void	ft_puterror_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}
