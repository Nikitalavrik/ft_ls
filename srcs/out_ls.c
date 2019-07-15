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

int		count_space(int max_len, t_ls *begin)
{
	int i;
	int	total_size;

	i = 8;
	while (i < max_len)
		i += 8;
	total_size = i * begin->count_files;
	total_size = total_size / begin->w_columns + 1;
	ft_printf("raws = %i\n", total_size);
	return (i);
}

void	output_paths(t_ls *begin)
{
	t_path	*tmp_path;
	int		sum_column;

	sum_column = 0;
	tmp_path = begin->paths;
	begin->col = count_space(begin->col, begin);
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

char	*get_link(t_ls *begin, char *path)
{
	char	*str;
	char	static buf[512];
	int		count;

	count = 0;
	ft_bzero(buf, sizeof(buf));
	str = pathcat(begin->d_path, path);
	count = readlink(str, buf, sizeof(buf));
	return (buf);
}

void	output_lpaths(t_ls *begin)
{
	t_path *tmp_path;
	int		flag_l;

	tmp_path = begin->paths;
	ft_printf("total %i\n", begin->block_size);
	while (tmp_path)
	{
		flag_l = out_permision(tmp_path->stats.st_mode);
		ft_printf(" %*llu", begin->max_numlink + 1, tmp_path->stats.st_nlink);
		ft_printf(" %-*s %-*s", begin->max_uid + 1, tmp_path->pw_name,\
							begin->max_group + 1, tmp_path->gr_name);
		out_num_bytes(tmp_path->stats.st_size, tmp_path->stats, begin);
		out_time_modify(tmp_path->stats);
		ft_printf(" %s", tmp_path->path);
		if (flag_l)
			ft_printf(" -> %s", get_link(begin, tmp_path->path));
		ft_printf("\n");
		tmp_path = tmp_path->next;
	}
	free_paths(begin->paths);
}

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

void	calc_max(t_ls *begin, t_path *path)
{	
	int				len;
	struct	passwd	*pw;
	struct	group	*gr;

	pw = getpwuid(path->stats.st_uid);
	gr = getgrgid(path->stats.st_gid);

	len = ft_nbrlen(path->stats.st_nlink);
	begin->max_numlink =  len > begin->max_numlink ? len : begin->max_numlink;
	path->gr_name = ft_strdup(gr->gr_name);
	len = ft_strlen(gr->gr_name);
	begin->max_group = len > begin->max_group ? len : begin->max_group;
	path->pw_name = ft_strdup(pw->pw_name);
	len = ft_strlen(pw->pw_name);
	begin->max_uid = len > begin->max_uid ? len : begin->max_uid;
}

void	put_path(t_ls *begin)
{
	struct	dirent	*rd;
	t_path			*tmp_path;
	int				max_len;
	int				flag;
	int				flag_l;
	char			*conc_path;


	max_len = 0;
	begin->d_path = begin->d_path ? begin->d_path : ft_strdup(".");
	begin->dir = opendir(begin->d_path);
	tmp_path = begin->paths;
	flag = check_flag(begin, 'R');
	flag_l = check_flag(begin, 'l');
	if (begin->dir)
	{
		while ((rd = readdir(begin->dir)))
		{
			if (rd->d_name[0] != '.' || check_flag(begin, 'a'))
			{
				max_len = rd->d_namlen > max_len ? rd->d_namlen : max_len;
				if (tmp_path->path)
					tmp_path = add_path(tmp_path);
				tmp_path->path = ft_strdup(rd->d_name);
				conc_path = pathcat(begin->d_path, rd->d_name);
				// ft_printf("path = %s d_name = %s\n", conc_path, rd->d_name);
				lstat(conc_path, &(tmp_path->stats));
				calc_max(begin, tmp_path);
				begin->block_size += tmp_path->stats.st_blocks;
				if (S_ISBLK(tmp_path->stats.st_mode) || S_ISCHR(tmp_path->stats.st_mode))
					begin->device = 1;
				if (flag && (S_ISDIR(tmp_path->stats.st_mode) && !S_ISLNK(tmp_path->stats.st_mode)))
					add_node(begin, conc_path);
				else
					ft_memdel((void **)&conc_path);
				begin->count_files++;
			}
		}
		closedir(begin->dir);
		begin->col = max_len + 1;
	}
}

void	output_ls(t_ls *begin)
{
	t_ls *save_begin;
	int		flag_next;
	int		flag_R;
	char	*init_dir;

	flag_R = check_flag(begin, 'R');
	flag_next = begin->next || flag_R ? 1 : 0;
	save_begin = begin;
	init_dir = begin->d_path;
	while (begin)
	{
		put_path(begin);
		if (begin->next)
			begin->next->col = begin->col;
		if (flag_next)
			ft_printf("%s:\n", begin->d_path);
		if (check_flag(begin, 'r'))
			sort_paths(begin->paths, &reverse_sort);
		else if (check_flag(begin, 't'))
			sort_paths_time(begin->paths);
		else
			sort_paths(begin->paths, &simple_sort);
		if (check_flag(begin, 'l'))
			output_lpaths(begin);
		else
			output_paths(begin);
		if (begin->next)
			ft_printf("\n");
		begin = begin->next;
	}
	begin = save_begin;
	// free_dirs(begin);
	// system("leaks ft_ls");
}