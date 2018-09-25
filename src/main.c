/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 16:54:10 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/24 18:14:12 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Count and set the number of files and dir in the "environment" struct
*/

static void		set_nb_rep_files(void *tree, t_ftlsenv *env)
{
	if (((((t_lsfile *)((t_btree *)(tree))->data))->st.st_mode & S_IFMT)
			== S_IFDIR)
		env->nb_rep++;
	else
		env->nb_files++;
}

/*
**	Initialisation of the "environment" struct
*/

static void    init_env(t_ftlsenv *env)
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

/*
**	The main function
**
**	params: ac -> number of arguments
** 			av -> arguments
**	return: EXIT_FAILURE if failed or EXIT_SUCCESS
**
**	Description:
**
**	- Initialisation of the "environment" struct with init_env()
**	- Parsing the arguments with ls_parser() for catch the options and put the
**	files/dir arguments on the args tree. Return EXIT_FAILURE if failed
**	- If the tree args is NULL, there is no files/dir in arguments
**		- call ft_ls() with the current path directly
**	- Or else, there is files/dir in arguments
**		- Calc the number of files and directories for final formatting by
**		applying set_nb_rep_files() on all the nodes in the args tree
**		- Print all the files first
**		- Then, print all the directories
**	- Free all the nodes and the args tree before finishing with del_file()
**	- Return EXIT_SUCCESS
*/

int     main(int ac, char **av)
{
	t_ftlsenv   env;
	t_btree     *args;

	(void)ac;
	args = NULL;
	init_env(&env);
	if (!ls_parser(av, &env, &args))
		return (EXIT_FAILURE);
	if (args == NULL)
		ft_ls(".", &env);
	else
	{
		ft_btree_apply_infix_forls(args, &env, set_nb_rep_files);
		ft_btree_apply_infix_forls(args, &env, print_files_args);
		ft_btree_apply_infix_forls(args, &env, print_dir_args);
	}
	ft_btree_del(args, del_file);
	return (EXIT_SUCCESS);
}
