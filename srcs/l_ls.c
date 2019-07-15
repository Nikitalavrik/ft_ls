/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 11:03:22 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/11 11:03:23 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls	*create_ls(void)
{
	int i;
	t_ls *l_ls;

	i = 0;
	l_ls = ft_memalloc(sizeof(t_ls));
	l_ls->paths = create_path();
	l_ls->next = NULL;
	l_ls->d_path = NULL;
	l_ls->block_size = 0;
	l_ls->max_filename = 0;
	l_ls->max_group = 0;
	l_ls->max_numlink = 0;
	l_ls->max_uid = 0;
	l_ls->device = 0;
	l_ls->count_files = 0;
	while (i < 5)
	{
		l_ls->flags[i] = 0;
		i++;
	}
	return (l_ls);
}

void	copy_node_param(t_ls *begin, t_ls *new_node)
{
	int	i;

	i = 0;
	new_node->col = begin->col;
	new_node->w_rows = begin->w_rows;
	new_node->w_columns = begin->w_columns;
	while (i < 5)
	{
		new_node->flags[i] = begin->flags[i];
		i++;
	}
}

t_ls	*add_node(t_ls *begin, char *path)
{
	t_ls *new_node;
	t_ls *save_begin;
	

	new_node = create_ls();
	if (!begin)
		return (new_node);
	copy_node_param(begin, new_node);
	save_begin = begin;
	new_node->d_path = path;
	while (save_begin->next)
		save_begin = save_begin->next;
	save_begin->next = new_node;
	return (new_node);
}

int		check_flag(t_ls *begin, char flag)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (begin->flags[i] == flag)
			return (1);
		i++;
	}
	return (0);
}