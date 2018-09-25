/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 16:52:47 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 18:32:31 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "libftprintf.h"

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>

# define TRUE		1
# define FALSE		0
# define OPTS		"Raflrt"

typedef int		(*t_func_ptr)(void *, void *);

typedef struct	s_date
{
	char		month[4];
	char		day[3];
	char		hour[3];
	char		min[3];
	char		year[5];
}				t_date;

typedef struct	s_lformat
{
	char		*mode;
	char		*link;
	char		*owner;
	char		*group;
}				t_lformat;

typedef struct	s_options
{
	int			l;
	int			a;
	int			big_r;
	int			r;
	int			t;
	int			f;
}				t_options;

typedef struct	s_lsfile
{
	char		*path;
	struct stat	st;
	char		*name;
}				t_lsfile;

typedef struct	s_ftlsenv
{
	t_options	options;
	t_btree		*tree;
	int			len_max_links;
	int			len_max_size;
	int			len_max_owner;
	int			len_max_group;
	int			nb_rep;
	int			nb_files;
}				t_ftlsenv;

/*
**	SORT (src/sort/)
*/

t_func_ptr		get_sort_func(t_options opt);
int				basic_sort(void *a, void *b);
int				basic_sort_rev(void *a, void *b);
int				mtime_nano_sort(void *a, void *b);
int				mtime_nano_sort_rev(void *a, void *b);
int				mtime_sort(void *a, void *b);
int				mtime_sort_rev(void *a, void *b);
int				f_sort(void *a, void *b);
int				f_sort_rev(void *a, void *b);

/*
**	TREES TOOLS (src/trees_tools.c)
*/

t_lsfile		*create_file(char *name, char *path, struct stat st);
void			del_file(void *data);
void			ft_btree_apply_infix_forls(t_btree *tree, t_ftlsenv *env,
					void (*func)(void *, t_ftlsenv *env));
void			ft_btree_apply_rev_infix_forls(t_btree *tree, t_ftlsenv *env,
					void (*func)(void *, t_ftlsenv *env));
void			create_tree(t_btree **tree, t_lsfile *file, t_ftlsenv *env);

/*
** PARSING (src/parsing.c)
*/

int				ls_parser(char **av, t_ftlsenv *env, t_btree **args);

/*
** PRINTING (src/printing/)
*/

void			ls_printer(void *tree, t_ftlsenv *env);
void			print_long_format(t_lsfile *file, t_ftlsenv *env);

char			get_type(mode_t mode);
char			*get_mode(mode_t mode);
char			*get_owner(uid_t uid);
char			*get_group(gid_t gid);
void			print_time(time_t *timer);
void			print_files_args(void *tree, t_ftlsenv *env);
void			print_dir_args(void *tree, t_ftlsenv *env);
void			print_tree(void *tree);
void			print_recursive(void *tree, t_ftlsenv *env);

/*
** LOGIC OF THE LS (src/ft_ls.c)
*/

int				ft_ls(char *path, t_ftlsenv *env);

/*
** ERROR MANAGEMENT (src/errors.c)
*/

int				catch_error(char *path);
void			err_malloc(void);

#endif
