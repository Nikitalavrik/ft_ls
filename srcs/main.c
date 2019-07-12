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
		begin = parsing(argc, argv, begin);
		output_ls(begin);
	}
	return (0);
}