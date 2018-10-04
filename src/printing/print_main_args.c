/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_main_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 00:26:36 by ndubouil          #+#    #+#             */
/*   Updated: 2018/10/04 19:30:30 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		iflinkisdir(t_lsfile *file, char **path, t_ftlsenv *env)
{
	struct stat	st;
	int			result;
	char		*tmp;

	result = FALSE;
	if (env->options.l)
		return (result);
	if (!(*path = ft_strnew(file->st.st_size)))
		err_malloc();
	readlink(file->name, *path, file->st.st_size);
	if (*path[0] != '/')
	{
		tmp = ft_strdup(*path);
		*path = ft_strjoin("/", *path);
		ft_strdel(&tmp);
	}
	if ((lstat(*path, &st)) >= 0)
	{
		if ((st.st_mode & S_IFMT) == S_IFDIR)
			result = TRUE;
	}
	return (result);
}

/*
**	Function for printing the files in the main and call ft_ls()
*/

void	print_files_args(void *tree, t_ftlsenv *env)
{
	t_lsfile	*file;
	int			linkisdir;
	char		*path;

	path = NULL;
	linkisdir = FALSE;
	file = ((t_lsfile *)((t_btree *)(tree))->data);
	if ((file->st.st_mode & S_IFMT) == S_IFLNK)
		linkisdir = iflinkisdir(file, &path, env);
	if (linkisdir)
	{
		(env->nb_files > 0) ? env->nb_files-- : 0;
		env->nb_rep++;
	}
	if (((file->st.st_mode & S_IFMT) != S_IFDIR) && !linkisdir)
		ft_ls(file->name, env);
	ft_strdel(&path);
}

/*
**	Function for printing the directories in the main and call ft_ls()
*/

void	print_dir_args(void *tree, t_ftlsenv *env)
{
	t_lsfile	*file;
	int			linkisdir;
	char		*path;

	path = NULL;
	linkisdir = FALSE;
	file = ((t_lsfile *)((t_btree *)(tree))->data);
	if ((file->st.st_mode & S_IFMT) == S_IFLNK)
		linkisdir = iflinkisdir(file, &path, env);
	if ((file->st.st_mode & S_IFMT) == S_IFDIR || linkisdir)
	{
		if ((((t_btree *)(tree))->parent != NULL && env->nb_rep > 1)
			|| env->nb_files > 0)
			ft_printf("\n");
		if (env->nb_rep > 1 || env->nb_files)
			ft_printf("%s:\n", file->name);
		(linkisdir) ? ft_ls(path, env) : ft_ls(file->name, env);
	}
	ft_strdel(&path);
}
