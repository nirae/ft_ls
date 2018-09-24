/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 21:01:29 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/24 01:28:55 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

static char		get_type(mode_t mode)
{
	if ((mode & S_IFMT) == S_IFDIR)
		return ('d');
	else if ((mode & S_IFMT) == S_IFREG)
		return ('-');
	else if ((mode & S_IFMT) == S_IFLNK)
		return ('l');
	else if ((mode & S_IFMT) == S_IFCHR)
		return ('c');
	else if ((mode & S_IFMT) == S_IFBLK)
		return ('b');
	else if ((mode & S_IFMT) == S_IFSOCK)
		return ('s');
	else if ((mode & S_IFMT) == S_IFIFO)
		return ('p');
	return ('?');
}

static char		*get_mode(mode_t mode)
{
	char	model[] = "rwxrwxrwx";
	char	*result;
	//char	result[10];
	int		i = -1;

	result = ft_strnew(sizeof(char) * 9);
	while (++i < 9)
	{
		if (mode & (1 << (8 - i)))
			result[i] = model[i];
		else
			result[i] = '-';
	}
	//result[9] = '\0';
	return (result);
}

char		*get_owner(uid_t uid)
{
	struct passwd *tmp;

	if (!(tmp = getpwuid(uid)))
		return (NULL);
	return (tmp->pw_name);
}

char		*get_group(gid_t gid)
{
	struct group *tmp;

	if (!(tmp = getgrgid(gid)))
		return (NULL);
	return (tmp->gr_name);
}

void	print_time(time_t *timer)
{
	char *cctime = ctime(timer);
	char month[4];
	char day[3];
	char hour[3];
	char min[3];
	char year[5];

	int i = -1;
	while (++i < 3)
		month[i] = cctime[4 + i];
	month[i] = '\0';
	i = -1;
	while (++i < 2)
		day[i] = cctime[8 + i];
	day[i] = '\0';
	i = -1;
	while (++i < 2)
		hour[i] = cctime[11 + i];
	hour[i] = '\0';
	i = -1;
	while (++i < 2)
		min[i] = cctime[14 + i];
	min[i] = '\0';
	i = -1;
	while (++i < 4)
		year[i] = cctime[20 + i];
	year[i] = '\0';

	if (*timer < (time(NULL) - 15778800))
		ft_printf("%s %s %5s", month, day, year);
	else
		ft_printf("%s %s %s:%s", month, day, hour, min);
}


void		print_long_format(t_lsfile *file, t_ftlsenv *env)
{
	char	*mode;
	char	*link;
	char	*owner;
	char	*group;

	// malloc a proteger
	link = ft_strnew(file->stat_infos.st_size);
	mode = get_mode(file->stat_infos.st_mode);
	// owner
	if (!(owner = ft_strdup(get_owner(file->stat_infos.st_uid))))
		owner = ft_itoa(file->stat_infos.st_uid);
	// group
	if (!(group= ft_strdup(get_group(file->stat_infos.st_gid))))
		group = ft_itoa(file->stat_infos.st_gid);
	// affichage
	ft_printf("%c%s  %*d %-*s  %-*s  %*lld ",
			get_type(file->stat_infos.st_mode),
			mode,
			env->len_max_links,
			file->stat_infos.st_nlink,
			env->len_max_owner,
			owner,
			env->len_max_group,
			group,
			env->len_max_size,
			file->stat_infos.st_size
		);
	print_time(&file->stat_infos.st_mtimespec.tv_sec);
	ft_printf(" %s", file->name);
	if (get_type(file->stat_infos.st_mode) == 'l')
	{
		readlink(file->path, link, file->stat_infos.st_size + 1);
		ft_printf(" -> %s\n", link);
	}
	else
		ft_printf("\n");
	ft_strdel(&owner);
	ft_strdel(&group);
	ft_strdel(&mode);
	ft_strdel(&link);
}

void		ls_printer(void *tree, t_ftlsenv *env)
{
	if (env->options.l)
		print_long_format((((t_lsfile *)((t_btree *)(tree))->data)), env);
	else
		ft_printf("%s\n", (((t_lsfile *)((t_btree *)(tree))->data))->name);
}
