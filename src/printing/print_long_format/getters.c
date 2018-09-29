/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 00:39:48 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/28 19:48:59 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <pwd.h>
#include <grp.h>

/*
**	Return the good char for the type of the file
*/

char			get_type(mode_t mode)
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

static void		check_specials(mode_t mode, char *result)
{
	if ((mode & S_ISUID) && result[2] == 'x')
		result[2] = 's';
	else if (mode & S_ISUID)
		result[2] = 'S';
	if ((mode & S_ISGID) && result[5] == 'x')
		result[5] = 's';
	else if (mode & S_ISGID)
		result[5] = 'S';
	if ((mode & S_ISVTX) && result[8] == 'x')
		result[8] = 't';
	else if (mode & S_ISVTX)
		result[8] = 'T';
}

/*
**	Return a string with the mode/rights of the file
*/

char			*get_mode(mode_t mode)
{
	char	model[10];
	char	*result;
	int		i;

	ft_strcpy(model, "rwxrwxrwx");
	i = -1;
	if (!(result = ft_strnew(sizeof(char) * 9)))
		err_malloc();
	while (++i < 9)
	{
		if (mode & (1 << (8 - i)))
			result[i] = model[i];
		else
			result[i] = '-';
	}
	check_specials(mode, result);
	return (result);
}

/*
**	Return the name of the owner of the file
*/

char			*get_owner(uid_t uid)
{
	struct passwd *tmp;

	if (!(tmp = getpwuid(uid)))
		return (NULL);
	return (tmp->pw_name);
}

/*
**	Return the name of the group of the file
*/

char			*get_group(gid_t gid)
{
	struct group *tmp;

	if (!(tmp = getgrgid(gid)))
		return (NULL);
	return (tmp->gr_name);
}
