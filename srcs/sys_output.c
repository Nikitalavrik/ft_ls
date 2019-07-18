/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 14:02:47 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/11 14:02:48 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sys_print_node(t_ls *begin)
{
	int		i;
	t_ls	*save_begin;

	save_begin = begin;
	while (save_begin)
	{
		i = 0;
		ft_printf("path = %s\nflags ", save_begin->d_path);
		ft_printf("flag_l %d\n", begin->flag->l);
		ft_printf("flag_r %d\n", begin->flag->r);
		ft_printf("flag_R %d\n", begin->flag->rr);
		ft_printf("flag_a %d\n", begin->flag->a);
		ft_printf("flag_t %d\n", begin->flag->t);
		save_begin = save_begin->next;
	}
	ft_printf("-------------------\n");
}

void	sys_output_path(t_path *begin)
{
	t_path	*tmp_path;

	tmp_path = begin;
	ft_printf("PATH : ");
	while (tmp_path)
	{
		ft_printf("%s ", tmp_path->path);
		tmp_path = tmp_path->next;
	}
	ft_printf("\n------------------\n");
}
