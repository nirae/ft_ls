/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_printer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 00:31:33 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 00:32:35 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	The basic printer
**	Use the good function with the options
*/

void		ls_printer(void *tree, t_ftlsenv *env)
{
	if (env->options.l)
		print_long_format((((t_lsfile *)((t_btree *)(tree))->data)), env);
	else
		ft_printf("%s\n", (((t_lsfile *)((t_btree *)(tree))->data))->name);
}
