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
	// char *str1;
	// char *str2;
	// char *res;


	// str1 = "libft";
	// str2 = "ft_bzero.c";
	// res = pathcat(str1, str2);
	// if (argc && argv)
	// 	ft_printf("|%s|\n", res);
	// free(res);

		// system("leaks ft_ls");
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
	// system("leaks ft_ls");
	return (0);
}