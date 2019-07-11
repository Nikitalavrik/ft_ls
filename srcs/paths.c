/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 13:18:20 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/11 13:18:21 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path	*create_path(void)
{
	t_path	*path;

	path = ft_memalloc(sizeof(t_path));
	path->path = NULL;
	path->next = NULL;
	return (path);
}

t_path	*add_path(t_path *begin)
{
	t_path	*save_begin;
	t_path	*new_path;

	save_begin = begin;
	new_path = create_path();
	while (save_begin->next)
		save_begin = save_begin->next;
	save_begin->next = new_path;
	return (new_path);
}

int		ft_lstlen(t_path *begin)
{
	int 	count;
	t_path	*tmp_begin;

	count = 0;
	tmp_begin = begin;
	while (tmp_begin)
	{
		tmp_begin = tmp_begin->next;
		count++;
	}
	return (count);
}
