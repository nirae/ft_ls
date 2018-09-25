/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atime_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 18:54:16 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 20:25:07 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Sort by the last access time, using sec
**	For option "-u"
**	If both arguments are equals, using atime_nano_sort()
*/

int		atime_sort(void *a, void *b)
{
	time_t na;
	time_t nb;

	na = ((t_lsfile *)(a))->st.st_atimespec.tv_sec;
	nb = ((t_lsfile *)(b))->st.st_atimespec.tv_sec;
	if (na == nb)
		return (basic_sort(a, b));
	else if (na <= nb)
		return (1);
	return (-1);
}

int		atime_sort_rev(void *a, void *b)
{
	time_t na;
	time_t nb;

	na = ((t_lsfile *)(a))->st.st_atimespec.tv_sec;
	nb = ((t_lsfile *)(b))->st.st_atimespec.tv_sec;
	if (na == nb)
		return (basic_sort_rev(a, b));
	else if (na > nb)
		return (1);
	return (-1);
}
