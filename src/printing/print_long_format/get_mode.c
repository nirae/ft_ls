/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 00:37:43 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 00:39:10 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Return a string with the mode/rights of the file
*/

char		*get_mode(mode_t mode)
{
	char	model[] = "rwxrwxrwx";
	char	*result;
	int		i = -1;

	if (!(result = ft_strnew(sizeof(char) * 9)))
		err_malloc();
	while (++i < 9)
	{
		if (mode & (1 << (8 - i)))
			result[i] = model[i];
		else
			result[i] = '-';
	}
	return (result);
}
