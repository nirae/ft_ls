/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 21:01:29 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 00:58:28 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_long_format(t_lsfile *file, t_ftlsenv *env)
{
	char	*mode;
	char	*link;
	char	*owner;
	char	*group;

	// malloc a proteger
	link = ft_strnew(file->st.st_size);
	mode = get_mode(file->st.st_mode);
	// owner
	if (!(owner = ft_strdup(get_owner(file->st.st_uid))))
		owner = ft_itoa(file->st.st_uid);
	// group
	if (!(group= ft_strdup(get_group(file->st.st_gid))))
		group = ft_itoa(file->st.st_gid);
	// affichage
	ft_printf("%c%s  %*d %-*s  %-*s  %*lld ",
			get_type(file->st.st_mode),
			mode,
			env->len_max_links,
			file->st.st_nlink,
			env->len_max_owner,
			owner,
			env->len_max_group,
			group,
			env->len_max_size,
			file->st.st_size
		);
	print_time(&file->st.st_mtimespec.tv_sec);
	ft_printf(" %s", file->name);
	if (get_type(file->st.st_mode) == 'l')
	{
		readlink(file->path, link, file->st.st_size + 1);
		ft_printf(" -> %s\n", link);
	}
	else
		ft_printf("\n");
	ft_strdel(&owner);
	ft_strdel(&group);
	ft_strdel(&mode);
	ft_strdel(&link);
}
