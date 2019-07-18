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
# include <stdio.h>
# define RED "[0;31m"
# define GREEN "[0;32m"
# define RESET "[0m"
# define YELLOW "[0;33m"
# define MAGENTA "[1;35m"
# define BLUE "[0;34m"

int					ft_printf(const char *s, ...);

typedef	struct		s_path
{
	char			*path;
	char			*pw_name;
	char			*gr_name;
	int				is_dir;
	struct stat		stats;
	struct s_path	*next;
}					t_path;

typedef struct		s_flags
{
	int				l;
	int				r;
	int				rr;
	int				t;
	int				f;
	int				a;
	int				g;
	int				gg;
	int				one;
	int				error;
	int				exist;
	int				first;
	int				f_row;
}					t_flags;

typedef	struct		s_ls
{
	struct s_path	*paths;
	struct s_flags	*flag;
	char			*d_path;
	DIR				*dir;
	int				w_rows;
	int				w_columns;
	int				col;
	int				block_size;
	int				max_numlink;
	int				max_uid;
	int				max_group;
	int				device;
	int				max_filename;
	int				max_bytes;
	int				count_files;
	struct s_ls		*next;
}					t_ls;

void				sys_output_path(t_path *begin);
void				sys_print_node(t_ls *begin);

void				output_ls(t_ls *begin);

t_ls				*create_ls(void);
t_ls				*add_node(t_ls *begin, char *path);
int					check_flag(char *flags, char flag);
void				copy_node_param(t_ls *begin, t_ls *new_node);
int					check_lnk(char *dirname, t_ls *begin);

t_path				*create_path(void);
t_path				*add_path(t_path *begin);
int					ft_lstlen(t_path *begin);
char				*pathcat(char *dir, char *file);
void				calc_max(t_ls *begin, t_path *path);

int					parsing(int argc, char **argv, t_ls *begin);
void				recursion(t_ls *begin);
void				iter_ls(t_ls *begin, int f_row);
void				output_paths(t_ls *begin);
void				output_lpaths(t_ls *begin);
int					put_path(t_ls *begin);

char				*get_link(t_ls *begin, char *path);
void				color_print(unsigned long num);
int					out_permision(unsigned long perm);
void				out_num_bytes(unsigned int num, struct stat stats,\
																t_ls *begin);
void				out_time_modify(struct stat stats);

int					simple_sort(char *s1, char *s2);
void				sort_paths(t_path *begin, int f(char *s1, char *s2));
void				sort_paths_time(t_path *begin);
void				sort_rev(t_path **begin);

void				free_dirs(t_ls *begin);
void				free_paths(t_path *paths);
int					ft_nbrlen(int num);
int					count_space(int max_len);

#endif
