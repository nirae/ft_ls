/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 08:23:34 by ndubouil          #+#    #+#             */
/*   Updated: 2017/11/22 12:21:45 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int		i;

	i = 1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i - 1);
}

char		*ft_itoa(int n)
{
	int		isneg;
	int		len;
	int		i;
	char	*result;

	if (n < -2147483647)
		return (ft_strdup("-2147483648"));
	if ((isneg = !ft_ispositive(n)))
		n = -n;
	len = ft_count(n);
	if (!(result = ft_strnew(len + isneg + 1)))
		return (0);
	i = 0;
	while (i <= len)
	{
		result[i++] = (n % 10) + '0';
		n = n / 10;
	}
	if (isneg)
		result[i] = '-';
	return (ft_strrev(result));
}
