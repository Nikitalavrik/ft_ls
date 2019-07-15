/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:32:46 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/12 11:32:47 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		out_permision(unsigned long perm)
{
	char type;

	type = S_ISDIR(perm) ? 'd' : '-';
	type = S_ISLNK(perm) ? 'l' : type;
	type = S_ISCHR(perm) ? 'c' : type;
	type = S_ISBLK(perm) ? 'b' : type;
	ft_printf("%c%c%c%c%c%c%c%c%c%c", 
	type,
	(perm & S_IRUSR) ? 'r' : '-',
	(perm & S_IWUSR) ? 'w' : '-',
	(perm & S_IXUSR) ? 'x' : '-',
	(perm & S_IRGRP) ? 'r' : '-',
	(perm & S_IWGRP) ? 'w' : '-',
	(perm & S_IXGRP) ? 'x' : '-',
	(perm & S_IROTH) ? 'r' : '-',
	(perm & S_IWOTH) ? 'w' : '-',
	(perm & S_IXOTH) ? 'x' : '-');
	return (type == 'l');
}

void	out_num_bytes(unsigned int num, struct stat stats, t_ls *begin)
{

	if (S_ISBLK(stats.st_mode) || S_ISCHR(stats.st_mode))
		ft_printf(" %5u, %3u", major(stats.st_rdev), minor(stats.st_rdev));
	else if (begin->device)
		ft_printf(" %10u", num);
	else
		ft_printf(" %5u", num);
}

void	out_time_modify(struct stat stats)
{
	time_t	mod_time;
	char	*str;
	char	time_str[14];
	int i;

	mod_time = stats.st_mtimespec.tv_sec;
	str = ctime(&mod_time);
	i = 3;
	while (i < 16)
	{
		time_str[i - 3] = str[i];
		i++;
	}
	time_str[13] = '\0';
	ft_printf("%s", time_str);
}
