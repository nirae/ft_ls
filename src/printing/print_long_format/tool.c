/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 19:19:56 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/28 19:20:24 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Free the struct t_lformat
*/

void		del_tool(t_lformat *tool)
{
	ft_strdel(&tool->owner);
	ft_strdel(&tool->group);
	ft_strdel(&tool->mode);
	ft_strdel(&tool->link);
}

/*
**	Setting the struct t_lformat with the file informations
*/

void		set_tool(t_lformat *tool, t_lsfile *file)
{
	if (!(tool->link = ft_strnew(file->st.st_size)))
		err_malloc();
	if (!(tool->mode = get_mode(file->st.st_mode)))
		err_malloc();
	if (!(tool->owner = ft_strdup(get_owner(file->st.st_uid))))
		tool->owner = ft_itoa(file->st.st_uid);
	if (!(tool->group = ft_strdup(get_group(file->st.st_gid))))
		tool->group = ft_itoa(file->st.st_gid);
}
