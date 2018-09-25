/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 18:02:11 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/24 18:06:51 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Sort function for the basic sort. Use ft_strcmp()
*/

int		basic_sort(void *a, void *b)
{
	const char *na;
	const char *nb;

	na = ((t_lsfile *)(a))->name;
	nb = ((t_lsfile *)(b))->name;
	return (ft_strcmp(na, nb));
}

int		basic_sort_rev(void *a, void *b)
{
	const char *na;
	const char *nb;

	na = ((t_lsfile *)(a))->name;
	nb = ((t_lsfile *)(b))->name;
	return (ft_strcmp(nb, na));
}
