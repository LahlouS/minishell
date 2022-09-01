/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:02:39 by lchan             #+#    #+#             */
/*   Updated: 2022/07/13 13:45:19 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_llstadd_back(t_llist **alst, t_llist *new)
{
	t_llist	*tmp;

	if (alst)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			tmp = ft_llstlast(*alst);
			tmp->next = new;
			new->prev = tmp;
		}
	}
}
