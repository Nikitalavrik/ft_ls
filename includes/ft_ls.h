/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:59:08 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/09 17:59:09 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <stdarg.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

int		ft_printf(const char *s, ...);

typedef	struct		s_path
{
	char			*path;
	struct	stat	stats;
	struct	s_path	*next;
}					t_path;


typedef	struct		s_ls
{
	struct	s_path	*paths;
	char			*d_path;
	DIR				*dir;
	int				w_rows;
	int				w_columns;
	int				col;
	char			flags[5];
	struct	s_ls	*next;
}					t_ls;

void				sys_output_path(t_path *begin);
void				sys_print_node(t_ls *begin);

void				output_ls(t_ls *begin);

t_ls				*create_ls(void);
t_ls				*add_node(t_ls *begin, char *path);
int					check_flag(t_ls *begin, char flag);

t_path				*create_path(void);
t_path				*add_path(t_path *begin);
int					ft_lstlen(t_path *begin);
char				*pathcat(char *dir, char *file);

t_ls				*parsing(int argc, char **argv, t_ls *begin);

void				out_permision(unsigned long perm);
void				out_num_link(unsigned long num);
void				out_owner_group(struct stat stats);
void				out_num_bytes(unsigned int num);
void				out_time_modify(struct stat stats);

#endif