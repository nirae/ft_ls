/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 16:52:47 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/17 18:09:58 by ndubouil         ###   ########.fr       */
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
	//struct dirent	**dir_infos;
	struct stat		stat_infos;
	char			*name;
}					t_lsfile;

typedef struct		s_ftlsenv
{
	t_options		options;
	t_btree			*tree;
}					t_ftlsenv;

#endif
