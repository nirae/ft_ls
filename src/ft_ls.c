/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:13:54 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 20:27:20 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Reset the len max variables in the "environment" struct
*/

static void	reset_len_max(t_ftlsenv *env)
{
	env->len_max_links = 0;
	env->len_max_size = 0;
	env->len_max_group = 0;
	env->len_max_owner = 0;
}

/*
**	Return the complete path of a file name or exit if malloc failed
*/

static char	*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;

	if (parent[ft_strlen(parent) - 1] == '/')
	{
		if (!(tmp = ft_strdup(parent)))
			err_malloc();
	}
	else
	{
		if (!(tmp = ft_strjoin(parent, "/")))
			err_malloc();
	}
	if (!(result = ft_strjoin(tmp, name)))
		err_malloc();
	ft_strdel(&tmp);
	return (result);
}

/*
**	Managing the case of a directory
**
**	params: path -> the path of the directory
** 			env -> the "environment" struct
**			tree -> the tree need to be filled
**			total -> the total size in blocks, for print in long format
**	return: FALSE if failed or TRUE
**
**	Description:
**
**	- Open the directory with opendir(), return FALSE if failed due to
**	catch_error()
**	- Read the content of the directory by each element in a loop with readdir()
**		- Get the complete path with get_complete_path() for no errors with
**		lstat. The malloc is protected with an exit() in the get_complete_path
**		function
**		- Get the struct stat of the file with lstat() and catch the error if
**		happens with catch_error()
**		- Managing the "-a" option and create the node represent the file in the
**		tree with create_tree() and create_file(). And increase the total size
**		- Free the variable new_path with ft_strdel()
**	- Close the directory with closedir()
**	- Return TRUE
*/

static int	manage_rep(char *path, t_ftlsenv *env, t_btree **tree, int *total)
{
	struct stat		file;
	DIR				*dirp;
	struct dirent	*dir;
	char			*new_path;

	if (!(dirp = opendir(path)))
		return (catch_error(path));
	while ((dir = readdir(dirp)) != NULL)
	{
		new_path = get_complete_path(path, dir->d_name);
		if ((lstat(new_path, &file)) < 0)
		{
			catch_error(path);
			continue;
		}
		if ((env->options.a || env->options.f) || dir->d_name[0] != '.')
		{
			*total += file.st_blocks;
			create_tree(tree, create_file(dir->d_name, new_path, file), env);
		}
		ft_strdel(&new_path);
	}
	closedir(dirp);
	return (TRUE);
}

/*
**	The principal function, ft_ls
**
**	params: path -> the path of the file who want to be printed
** 			env -> the "environment" struct
**	return: FALSE if failed or TRUE
**
**	Description:
**
**	- Initialisation an reset the env struct with reset_len_max()
**	- Get the struct stat of the path with lstat(). Catch the error if
**	happens with catch_error() and stop the function with FALSE
**	- If the path is a directory
**		- Call the function manage_rep() for fill the tree with the content and
**		stop the function with FALSE if failed
**		- Print the tree in terms of the options. If there is the long format
**		option, print the total blocks size and apply the function ls_printer()
**		on each nodes.
**		- If there is the "-R" option, apply the function print_recursive() on
**		each nodes, who call a new time the ft_ls() if it's a directory, etc ...
**	- Or else, the path is a file
**		- Create a node with create_tree() and create_file() and print it with
**		ls_printer()
**	- Free the tree by apply on each node the function del_file() with
**	ft_btree_del()
**	- Return TRUE
*/

int			ft_ls(char *path, t_ftlsenv *env)
{
	t_btree			*tree;
	struct stat		file;
	int				total;

	tree = NULL;
	total = 0;
	reset_len_max(env);
	if ((lstat(path, &file)) < 0)
		return (catch_error(path));
	if ((file.st_mode & S_IFMT) == S_IFDIR)
	{
		if (!manage_rep(path, env, &tree, &total))
			return (FALSE);
		env->options.l ? ft_printf("total %d\n", total) : 0;
		ft_btree_apply_infix_forls(tree, env, ls_printer);
		if (env->options.big_r)
			ft_btree_apply_infix_forls(tree, env, print_recursive);
	}
	else
	{
		create_tree(&tree, create_file(path, path, file), env);
		ft_btree_apply_infix_forls(tree, env, ls_printer);
	}
	ft_btree_del(tree, del_file);
	return (TRUE);
}
