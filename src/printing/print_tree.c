/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 00:16:12 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 18:07:10 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	A printing function for debug and print all the tree
**	Usage : ft_btree_apply_infix(void *tree, print_tree);
*/

void	print_tree(void *tree)
{
	if (((t_btree *)(tree))->parent != NULL)
	{
		ft_printf("(%s) -> (%s)\n",
			(((t_lsfile *)((t_btree *)(tree))->parent->data))->name,
			(((t_lsfile *)((t_btree *)(tree))->data))->name);
	}
	else
	{
		ft_printf("(%s)\n",
			(((t_lsfile *)((t_btree *)(tree))->data))->name);
	}
}
