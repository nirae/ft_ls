/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtime_nano_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 18:07:29 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/24 18:10:32 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Sort by the last modification time, using nanosec
**	For option "-t"
*/

int		mtime_nano_sort(void *a, void *b)
{
	long int na;
	long int nb;

	na = ((t_lsfile *)(a))->st.st_mtimespec.tv_nsec;
	nb = ((t_lsfile *)(b))->st.st_mtimespec.tv_nsec;
	if (na <= nb)
		return (1);
	return (-1);
}

int		mtime_nano_sort_rev(void *a, void *b)
{
	long int na;
	long int nb;

	na = ((t_lsfile *)(a))->st.st_mtimespec.tv_nsec;
	nb = ((t_lsfile *)(b))->st.st_mtimespec.tv_nsec;
	if (na > nb)
		return (1);
	return (-1);
}
