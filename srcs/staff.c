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

int		check_lnk(char *dirname, t_ls *begin)
{
	struct stat stats;

	if (!dirname)
		return (0);
	lstat(dirname, &stats);
	if ((S_ISLNK(stats.st_mode) && dirname[ft_strlen(dirname) - 1] != '/'\
	&& begin->flag->l) || S_ISREG(stats.st_mode))
	{
		begin->paths->path = ft_strdup(dirname);
		begin->paths->stats = stats;
		begin->w_rows = 0;
		calc_max(begin, begin->paths);
		return (1);
	}
	return (0);
}

void	recursion(t_ls *begin)
{
	t_path	*tmp_path;
	char	*conc_path;
	t_ls	*next_r;

	tmp_path = begin->paths;
	while (tmp_path)
	{
		conc_path = pathcat(begin->d_path, tmp_path->path);
		if (begin->flag->rr && S_ISDIR(tmp_path->stats.st_mode) &&\
		!S_ISLNK(tmp_path->stats.st_mode) && ft_strcmp(tmp_path->path, ".")\
		&& ft_strcmp(tmp_path->path, "..") && begin->flag->first)
		{
			next_r = create_ls();
			copy_node_param(begin, next_r);
			next_r->d_path = conc_path;
			output_ls(next_r);
		}
		else
			ft_memdel((void **)&conc_path);
		tmp_path = tmp_path->next;
	}
}

void	iter_ls(t_ls *begin, int f_row)
{
	if (!check_lnk(begin->d_path, begin))
		put_path(begin);
	begin->flag->first = begin->flag->rr;
	(f_row && begin->w_rows) ? ft_printf("\n") : 0;
	(begin->flag->error) ? perror(begin->d_path) : 0;
	if ((begin->d_path || begin->flag->rr) && begin->flag->exist\
	&& begin->w_rows && !begin->flag->error)
		ft_printf("%s:\n", begin->d_path);
	if (begin->next)
		begin->next->col = begin->col;
	if (!begin->flag->f)
	{
		if (begin->flag->t)
			sort_paths_time(begin->paths);
		else
			sort_paths(begin->paths, &simple_sort);
		if (begin->flag->r)
			sort_rev(&begin->paths);
	}
	(begin->flag->l) ? output_lpaths(begin) : output_paths(begin);
	f_row = 1;
	begin->flag->f_row = f_row;
	if (begin->flag->first)
		recursion(begin);
}
