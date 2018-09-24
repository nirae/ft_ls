/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 00:43:02 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/24 01:54:34 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		basic_sort(void *a, void *b)
{
	const char *na;
	const char *nb;

	na = ((t_lsfile *)(a))->name;
	nb = ((t_lsfile *)(b))->name;
	return (ft_strcmp(na, nb));
}

static int		basic_sort_rev(void *a, void *b)
{
	const char *na;
	const char *nb;

	na = ((t_lsfile *)(a))->name;
	nb = ((t_lsfile *)(b))->name;
	return (ft_strcmp(nb, na));
}

static int		mtime_nano_sort(void *a, void *b)
{
	long int na;
	long int nb;

	na = ((t_lsfile *)(a))->stat_infos.st_mtimespec.tv_nsec;
	nb = ((t_lsfile *)(b))->stat_infos.st_mtimespec.tv_nsec;
	if (na <= nb)
		return (1);
	return (-1);
}

static int		mtime_nano_sort_rev(void *a, void *b)
{
	long int na;
	long int nb;

	na = ((t_lsfile *)(a))->stat_infos.st_mtimespec.tv_nsec;
	nb = ((t_lsfile *)(b))->stat_infos.st_mtimespec.tv_nsec;
	if (na > nb)
		return (1);
	return (-1);
}

static int		mtime_sort(void *a, void *b)
{
	time_t na;
	time_t nb;

	na = ((t_lsfile *)(a))->stat_infos.st_mtimespec.tv_sec;
	nb = ((t_lsfile *)(b))->stat_infos.st_mtimespec.tv_sec;
	if (na == nb)
		return (mtime_nano_sort(a, b));
	else if (na <= nb)
		return (1);
	return (-1);
}

static int		mtime_sort_rev(void *a, void *b)
{
	time_t na;
	time_t nb;

	na = ((t_lsfile *)(a))->stat_infos.st_mtimespec.tv_sec;
	nb = ((t_lsfile *)(b))->stat_infos.st_mtimespec.tv_sec;
	if (na == nb)
		return (mtime_nano_sort_rev(a, b));
	else if (na > nb)
		return (1);
	return (-1);
}

int				(*get_sort_func(t_options opt))(void *, void *)
{
	if (opt.t)
	{
		if (opt.r)
			return (mtime_sort_rev);
		else
			return (mtime_sort);
	}
	else
	{
		if (opt.r)
			return (basic_sort_rev);
		else
			return (basic_sort);
	}
}
