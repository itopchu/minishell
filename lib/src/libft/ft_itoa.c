/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 17:00:51 by itopchu       #+#    #+#                 */
/*   Updated: 2022/10/08 17:00:51 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

#include <stdlib.h>

static size_t	ft_nbrlen(long nbr, int base)
{
	size_t	cnt;

	cnt = 0;
	if (! nbr)
		cnt++;
	while (nbr)
	{
		nbr /= base;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	char	*str_nbr;
	long	l_n;
	size_t	n_digits;

	l_n = (long) n;
	if (n < 0)
		l_n *= -1;
	n_digits = ft_nbrlen(l_n, 10) + (n < 0);
	str_nbr = ft_calloc(n_digits + 1, sizeof(char));
	if (str_nbr)
	{
		n_digits--;
		while (l_n)
		{
			str_nbr[n_digits--] = l_n % 10 + '0';
			l_n /= 10;
		}
		if (n < 0)
			str_nbr[n_digits] = '-';
		else if (n == 0)
			str_nbr[n_digits] = '0';
	}
	return (str_nbr);
}
