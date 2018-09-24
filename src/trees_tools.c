/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 01:31:48 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/23 23:30:56 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lsfile	*create_file(char *name, char *path, struct stat st)
{
	t_lsfile *file;

	file = ft_memalloc(sizeof(t_lsfile));
	file->stat_infos = st;
	file->name = ft_strdup(name);
	file->path = ft_strdup(path);
	return (file);
}

void	del_file(void *data)
{
	ft_strdel(&((t_lsfile *)(data))->name);
	ft_strdel(&((t_lsfile *)(data))->path);
	ft_memdel(&data);
}

void		ft_btree_apply_infix_forls(t_btree *tree, t_ftlsenv *env,
				void (*func)(void *, t_ftlsenv *env))
{
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		ft_btree_apply_infix_forls(tree->left, env, func);
	(*func)((void *)tree, env);
	if (tree->right != NULL)
		ft_btree_apply_infix_forls(tree->right, env, func);
}

void		ft_btree_apply_rev_infix_forls(t_btree *tree, t_ftlsenv *env,
				void (*func)(void *, t_ftlsenv *env))
{
	if (tree == NULL)
		return;
	if (tree->right != NULL)
		ft_btree_apply_infix_forls(tree->right, env, func);
	(*func)((void *)tree, env);
	if (tree->left != NULL)
		ft_btree_apply_infix_forls(tree->left, env, func);
}

void		create_tree(t_btree **tree, t_lsfile *file, t_ftlsenv *env)
{
	int		len;
	// Set de la longueur du nombre de liens, pour l'affichage
	len = ft_count(file->stat_infos.st_nlink) + 1;
	if (len > env->len_max_links)
		env->len_max_links = len;
	// Set de la longueur de la taille, pour l'Affichage
	len = ft_count(file->stat_infos.st_size) + 1;
	if (len > env->len_max_size)
		env->len_max_size = len;
	// Set de la longueur du nom de l'owner pour l'affichage
	len = ft_strlen(get_owner(file->stat_infos.st_uid));
	if (len > env->len_max_owner)
		env->len_max_owner = len;
	// Set de la longueur du nom de l'owner pour l'affichage
	len = ft_strlen(get_group(file->stat_infos.st_gid));
	if (len > env->len_max_group)
		env->len_max_group = len;
	// Si l'arbre existe pas on le fait
	if (*tree == NULL)
		*tree = ft_btree_create_node(file);
	// Si l'arbre existe on insert
	else
		ft_btree_insert_data(tree, NULL, file, get_sort_func(env->options));
}
