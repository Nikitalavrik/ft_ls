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

void	put_flag(t_ls *begin, char c)
{
	if (c == 'a')
		begin->flag->a = 1;
	if (c == 'l')
		begin->flag->l = 1;
	if (c == 't')
		begin->flag->t = 1;
	if (c == 'r')
		begin->flag->r = 1;
	if (c == 'R')
		begin->flag->rr = 1;
	if (c == 'f')
		begin->flag->f = 1;
	if (c == 'g')
	{
		begin->flag->g = 1;
		begin->flag->l = 1;
	}
	if (c == 'G')
		begin->flag->gg = 1;
	if (c == '1')
		begin->flag->one = 1;
}

void	parse_flags(t_ls *begin, char *flags)
{
	int		i;

	i = 0;
	while (flags[i])
	{
		put_flag(begin, flags[i]);
		i++;
	}
}

int		check_valid_flags(char c)
{
	int		i;
	char	*valid_flags;

	i = 0;
	valid_flags = "arltRfgG1";
	while (valid_flags[i])
	{
		if (valid_flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		put_check_flag(char *argv, t_ls *tmp)
{
	int		k;
	char	flags[20];
	int		f;

	k = 0;
	f = 0;
	ft_bzero(flags, 20);
	while (argv[k + 1] && argv[k + 1] != ' ' && k < 20)
	{
		tmp->flag->error = argv[k + 1] == 'h';
		if (check_valid_flags(argv[k + 1]) && argv[k + 1] != 'h')
		{
			if (!check_flag(flags, argv[k + 1]))
				flags[f++] = argv[k + 1];
		}
		else
			return (0);
		k++;
	}
	parse_flags(tmp, flags);
	return (1);
}

int		parsing(int argc, char **argv, t_ls *begin)
{
	t_ls	*tmp;
	int		i;
	int		k;

	i = 1;
	k = 0;
	tmp = begin;
	while (i < argc)
	{
		if (argv[i][0] == '-' && !k)
		{
			if (!(k = put_check_flag(argv[i], tmp)))
				return (0);
		}
		else if (!tmp->d_path)
			tmp->d_path = ft_strdup(argv[i]);
		else
			tmp = add_node(tmp, ft_strdup(argv[i]));
		i++;
	}
	return (1);
}
