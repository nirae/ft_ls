/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_main_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 00:26:36 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/28 17:44:24 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Function for printing the files in the main and call ft_ls()
*/

void	print_files_args(void *tree, t_ftlsenv *env)
{
	if (((((t_lsfile *)((t_btree *)(tree))->data))->st.st_mode & S_IFMT)
		!= S_IFDIR)
		ft_ls((((t_lsfile *)((t_btree *)(tree))->data))->name, env);
}

/*
**	Function for printing the directories in the main and call ft_ls()
*/

void	print_dir_args(void *tree, t_ftlsenv *env)
{
	if (((((t_lsfile *)((t_btree *)(tree))->data))->st.st_mode & S_IFMT)
		== S_IFDIR)
	{
		if (((t_btree *)(tree))->parent != NULL || env->nb_files)
			ft_printf("\n");
		if (env->nb_rep > 1 || env->nb_files)
			ft_printf("%s:\n", (((t_lsfile *)((t_btree *)(tree))->data))->name);
		ft_ls((((t_lsfile *)((t_btree *)(tree))->data))->name, env);
	}
}
