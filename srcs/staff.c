/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   staff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 19:43:56 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/17 19:43:57 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_nbrlen(int num)
{
	int	count;

	count = 1;
	while (num > 10)
	{
		num /= 10;
		count++;
	}
	return (count);
}

int		count_space(int max_len)
{
	int i;

	i = 8;
	while (i < max_len)
		i += 8;
	return (i);
}
