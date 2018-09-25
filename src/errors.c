/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 21:25:17 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/24 21:39:05 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		catch_error(char *path)
{
	ft_printf("ft_ls: %s: %s\n", path, strerror(errno));
	return (FALSE);
}

void	err_malloc(void)
{
	ft_printf("ft_ls: error: malloc failed");
	exit(EXIT_FAILURE);
}
