/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 00:46:20 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 18:06:02 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>

/*
**	Cut the month on the ctime and put it on the month arg
*/

static void		get_month(char *cctime, char month[4])
{
	int			i;

	i = -1;
	while (++i < 3)
		month[i] = cctime[4 + i];
	month[i] = '\0';
}

/*
**	Cut the day on the ctime and put it on the day arg
*/

static void		get_day(char *cctime, char day[3])
{
	int			i;

	i = -1;
	while (++i < 2)
		day[i] = cctime[8 + i];
	day[i] = '\0';
}

/*
**	Cut the hour on the ctime and put it on the hour arg
*/

static void		get_hour(char *cctime, char hour[3])
{
	int			i;

	i = -1;
	while (++i < 2)
		hour[i] = cctime[11 + i];
	hour[i] = '\0';
}

/*
**	Cut the min on the ctime and put it on the min arg
*/

static void		get_min(char *cctime, char min[3])
{
	int			i;

	i = -1;
	while (++i < 2)
		min[i] = cctime[14 + i];
	min[i] = '\0';
}

/*
**	Print the date of the file, cutting the ctime result for made my formatting
*/

void			print_time(time_t *timer)
{
	char		*cctime;
	t_date		date;
	int			i;

	cctime = ctime(timer);
	i = -1;
	get_month(cctime, date.month);
	get_day(cctime, date.day);
	get_hour(cctime, date.hour);
	get_min(cctime, date.min);
	while (++i < 4)
		date.year[i] = cctime[20 + i];
	date.year[i] = '\0';
	if (*timer < (time(NULL) - 15778800))
		ft_printf("%s %s %5s", date.month, date.day, date.year);
	else
		ft_printf("%s %s %s:%s", date.month, date.day, date.hour, date.min);
}
