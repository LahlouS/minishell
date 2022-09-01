/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:02:58 by lchan             #+#    #+#             */
/*   Updated: 2022/07/13 12:48:31 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_llstadd_front(t_llist **alst, t_llist *new)
{
	new->prev = NULL;
	new->next = *alst;
	(*alst)->prev = new;
	*alst = new;
}
