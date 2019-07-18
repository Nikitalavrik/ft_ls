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

void	output_paths(t_ls *begin)
{
	t_path	*tmp_path;
	int		sum_column;

	sum_column = 0;
	tmp_path = begin->paths;
	begin->col = begin->flag->one ? 0 : count_space(begin->col);
	while (tmp_path && tmp_path->path)
	{
		if (!begin->flag->one)
		{
			sum_column += begin->col;
			if (sum_column > begin->w_columns)
			{
				sum_column = begin->col;
				ft_printf("\n");
			}
		}
		if (begin->flag->gg)
			color_print(tmp_path->stats.st_mode);
		ft_printf("%-*s\033%s", begin->col, tmp_path->path, RESET);
		begin->flag->one ? ft_printf("\n") : 0;
		tmp_path = tmp_path->next;
	}
	if (!begin->flag->one && begin->paths->path)
		ft_printf("\n");
}

void	output_lpaths(t_ls *begin)
{
	t_path	*tmp_path;
	int		flag_l;

	tmp_path = begin->paths;
	if (tmp_path && tmp_path->path && begin->w_rows)
		ft_printf("total %i\n", begin->block_size);
	while (tmp_path && tmp_path->path)
	{
		if (begin->flag->gg)
			color_print(tmp_path->stats.st_mode);
		flag_l = out_permision(tmp_path->stats.st_mode);
		ft_printf(" %*llu", begin->max_numlink + 1, tmp_path->stats.st_nlink);
		if (!begin->flag->g)
			ft_printf(" %-*s", begin->max_uid + 1, tmp_path->pw_name);
		ft_printf(" %-*s", begin->max_group + 1, tmp_path->gr_name);
		out_num_bytes(tmp_path->stats.st_size, tmp_path->stats, begin);
		out_time_modify(tmp_path->stats);
		ft_printf(" %s\033%s", tmp_path->path, RESET);
		if (flag_l)
			ft_printf(" -> %s", get_link(begin, tmp_path->path));
		ft_printf("\n");
		tmp_path = tmp_path->next;
	}
}

void	put_lstat(t_ls *begin, t_path *tmp_path, struct dirent *rd, int *m_len)
{
	char	*conc_path;

	*m_len = rd->d_namlen > *m_len ? rd->d_namlen : *m_len;
	if (tmp_path->path)
		tmp_path = add_path(tmp_path);
	tmp_path->path = ft_strdup(rd->d_name);
	conc_path = pathcat(begin->d_path, rd->d_name);
	lstat(conc_path, &(tmp_path->stats));
	calc_max(begin, tmp_path);
	begin->block_size += tmp_path->stats.st_blocks;
	if (S_ISBLK(tmp_path->stats.st_mode) ||\
			S_ISCHR(tmp_path->stats.st_mode))
		begin->device = 1;
	ft_memdel((void **)&conc_path);
	begin->count_files++;
}

int		put_path(t_ls *begin)
{
	struct dirent	*rd;
	t_path			*tmp_path;
	int				max_len;

	max_len = 0;
	begin->d_path = begin->d_path ? begin->d_path : ft_strdup(".");
	begin->dir = opendir(begin->d_path);
	tmp_path = begin->paths;
	if (begin->dir)
	{
		while ((rd = readdir(begin->dir)))
		{
			if (rd->d_name[0] != '.' || begin->flag->a || begin->flag->f)
				put_lstat(begin, tmp_path, rd, &max_len);
		}
		closedir(begin->dir);
		begin->col = max_len + 1;
		return (1);
	}
	else
		begin->flag->error = 1;
	return (begin->flag->rr);
}

void	output_ls(t_ls *begin)
{
	t_ls	*save_begin;
	int		f_row;

	save_begin = begin;
	f_row = begin->flag->f_row;
	begin->flag->exist = begin->d_path ? 1 : 0;
	while (begin)
	{
		iter_ls(begin, f_row);
		begin = begin->next;
	}
	free_dirs(save_begin);
}
