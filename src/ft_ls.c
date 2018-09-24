/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:13:54 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/24 14:18:39 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;
	// Path complet
	if (parent[ft_strlen(parent) - 1] == '/')
		tmp = ft_strdup(parent);
	else
		tmp = ft_strjoin(parent, "/");
	result = ft_strjoin(tmp, name);
	ft_strdel(&tmp);
	return (result);
}

static void	print_recursif(void *tree, t_ftlsenv *env)
{
	char *n;

	n = (((t_lsfile *)((t_btree *)(tree))->data))->name;
	if ((((((t_lsfile *)((t_btree *)(tree))->data))->stat_infos.st_mode & S_IFMT) == S_IFDIR) &&
			(ft_strcmp(n, ".") != 0 && ft_strcmp(n, "..")) )
	{
	// Print du nom
		ft_printf("\n%s:\n", (((t_lsfile *)((t_btree *)(tree))->data))->path);
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
	int				total;

	tree = NULL;
	total = 0;
	// remise a zero
	env->len_max_links = 0;
	env->len_max_size = 0;
	env->len_max_group = 0;
	env->len_max_owner = 0;
	if ((lstat(path, &file)) < 0)
	{
		ft_printf("ft_ls: %s: %s\n", path, strerror(errno));
		return (0);
	}
	// Si c'est un dossier
	if ((file.st_mode & S_IFMT) == S_IFDIR)
	{
		// Ouverture du dossier
		if (!(dirp = opendir(path)))
		{
			ft_printf("ft_ls: %s: %s\n", path, strerror(errno));
			return(0);
		}
		// Boucle sur le contenu du dossier
		while ((dir = readdir(dirp)) != NULL)
		{
			// Recuperation du path complet
			new_path = get_complete_path(path, dir->d_name);
			// Stat du fichier
			if ((lstat(new_path, &file)) < 0)
			{
				ft_printf("ft_ls: %s: %s\n", path, strerror(errno));
				continue;
			}
			// Ajout de la taille au total
			total += file.st_blocks;
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
		if (env->options.l)
			ft_printf("total %d\n", total);
			ft_btree_apply_infix_forls(tree, env, ls_printer);
		if (env->options.R)
		{
			ft_btree_apply_infix_forls(tree, env, print_recursif);
		}
		// Free de l'arbre
		ft_btree_del(tree, del_file);
		closedir(dirp);
	}
	// Si c'est pas un dossier
	else
	{
		// Affichage du fichier
		//ft_btree_apply_infix_forls(tree, env, ls_printer);
		create_tree(&tree, create_file(path, path, file), env);
		if (env->options.l)
			print_long_format((((t_lsfile *)((t_btree *)(tree))->data)), env);
		else
			ft_printf("%s\n", path);
		ft_btree_del(tree, del_file);
	}
	return (0);
}
