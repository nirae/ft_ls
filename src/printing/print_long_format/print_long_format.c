/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 01:09:04 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/27 21:07:21 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Free the struct t_lformat
*/

static void		del_tool(t_lformat *tool)
{
	ft_strdel(&tool->owner);
	ft_strdel(&tool->group);
	ft_strdel(&tool->mode);
	ft_strdel(&tool->link);
}

/*
**	Setting the struct t_lformat with the file informations
*/

static void		set_tool(t_lformat *tool, t_lsfile *file)
{
	if (!(tool->link = ft_strnew(file->st.st_size)))
		err_malloc();
	if (!(tool->mode = get_mode(file->st.st_mode)))
		err_malloc();
	if (!(tool->owner = ft_strdup(get_owner(file->st.st_uid))))
		tool->owner = ft_itoa(file->st.st_uid);
	if (!(tool->group = ft_strdup(get_group(file->st.st_gid))))
		tool->group = ft_itoa(file->st.st_gid);
}

void			print_ifdevices_nocb(t_lsfile *f, t_ftlsenv *env, t_lformat t)
{
	ft_printf("%c%s  %*d %-*s  %-*s    %*c %*d ",
		get_type(f->st.st_mode),
		t.mode,
		env->len_max_links,
		f->st.st_nlink,
		env->len_max_owner,
		t.owner,
		env->len_max_group,
		t.group,
		env->len_max_major,
		' ',
		env->len_max_minor,
		minor(f->st.st_rdev));
}

void			print_ifdevices(t_lsfile *file, t_ftlsenv *env, t_lformat tool)
{
	char		*maj;
	char		*min;
	int			i;

	if (!(maj = ft_itoa(major(file->st.st_rdev))))
		err_malloc();
	if (!(min = ft_itoa(minor(file->st.st_rdev))))
		err_malloc();
	i = -1;
	while (maj[++i] == '0' && (maj[i + 1] != '0' && maj[i + 1] != '\0'))
		maj[i] = ' ';
	i = -1;
	while (min[++i] == '0' && (min[i + 1] != '0' && min[i + 1] != '\0'))
		min[i] = ' ';
	if (!S_ISCHR(file->st.st_mode) && !S_ISBLK(file->st.st_mode))
		print_ifdevices_nocb(file, env, tool);
	else
		ft_printf("%c%s  %*d %-*s  %-*s   %*s, %*s ",
			get_type(file->st.st_mode), tool.mode, env->len_max_links,
			file->st.st_nlink, env->len_max_owner, tool.owner,
			env->len_max_group, tool.group, env->len_max_major, maj,
			env->len_max_minor, min);
	ft_strdel(&maj);
	ft_strdel(&min);
}

/*
**	Printer for the long format "-l" option
**	Setting the struct with set_tool(), print with the good formatting and free
**	the struct with del_tool()
*/

void			print_long_format(t_lsfile *file, t_ftlsenv *env)
{
	t_lformat	tool;

	set_tool(&tool, file);
	if (env->ifdevices)
		print_ifdevices(file, env, tool);
	else
		ft_printf("%c%s  %*d %-*s  %-*s  %*lld ",
			get_type(file->st.st_mode), tool.mode, env->len_max_links,
			file->st.st_nlink, env->len_max_owner, tool.owner,
			env->len_max_group, tool.group, env->len_max_size,
			file->st.st_size);
	print_time(file->st, env->options);
	ft_printf(" %s", file->name);
	if (get_type(file->st.st_mode) == 'l')
	{
		readlink(file->path, tool.link, file->st.st_size + 1);
		ft_printf(" -> %s\n", tool.link);
	}
	else
		ft_printf("\n");
	del_tool(&tool);
}
