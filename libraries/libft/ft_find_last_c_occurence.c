/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_last_c_occurence.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:51:12 by lchan             #+#    #+#             */
/*   Updated: 2022/05/27 19:28:11 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_find_last_c_occurence(char *path, char c)
{
	int	i;
	int	slash;

	i = -1;
	slash = i + 1;
	while (path[++i])
		if (path[i] == c)
			slash = i + 1;
	return (slash);
}

/*****************************************
* return position of the last c encounted
******************************************/
