/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 01:05:29 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/24 16:53:33 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Check if the option is valid, return TRUE or FALSE
*/

static int     is_valid_option(char op)
{
    if (op == 'l' || op == 'a' || op == 'R' || op == 'r' || op == 't')
        return (TRUE);
    return (FALSE);
}

/*
**	Set the good option in the env struct. Check the options recursively
**	- If an option is not valid (check with is_valid_option()), print the error
*	and exit the program with EXIT_FAILURE;
*/

static void    set_options(char *ops, t_ftlsenv *env, int pos)
{
	if (ops[pos] == '\0')
		return;
	if (!is_valid_option(ops[pos]))
	{
		ft_printf("ft_ls: illegal option -- %c\nusage: ft_ls [-%s] [file ...]\n"
			, ops[pos], OPTS);
		exit(EXIT_FAILURE);
	}
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

/*
**	The parser
**
**	params: av -> arguments
**			env -> "environment" struct
**			args -> A pointer to the tree of the arguments in the main()
**	return: FALSE if failed or TRUE
**
**	Description:
**
**	- For each argument in av
**		- If the argument is a potential option
**			- Call set_options for catch it and set in env
**		- Or else, the argument is probably a file/dir
**			- Get the informations about the file with lstat and manage the
**			error if it happens. If its the last argument, return FALSE, else
**			continue
**			- Create the node for the file in the tree args
**	- Return TRUE
*/

int			ls_parser(char **av, t_ftlsenv *env, t_btree **args)
{
	int				i;
	struct stat		file;

	i = 0;
	while (av[++i])
	{
		if (((av[i][0] == '-') && (av[i][1] != '\0')) && *args == NULL)
			set_options(av[i], env, 1);
		else
		{
			if ((lstat(av[i], &file)) < 0)
			{
				ft_printf("ft_ls: %s: %s\n", av[i], strerror(errno));
				if (av[i + 1] == '\0')
					return (FALSE);
				continue;
			}
			create_tree(args, create_file(av[i], av[i], file), env);
		}
	}
	return (TRUE);
}
