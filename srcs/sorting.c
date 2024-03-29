/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:12:00 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/15 14:12:00 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		simple_sort(char *s1, char *s2)
{
	return (ft_strcmp(s1, s2) > 0);
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
	tmp_path = swap_path->pw_name;
	swap_path->pw_name = swap_path->next->pw_name;
	swap_path->next->pw_name = tmp_path;
	tmp_path = swap_path->gr_name;
	swap_path->gr_name = swap_path->next->gr_name;
	swap_path->next->gr_name = tmp_path;
}

void	sort_rev(t_path **begin)
{
	t_path	*tmp_path;
	t_path	*tmp_prev;
	t_path	*tmp_next;

	tmp_path = *begin;
	tmp_prev = NULL;
	tmp_next = NULL;
	while (tmp_path)
	{
		tmp_next = tmp_path->next;
		tmp_path->next = tmp_prev;
		tmp_prev = tmp_path;
		tmp_path = tmp_next;
	}
	*begin = tmp_prev;
}

void	sort_paths(t_path *begin, int f(char *s1, char *s2))
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
			if (f(tmp_begin->path, tmp_begin->next->path))
				swap_paths(tmp_begin);
			tmp_begin = tmp_begin->next;
		}
		tmp_begin = begin;
		i++;
	}
}

void	sort_paths_time(t_path *begin)
{
	t_path	*tmp_begin;
	time_t	mod_time;
	int		i;
	int		len;

	i = 0;
	len = ft_lstlen(begin);
	tmp_begin = begin;
	while (i < len)
	{
		while (tmp_begin->next)
		{
			mod_time = tmp_begin->stats.st_mtimespec.tv_sec;
			if (mod_time < tmp_begin->next->stats.st_mtimespec.tv_sec)
				swap_paths(tmp_begin);
			tmp_begin = tmp_begin->next;
		}
		tmp_begin = begin;
		i++;
	}
}
