/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 16:52:47 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/22 03:52:14 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "libftprintf.h"

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# define TRUE 1
# define FALSE 0

# define ILLEGAL_OP 3

typedef struct		s_options
{
	int				l;
	int				a;
	int				R;
	int				r;
	int				t;
}					t_options;

typedef struct		s_lsfile
{
	char			*path;
	struct stat		stat_infos;
	char			*name;
}					t_lsfile;

typedef struct		s_ftlsenv
{
	t_options		options;
	t_btree			*tree;
}					t_ftlsenv;

/*
**	SORT (src/sort.c)
*/

int					(*get_sort_func(t_options opt))(void *, void *);

/*
**	TREES TOOLS (src/trees_tools.c)
*/

t_lsfile	*create_file(char *name, char *path, struct stat st);
void		ft_btree_apply_infix_forls(t_btree *tree, t_ftlsenv *env,
				void (*func)(void *, t_ftlsenv *env));
void		ft_btree_apply_rev_infix_forls(t_btree *tree, t_ftlsenv *env,
				void (*func)(void *, t_ftlsenv *env));
void		create_tree(t_btree **tree, t_lsfile *file, t_ftlsenv *env);

/*
** PARSING (src/parsing.c)
*/

int			ls_parser(char **av, t_ftlsenv *env, t_btree **args);

#endif
