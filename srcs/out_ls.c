/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 11:03:31 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/11 11:03:31 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		calc_col(t_ls *begin)
{
	DIR *dir;
	struct dirent *rd;
	int	max_len;
	int	len;

	max_len = 0;
	dir = opendir(begin->paths->path ? begin->paths->path : ".");
	if (dir)
	{
		while ((rd = readdir(dir)) != NULL)
		{
			len = ft_strlen(rd->d_name);
			if (len > max_len)
				max_len = len;
		}
		closedir(dir);
	}
	return (max_len + 1);
}

void	output_paths(t_ls *begin)
{
	t_path	*tmp_path;
	int		sum_column;

	sum_column = 0;
	tmp_path = begin->paths;
	while (tmp_path)
	{
		sum_column += begin->col;
		if (sum_column > begin->columns)
		{
			sum_column = begin->col;
			ft_printf("\n");
		}
		ft_printf("%-*s", begin->col, tmp_path->path);
		tmp_path = tmp_path->next;
	}
	ft_printf("\n");
}

void	put_path(t_ls *begin)
{
	struct	dirent	*rd;
	t_path			*tmp_path;
	int				max_len;
	int				len;

	max_len = 0;
	begin->dir = opendir(begin->d_path ? begin->d_path : ".");
	tmp_path = begin->paths;
	if (begin->dir)
	{
		while ((rd = readdir(begin->dir)))
		{
			if (rd->d_name[0] != '.')
			{
				len = ft_strlen(rd->d_name);
				max_len = len > max_len ? len : max_len;
				if (tmp_path->path)
					tmp_path = add_path(tmp_path);
				tmp_path->path = rd->d_name;
			}
		}
		begin->col = max_len + 1;
		// output_path(begin->paths);
	}
}

void	sort_paths(t_path *begin)
{
	t_path	*tmp_begin;
	char	*tmp_path;
	int		i;
	int		len;

	i = 0;
	len = ft_lstlen(begin);
	tmp_begin = begin;
	while (i < len)
	{
		while (tmp_begin->next)
		{
			if (ft_strcmp(tmp_begin->path, tmp_begin->next->path) > 0)
			{
				tmp_path = tmp_begin->path;
				tmp_begin->path = tmp_begin->next->path;
				tmp_begin->next->path = tmp_path;
			}
			tmp_begin = tmp_begin->next;
		}
		tmp_begin = begin;
		i++;
	}
}

void	output_ls(t_ls *begin)
{
	t_ls *save_begin;

	save_begin = begin;
	while (begin)
	{
		put_path(begin);
		if (begin->next)
			begin->next->col = begin->col;
		sort_paths(begin->paths);
		output_paths(begin);
		begin = begin->next;
		// if (begin)
		// 	ft_printf("\n");
	}
	begin = save_begin;
}