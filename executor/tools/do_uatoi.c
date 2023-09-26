/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_unsigned.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 18:58:02 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/18 18:58:02 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_uatoi(char *s)
{
	long	ret;
	int		i;

	if (!s)
		return (0);
	i = -1;
	ret = 0;
	while (ft_isdigit(s[++i]))
	{
		ret = (ret * 10) + s[i] - '0';
		if (ret >= INT_MAX)
			return (0);
	}
	return (ret);
}
