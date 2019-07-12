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

void	out_permision(unsigned long perm)
{
	ft_printf("%c%c%c%c%c%c%c%c%c%c", 
	S_ISDIR(perm) ? 'd' : '-',
	(perm & S_IRUSR) ? 'r' : '-',
	(perm & S_IWUSR) ? 'w' : '-',
	(perm & S_IXUSR) ? 'x' : '-',
	(perm & S_IRGRP) ? 'r' : '-',
	(perm & S_IWGRP) ? 'w' : '-',
	(perm & S_IXGRP) ? 'x' : '-',
	(perm & S_IROTH) ? 'r' : '-',
	(perm & S_IWOTH) ? 'w' : '-',
	(perm & S_IXOTH) ? 'x' : '-');
}

void	out_num_link(unsigned long num)
{
	ft_printf("%5llu", num);
}

void	out_owner_group(struct stat stats)
{
	struct	passwd	*pw;
	struct	group	*gr;

	pw = getpwuid(stats.st_uid);
	gr = getgrgid(stats.st_gid);

	ft_printf(" %s  %s", pw->pw_name, gr->gr_name);
}

void	out_num_bytes(unsigned int num)
{
	ft_printf(" %6u", num);
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
