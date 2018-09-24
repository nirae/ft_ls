/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 16:54:10 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/24 14:20:47 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/////////////////////////////////////////////////////////
//////////              DEBUG           ////////////////
////////////////////////////////////////////////////////

void        print_tree(void *tree)
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
//////////////////////////////////////////////////////////////

void    init_env(t_ftlsenv *env)
{
    env->options.l = FALSE;
    env->options.a = FALSE;
    env->options.R = FALSE;
    env->options.r = FALSE;
    env->options.t = FALSE;
	env->tree = NULL;
	env->nb_rep = 0;
	env->nb_files = 0;
}

void    print_fichiers(void *tree, t_ftlsenv *env)
{
	// Si c'est pas un dossier
	if (((((t_lsfile *)((t_btree *)(tree))->data))->stat_infos.st_mode & S_IFMT) != S_IFDIR)
		ft_ls((((t_lsfile *)((t_btree *)(tree))->data))->name, env);
}

void	print_dossiers(void *tree, t_ftlsenv *env)
{
	if (((((t_lsfile *)((t_btree *)(tree))->data))->stat_infos.st_mode & S_IFMT) == S_IFDIR)
	{
		if (((t_btree *)(tree))->parent != NULL || env->nb_files)
			ft_printf("\n");
	// Print du nom
		if (env->nb_rep > 1)
			ft_printf("%s:\n", (((t_lsfile *)((t_btree *)(tree))->data))->name);
		ft_ls((((t_lsfile *)((t_btree *)(tree))->data))->name, env);
	}
}

void	set_nb_rep_files(void *tree, t_ftlsenv *env)
{
	if (((((t_lsfile *)((t_btree *)(tree))->data))->stat_infos.st_mode & S_IFMT) == S_IFDIR)
		env->nb_rep++;
	else
		env->nb_files++;
}

int     main(int ac, char **av)
{
	t_ftlsenv   env;
	t_btree     *args;
	// Initialisations
	(void)ac;
	args = NULL;
	init_env(&env);
		// Parsing
		if (!ls_parser(av, &env, &args))
			return (0);
		// Si pas d'arbre = Pas de fichiers en arguments
		if (args == NULL)
			ft_ls(".", &env);
		// Sinon affichage des fichiers arguments
		else
		{
			// Calcul du nombre d'arguments qui sont des dossiers et fichiers
			ft_btree_apply_infix_forls(args, &env, set_nb_rep_files);
			// print les fichiers d'abord
			ft_btree_apply_infix_forls(args, &env, print_fichiers);
			// puis print les dossier
			ft_btree_apply_infix_forls(args, &env, print_dossiers);
		}
		// Free de l'arbre
		ft_btree_del(args, del_file);
	return (0);
}
