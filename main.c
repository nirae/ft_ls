/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 16:54:10 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/22 03:52:04 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <errno.h>
/////////////////////////////////////////////////////////
//////////              DEBUG           ////////////////
////////////////////////////////////////////////////////

void        print_tree(void *tree)
{
	if (((t_btree *)(tree))->parent != NULL)
	{
        printf("(%s) -> (%s)\n",
        	(((t_lsfile *)((t_btree *)(tree))->parent->data))->name,
         	(((t_lsfile *)((t_btree *)(tree))->data))->name);
	}
    else
    {
    	printf("(%s)\n",
            (((t_lsfile *)((t_btree *)(tree))->data))->name);
    }
  }

void        print(void *tree)
{
	printf("%s, %s\n", (((t_lsfile *)((t_btree *)(tree))->data))->name, (((t_lsfile *)((t_btree *)(tree))->data))->path);
}
//////////////////////////////////////////////////////////////

void    init_env(t_ftlsenv *env)
{
    env->options.l = FALSE;
    env->options.a = FALSE;
    env->options.R = FALSE;
    env->options.r = FALSE;
    env->options.t = FALSE;
}

char	*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	// Path complet
	if (parent[ft_strlen(parent) - 1] == '/')
		tmp = ft_strdup(parent);
	else
		tmp = ft_strjoin(parent, "/");
	return (ft_strjoin(tmp, name));
}

int		ft_ls(char *path, t_ftlsenv *env);

void	print_recursif(void *tree, t_ftlsenv *env)
{
	if (((((t_lsfile *)((t_btree *)(tree))->data))->stat_infos.st_mode & S_IFMT) == S_IFDIR)
	{
	// Print du nom
		ft_printf("%s:\n", (((t_lsfile *)((t_btree *)(tree))->data))->path);
		ft_ls((((t_lsfile *)((t_btree *)(tree))->data))->path, env);
		//ft_printf("\n");
	}
}

int		ft_ls(char *path, t_ftlsenv *env)
{
	t_btree			*tree;
	struct stat		file;
	DIR				*dirp;
	struct dirent	*dir;
	char			*new_path;

	tree = NULL;
	if ((lstat(path, &file)) < 0)
	{
    	ft_printf("erreur de lstat\n");
		// GERER L'ERREUR;
		exit(0);
	}
	// SI c'est un dossier
	if ((file.st_mode & S_IFMT) == S_IFDIR)
	{
		// Ouverture du dossier
		if (!(dirp = opendir(path)))
		{
			ft_printf("le dossier n'a pas pu etre ouvert\n");
			// GERER L'ERREUR
			exit(0);
		}
		// Boucle sur le contenu du dossier
		while ((dir = readdir(dirp)) != NULL)
		{
			// Path complet
			new_path = get_complete_path(path, dir->d_name);
			// Stat du fichier
			if ((lstat(new_path, &file)) < 0)
			{
				ft_printf("erreur de lstat %d\n", errno);
				// GERER L'ERREUR
				exit(0);
			}
			// Creation du noeud, gestion du flag -a
			if (env->options.a || dir->d_name[0] != '.')
				create_tree(&tree, create_file(dir->d_name, new_path, file), env);
			ft_strdel(&new_path);
		}
		// DEBUG
		/*ft_printf("ARBRE : \n");
		ft_btree_apply_prefix(tree, &print_tree);
		ft_printf("\n\n\n");*/
		// Affichage
		ft_btree_apply_infix(tree, print);
		ft_printf("\n");
		if (env->options.R)
			ft_btree_apply_infix_forls(tree, env, print_recursif);
		// FREE L'ARBRE
		closedir(dirp);
	}
	// Si c'est pas un dossier
	else
	{
		// Affichage du fichier
		ft_printf("%s\n", path);
	}
	return (0);
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
	// Print du nom
		ft_printf("%s:\n", (((t_lsfile *)((t_btree *)(tree))->data))->name);
		ft_ls((((t_lsfile *)((t_btree *)(tree))->data))->name, env);
		ft_printf("\n");
	}
}

int     main(int ac, char **av)
{
	t_ftlsenv   env;
	t_btree     *args;
	// Initialisations
	args = NULL;
	init_env(&env);
	// Si arguments
	if (ac > 1)
	{
		// Parsing
		ls_parser(av, &env, &args);
		// Si pas d'arbre = Pas de fichiers en arguments
		if (args == NULL)
			ft_ls(".", &env);
		// Sinon affichage des fichiers arguments
		else
		{
			// print les fichiers
			ft_btree_apply_infix_forls(args, &env, print_fichiers);
			ft_printf("\n");
			// print les dossier
			ft_btree_apply_infix_forls(args, &env, print_dossiers);
		}
	}
	// Si pas d'arguments
	else
	{
		ft_ls(".", &env);
	}
	return (0);
}
