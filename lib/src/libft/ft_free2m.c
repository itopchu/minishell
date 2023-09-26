/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free2m.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/16 00:50:59 by itopchu       #+#    #+#                 */
/*   Updated: 2023/07/16 00:50:59 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free2m(char **s)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}
