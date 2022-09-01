/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:33:49 by lchan             #+#    #+#             */
/*   Updated: 2021/11/30 16:47:31 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(int n)
{
	long int	big_n;
	int			count;

	count = 1;
	big_n = n;
	if (n < 0)
	{
		big_n = -big_n;
		count++;
	}
	else
		big_n = n;
	while (big_n >= 10)
	{
		count++;
		big_n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long int	big_n;
	int			count;
	char		*ascii;

	count = ft_count(n);
	big_n = n;
	ascii = (char *)malloc((count + 1) * sizeof(char));
	if (!ascii)
		return (NULL);
	ascii[count] = '\0';
	if (n == 0)
		ascii[0] = '0';
	else if (n < 0)
	{
		ascii[0] = '-';
		big_n *= -1;
	}
	while (big_n > 0 && --count >= 0)
	{
		ascii[count] = big_n % 10 + '0';
		big_n = big_n / 10;
	}
	return (ascii);
}
