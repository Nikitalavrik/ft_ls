/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 11:03:37 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/11 11:03:40 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls	*parsing(int argc, char **argv, t_ls *begin)
{
	t_ls *save_begin;
	int i;
	int	k;

	i = 1;
	save_begin = begin;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			k = 0;
			while (argv[i][k + 1] && argv[i][k + 1] != ' ')
			{
				begin->flags[k] = argv[i][k + 1];
				k++;
			}
		}
		else if (!begin->d_path)
			begin->d_path = argv[i];
		else
			begin = add_node(begin, argv[i]);
		i++;
	}
	// print_node(save_begin);
	return (save_begin);
}
