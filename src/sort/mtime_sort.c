/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtime_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 18:10:56 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/24 18:13:00 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Sort by the last modification time, using sec
**	For option "-t"
**	If both arguments are equals, using mtime_nano_sort()
*/

int		mtime_sort(void *a, void *b)
{
	time_t na;
	time_t nb;

	na = ((t_lsfile *)(a))->st.st_mtimespec.tv_sec;
	nb = ((t_lsfile *)(b))->st.st_mtimespec.tv_sec;
	if (na == nb)
		return (mtime_nano_sort(a, b));
	else if (na <= nb)
		return (1);
	return (-1);
}

int		mtime_sort_rev(void *a, void *b)
{
	time_t na;
	time_t nb;

	na = ((t_lsfile *)(a))->st.st_mtimespec.tv_sec;
	nb = ((t_lsfile *)(b))->st.st_mtimespec.tv_sec;
	if (na == nb)
		return (mtime_nano_sort_rev(a, b));
	else if (na > nb)
		return (1);
	return (-1);
}
