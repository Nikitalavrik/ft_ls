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
		if (sum_column > begin->w_columns)
		{
			sum_column = begin->col;
			ft_printf("\n");
		}
		ft_printf("%-*s", begin->col, tmp_path->path);
		tmp_path = tmp_path->next;
	}
	ft_printf("\n");
}

void	output_lpaths(t_ls *begin)
{
	t_path *tmp_path;

	tmp_path = begin->paths;
	while (tmp_path)
	{
		out_permision(tmp_path->stats.st_mode);
		out_num_link(tmp_path->stats.st_nlink);
		out_owner_group(tmp_path->stats);
		out_num_bytes(tmp_path->stats.st_size);
		out_time_modify(tmp_path->stats);
		ft_printf(" %s\n", tmp_path->path);
		tmp_path = tmp_path->next;
	}
}

void	put_path(t_ls *begin)
{
	struct	dirent	*rd;
	t_path			*tmp_path;
	int				max_len;
	int				flag;

	max_len = 0;
	begin->d_path = begin->d_path ? begin->d_path : ".";
	begin->dir = opendir(begin->d_path);
	tmp_path = begin->paths;
	flag = check_flag(begin, 'R');
	if (begin->dir)
	{
		while ((rd = readdir(begin->dir)))
		{
			if (rd->d_name[0] != '.')
			{
				max_len = rd->d_namlen > max_len ? rd->d_namlen : max_len;
				if (tmp_path->path)
					tmp_path = add_path(tmp_path);
				tmp_path->path = rd->d_name;
				stat(pathcat(begin->d_path, rd->d_name), &(tmp_path->stats));
				if (flag && S_ISDIR(tmp_path->stats.st_mode))
				{
					add_node(begin, pathcat(begin->d_path, rd->d_name));
					// ft_printf("dir = %s\n", pathcat(begin->d_path, rd->d_name));
							// sys_print_node(begin);
				}
			}
		}
		// sys_print_node(begin);
		begin->col = max_len + 1;
	}
}

void	swap_paths(t_path *swap_path)
{
	char		*tmp_path;
	struct stat tmp_stat;

	tmp_path = swap_path->path;
	swap_path->path = swap_path->next->path;
	swap_path->next->path = tmp_path;
	tmp_stat = swap_path->stats;
	swap_path->stats = swap_path->next->stats;
	swap_path->next->stats = tmp_stat;
}

void	sort_paths(t_path *begin)
{
	t_path	*tmp_begin;
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
				swap_paths(tmp_begin);
			tmp_begin = tmp_begin->next;
		}
		tmp_begin = begin;
		i++;
	}
}

void	output_ls(t_ls *begin)
{
	t_ls *save_begin;
	int		flag_next;
	int		flag_R;

	flag_R = check_flag(begin, 'R');
	flag_next = begin->next || flag_R ? 1 : 0;
	save_begin = begin;
	while (begin)
	{
		put_path(begin);
		if (begin->next)
			begin->next->col = begin->col;
		if (flag_next)
			ft_printf("%s:\n", begin->d_path);
		sort_paths(begin->paths);
		if (check_flag(begin, 'l'))
			output_lpaths(begin);
		else
			output_paths(begin);
		if (begin->next)
			ft_printf("\n");
		begin = begin->next;
	}
	begin = save_begin;
}