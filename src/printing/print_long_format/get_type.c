/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 00:35:04 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 00:37:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Return the good char for the type of the file
*/

char		get_type(mode_t mode)
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
