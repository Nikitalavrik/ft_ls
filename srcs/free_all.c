/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:04:52 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/15 15:04:53 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_paths(t_path *paths)
{
	t_path *next_path;
	
	next_path = paths;
	while (paths)
	{
		// ft_printf("path = %s\n", paths->path);
		next_path = paths->next;
		ft_memdel((void **)&paths->gr_name);
		ft_memdel((void **)&paths->pw_name);
		paths->next = NULL;
		ft_memdel((void **)&paths->path);
		ft_memdel((void **)&paths);
		paths = next_path;
	}
}

void	free_dirs(t_ls *begin)
{
	t_ls	*next_ls;

	next_ls = begin;
	while (begin)
	{
		next_ls = begin->next;
		ft_memdel((void **)&begin->d_path);
		free_paths(begin->paths);
		ft_memdel((void **)&begin->flag);
		begin->next = NULL;
		ft_memdel((void **)&begin);
		begin = next_ls;
	}
}