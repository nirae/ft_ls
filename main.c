/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 16:54:10 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/19 21:05:09 by ndubouil         ###   ########.fr       */
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
	printf("%s\n", (((t_lsfile *)((t_btree *)(tree))->data))->name);
}
//////////////////////////////////////////////////////////////

int			tri(void *a, void *b)
{
	const char *na;
	const char *nb;

	na = ((t_lsfile *)(a))->name;
	nb = ((t_lsfile *)(b))->name;
	return (strcmp(na, nb));
}

int     err_illegal_option(char op)
{
     ft_printf("Illegal option -%c\n", op);
      exit(0);
 }

int     is_valid_option(char op)
{
    if (op == 'l' || op == 'a' || op == 'R' || op == 'r' || op == 't')
        return (TRUE);
    return (FALSE);
}

void    init_env(t_ftlsenv *env)
{
    env->options.l = FALSE;
    env->options.a = FALSE;
    env->options.R = FALSE;
    env->options.r = FALSE;
    env->options.t = FALSE;
}


void    set_options(char *ops, t_ftlsenv *env, int pos)
{
	if (ops[pos] == '\0')
		return;
	if (!is_valid_option(ops[pos]))
 		err_illegal_option(ops[pos]);
	if (ops[pos] == 'l')
		env->options.l = TRUE;
	else if (ops[pos] == 'a')
		env->options.a = TRUE;
	else if (ops[pos] == 'R')
		env->options.R = TRUE;
	else if (ops[pos] == 'r')
		env->options.r = TRUE;
	else if (ops[pos] == 't')
		env->options.t = TRUE;
	set_options(ops, env, (pos + 1));
}

t_lsfile	*create_file(char *name, struct stat st)
{
	t_lsfile *file;

	file = ft_memalloc(sizeof(t_lsfile));
	file->stat_infos = st;
	file->name = ft_strdup(name);
	return (file);
}

// FT LS
int		ft_ls(char *path)
{
	t_btree			*tree;
	struct stat		file;
	DIR				*dirp;
	struct dirent	*dir;
	char			*tmp;
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
			if (path[ft_strlen(path)] == '/')
				tmp = ft_strdup(path);
			else
				tmp = ft_strjoin(path, "/");
			new_path = ft_strjoin(tmp, dir->d_name);
			ft_strdel(&tmp);
			// Stat du fichier
			if ((lstat(new_path, &file)) < 0)
			{
				ft_printf("erreur de lstat %d\n", errno);
				// GERER L'ERREUR
				exit(0);
			}
			// pas option -a
			if (dir->d_name[0] != '.')
			{
				// Si l'arbre existe pas on le fait
				if (tree == NULL)
					tree = ft_btree_create_node(create_file(dir->d_name, file));
				// Si l'arbre existe on insert
				else
					ft_btree_insert_data(&tree, NULL, create_file(dir->d_name, file), tri);
			}
			ft_strdel(&new_path);
		}
		// DEBUG
		/*ft_printf("ARBRE : \n");
		ft_btree_apply_prefix(tree, &print_tree);
		ft_printf("\n\n\n");*/
		//
		ft_btree_apply_infix(tree, &print);
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

void    print_fichiers(void *tree)
{
	// Si c'est pas un dossier
	if (((((t_lsfile *)((t_btree *)(tree))->data))->stat_infos.st_mode & S_IFMT) != S_IFDIR)
		ft_ls((((t_lsfile *)((t_btree *)(tree))->data))->name);
}

void	print_dossiers(void *tree)
{
	if (((((t_lsfile *)((t_btree *)(tree))->data))->stat_infos.st_mode & S_IFMT) == S_IFDIR)
	{
	// Print du nom
		ft_printf("%s:\n", (((t_lsfile *)((t_btree *)(tree))->data))->name);
		ft_ls((((t_lsfile *)((t_btree *)(tree))->data))->name);
		ft_printf("\n");
	}
}

int     main(int ac, char **av)
{
	t_ftlsenv   env;
	int         i;
	t_btree     *args;
	struct stat file;

	// Initialisations
	args = NULL;
	init_env(&env);
	i = 0;
	// Si arguments
	if (ac > 1)
	{
		// Boucle sur les arguments
		while (av[++i])
		{
			// Si l'argument est une option
			if (((av[i][0] == '-') && (av[i][1] != '\0')) && args == NULL)
			{
				// Recupere les options
				set_options(av[i], &env, 1);
				//// DEBUG ////
				ft_printf("options: l:%d, a:%d, R:%d, r:%d, t:%d\n", env.options.l, env.options.a, env.options.R, env.options.r, env.options.t);
			}
			// Sinon, l'argument est un nom de fichier potentiel
			else
			{
				// Recupere les infos avec lstat et test du fichier
				if ((lstat(av[i], &file)) < 0)
				{
					ft_printf("erreur de lstat\n");
					// GERER L'ERREUR
					exit(0);
				}
				// Creation de l'arbre des arguments
				if (args == NULL)
					args = ft_btree_create_node(create_file(av[i], file));
				else
					ft_btree_insert_data(&args, NULL, create_file(av[i], file), tri);
			}
		}
		// Si pas d'arbre = Pas de fichiers en arguments
		if (args == NULL)
			ft_ls(".");
		// Sinon affichage des fichiers arguments
		else
		{
			// print les fichiers
			ft_btree_apply_infix(args, print_fichiers);
			ft_printf("\n");
			// print les dossier
			ft_btree_apply_infix(args, print_dossiers);
		}
	}
	// Si pas d'arguments
	else
	{
		ft_ls("."/*, &env*/);
	}
	return (0);
}
