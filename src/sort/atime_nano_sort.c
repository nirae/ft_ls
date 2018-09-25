/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atime_nano_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 18:55:08 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 18:55:32 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Sort by the last modification time, using nanosec
**	For option "-t"
*/

int		atime_nano_sort(void *a, void *b)
{
	long int na;
	long int nb;

	na = ((t_lsfile *)(a))->st.st_atimespec.tv_nsec;
	nb = ((t_lsfile *)(b))->st.st_atimespec.tv_nsec;
	if (na <= nb)
		return (1);
	return (-1);
}

int		atime_nano_sort_rev(void *a, void *b)
{
	long int na;
	long int nb;

	na = ((t_lsfile *)(a))->st.st_atimespec.tv_nsec;
	nb = ((t_lsfile *)(b))->st.st_atimespec.tv_nsec;
	if (na > nb)
		return (1);
	return (-1);
}
