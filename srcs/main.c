/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:59:20 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/09 17:59:21 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"



int		main(int argc, char **argv)
{
	t_ls *begin;
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	begin = create_ls();
	begin->w_rows = w.ws_row;
	begin->w_columns = w.ws_col;
	if (argc > 0 && argv)
	{
		if (parsing(argc, argv, begin))
			output_ls(begin);
			// ft_printf("OK\n");
		else
		{
			if (!begin->flag->error)
				ft_printf("./ft_ls: illegal option\n");
			ft_printf("usage : ./ft_ls [-arltRfgG1] [file ...]\n");
			ft_memdel((void **)&begin);
		}
		// system("leaks ft_ls");
	}
	return (0);
}