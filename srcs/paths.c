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
	path->gr_name = NULL;
	path->pw_name = NULL;
	path->is_dir = 0;
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

char	*pathcat(char *dir, char *file)
{
	char *ret;
	int len;
	int i;
	int j;

	i = 0;
	j = ft_strlen(file);
	len = ft_strlen(dir);
	ret = ft_memalloc(sizeof(char) * (len + j +\
		(ft_get_index(dir, '/') == (unsigned int)len ? 1 : 2)));
	while (i < len)
	{
		ret[i] = dir[i];
		i++;
	}
	if (ret[i - 1] != '/')
		ret[i++] = '/';
	len = j;
	j = 0;
	while (j < len)
	{
		ret[i] = file[j];
		j++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
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
