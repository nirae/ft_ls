/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 01:05:29 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/24 01:05:59 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int     err_illegal_option(char op)
{
	ft_printf("Illegal option -%c\n", op);
	exit(0);
}

static int     is_valid_option(char op)
{
    if (op == 'l' || op == 'a' || op == 'R' || op == 'r' || op == 't')
        return (TRUE);
    return (FALSE);
}

static void    set_options(char *ops, t_ftlsenv *env, int pos)
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

int			ls_parser(char **av, t_ftlsenv *env, t_btree **args)
{
	int				i;
	struct stat		file;
	// Boucle sur les arguments
	i = 0;
	while (av[++i])
	{
		// Si l'argument est une option
		if (((av[i][0] == '-') && (av[i][1] != '\0')) && *args == NULL)
		{
			// Recupere les options
			set_options(av[i], env, 1);
			//// DEBUG ////
			//ft_printf("options: l:%d, a:%d, R:%d, r:%d, t:%d\n", env->options.l, env->options.a, env->options.R, env->options.r, env->options.t);
		}
		// Sinon, l'argument est un nom de fichier potentiel
		else
		{
			// Recupere les infos avec lstat et test du fichier
			if ((lstat(av[i], &file)) < 0)
			{
				ft_printf("ft_ls: %s: %s\n", av[i], strerror(errno));
				if (av[i + 1] == '\0')
					return (FALSE);
				continue;
			}
			// Creation de l'arbre des arguments
			create_tree(args, create_file(av[i], av[i], file), env);

		}
	}
	return (TRUE);
}
