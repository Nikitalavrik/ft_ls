/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 11:03:37 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/11 11:03:40 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_flags(t_ls *begin, char *flags)
{
	int		i;

	i = 0;
	while (flags[i])
	{	
		if (flags[i] == 'a')
			begin->flag->a = 1;
		if (flags[i] == 'l')
			begin->flag->l = 1;
		if (flags[i] == 't')
			begin->flag->t = 1;
		if (flags[i] == 'r')
			begin->flag->r = 1;
		if (flags[i] == 'R')
			begin->flag->R = 1;
		if (flags[i] == 'f')
			begin->flag->f = 1;
		if (flags[i] == 'g')
		{
			begin->flag->g = 1;
			begin->flag->l = 1;
		}
		if (flags[i] == 'G')
			begin->flag->G = 1;
		if (flags[i] == '1')
			begin->flag->one = 1;
		i++;
	}
}

int		check_valid_flags(char c)
{
	int		i;
	char	*valid_flags;

	i = 0;
	valid_flags = "arltRfguG1";
	while (valid_flags[i])
	{
		if (valid_flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		parsing(int argc, char **argv, t_ls *begin)
{
	t_ls	*save_begin;
	int		i;
	int		k;
	int		f;
	char	flags[20];

	i = 1;
	f = 0;
	k = 0;
	ft_bzero(flags, 20);
	save_begin = begin;
	while (i < argc)
	{
		if (argv[i][0] == '-' && !k)
		{
			k = 0;
			while (argv[i][k + 1] && argv[i][k + 1] != ' ' && k < 20)
			{
				if (check_valid_flags(argv[i][k + 1]) && argv[i][k + 1] != 'h')
				{
					if (!check_flag(flags, argv[i][k + 1]))
						flags[f++] = argv[i][k + 1];
				}
				else
					return (0);
				k++;
			}
			parse_flags(begin, flags);
		}
		else if (!begin->d_path)
			begin->d_path = ft_strdup(argv[i]);
		else
			begin = add_node(begin, ft_strdup(argv[i]));
		i++;
	}
	return (1);
}

int		check_LNK(char *dirname, t_ls *begin)
{
	struct stat stats;

	if (!dirname || !begin->flag->l)
		return (0);
	lstat(dirname, &stats);
	if (S_ISLNK(stats.st_mode) && dirname[ft_strlen(dirname) - 1] != '/')
	{
		begin->paths = create_path();
		begin->paths->path = ft_strdup(dirname);
		begin->paths->stats = stats;
		begin->w_rows = 0;
		calc_max(begin, begin->paths);
		return (1);
	}
	return (0);
}
