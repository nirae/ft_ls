/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 01:09:04 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/28 19:49:47 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void			print_link(t_lsfile *file, t_lformat tool)
{
	if (ft_strcmp(file->name, "stderr") == 0)
		ft_printf(" -> fd/2\n");
	else if (ft_strcmp(file->name, "stdin") == 0)
		ft_printf(" -> fd/0\n");
	else if (ft_strcmp(file->name, "stdout") == 0)
		ft_printf(" -> fd/1\n");
	else
	{
		readlink(file->path, tool.link, file->st.st_size + 1);
		ft_printf(" -> %s\n", tool.link);
	}
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
		print_link(file, tool);
	else
		ft_printf("\n");
	del_tool(&tool);
}
