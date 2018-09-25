/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 01:31:48 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 00:15:30 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Create and return a t_lsfile struct setted or stop the program if malloc
**	failed
*/

t_lsfile	*create_file(char *name, char *path, struct stat st)
{
	t_lsfile *file;

	if (!(file = ft_memalloc(sizeof(t_lsfile))))
		err_malloc();
	file->st = st;
	if (!(file->name = ft_strdup(name)))
		err_malloc();
	if (!(file->path = ft_strdup(path)))
		err_malloc();
	return (file);
}

/*
**	Free a t_lsfile struct
*/

void	del_file(void *data)
{
	ft_strdel(&((t_lsfile *)(data))->name);
	ft_strdel(&((t_lsfile *)(data))->path);
	ft_memdel(&data);
}

/*
**	Apply a function on each node. A copy of ft_btree_apply_infix from libft but
**	adapted for this project
*/

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

/*
**	Apply a function on each node. A copy of ft_btree_apply_rev_infix from libft
**	but adapted for this project
*/

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

/*
**	Create a node in the tree passed in arguments
**	And set the len_max of some informations for the padding in the printing
*/

void		create_tree(t_btree **tree, t_lsfile *file, t_ftlsenv *env)
{
	int		len;

	len = ft_count(file->st.st_nlink) + 1;
	if (len > env->len_max_links)
		env->len_max_links = len;
	len = ft_count(file->st.st_size) + 1;
	if (len > env->len_max_size)
		env->len_max_size = len;
	len = ft_strlen(get_owner(file->st.st_uid));
	if (len > env->len_max_owner)
		env->len_max_owner = len;
	len = ft_strlen(get_group(file->st.st_gid));
	if (len > env->len_max_group)
		env->len_max_group = len;
	if (*tree == NULL)
		*tree = ft_btree_create_node(file);
	else
		ft_btree_insert_data(tree, NULL, file, get_sort_func(env->options));
}
