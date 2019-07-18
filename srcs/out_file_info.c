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
		ft_printf(" %*u", begin->max_bytes, num);
}

void	out_time_modify(struct stat stats)
{
	time_t	mod_time;
	char	*str;
	char	time_str[14];
	time_t	time_now;
	int		i;

	mod_time = stats.st_mtimespec.tv_sec;
	str = ctime(&mod_time);
	time(&time_now);
	ft_bzero(time_str, 14);
	i = 3;
	while (i < 11)
	{
		time_str[i - 3] = str[i];
		i++;
	}
	i += time_now - mod_time > 15778463 ? 8 : 0;
	mod_time = time_now - mod_time > 15778463 ? 8 : 0;
	while (i < 16 + mod_time)
	{
		time_str[i - (3 + mod_time)] = str[i];
		i++;
	}
	ft_printf("%s", time_str);
}

void	color_print(unsigned long num)
{
	if (S_ISDIR(num))
		ft_printf("\033%s", GREEN);
	else if (S_ISLNK(num))
		ft_printf("\033%s", RED);
	else if (S_ISCHR(num))
		ft_printf("\033%s", MAGENTA);
	else if (S_ISBLK(num))
		ft_printf("\033%s", BLUE);
	else
		ft_printf("\033%s", YELLOW);
}

char	*get_link(t_ls *begin, char *path)
{
	char		*str;
	static char	buf[512];
	int			count;

	count = 0;
	ft_bzero(buf, sizeof(buf));
	if (begin->w_rows)
		str = pathcat(begin->d_path, path);
	else
		str = path;
	count = readlink(str, buf, sizeof(buf));
	if (begin->w_rows)
		free(str);
	return (buf);
}
