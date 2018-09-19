/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lli_itoa_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:30:02 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/26 22:00:27 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long long int n, int base)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

char		*ft_lli_itoa_base(long long int n, char *base_str)
{
	int		len;
	int		isneg;
	int		base;
	char	*result;

	base = ft_strlen(base_str);
	isneg = n < 0 ? 1 : 0;
	len = ft_count(n, base);
	if (!(result = ft_strnew(len + isneg)))
		return (NULL);
	result[0] = isneg ? '-' : '0';
	if (isneg)
		len++;
	while (n != 0)
	{
		if (n < 0)
			result[--len] = base_str[-1 * (n % base)];
		else
			result[--len] = base_str[n % base];
		n = n / base;
	}
	return (result);
}
