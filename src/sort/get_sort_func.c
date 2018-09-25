/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sort_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 17:01:18 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 18:30:55 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Choose and return the good sort function
**
**	params: opt -> struct options
**
**	return: pointer on function like int func(void *, void *)
*/

t_func_ptr		get_sort_func(t_options opt)
{
	if (opt.t)
	{
		if (opt.r)
			return (mtime_sort_rev);
		else
			return (mtime_sort);
	}
	if (opt.f)
	{
		if (opt.f)
			return (f_sort_rev);
		else
			return (f_sort);
	}
	else
	{
		if (opt.r)
			return (basic_sort_rev);
		else
			return (basic_sort);
	}
}
