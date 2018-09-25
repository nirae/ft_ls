/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_recursive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 00:19:32 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 00:24:56 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Print for recursive "-R" option
**	If it's a directory, print the name: and using ft_ls() for recursivity
*/

void	print_recursive(void *tree, t_ftlsenv *env)
{
	char		*n;
	mode_t		mode;

	n = (((t_lsfile *)((t_btree *)(tree))->data))->name;
	mode = (((t_lsfile *)((t_btree *)(tree))->data))->st.st_mode;
	if (((mode & S_IFMT) == S_IFDIR)
		&& (ft_strcmp(n, ".") != 0 && ft_strcmp(n, "..")))
	{
	// Print du nom
		ft_printf("\n%s:\n", (((t_lsfile *)((t_btree *)(tree))->data))->path);
		ft_ls((((t_lsfile *)((t_btree *)(tree))->data))->path, env);
		//ft_printf("\n");
	}
}
