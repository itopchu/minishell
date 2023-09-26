/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 17:04:05 by itopchu       #+#    #+#                 */
/*   Updated: 2022/10/08 17:04:05 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s_len;
	char	*new_s;

	s_len = ft_strlen(s1) + ft_strlen(s2);
	new_s = (char *)malloc(s_len + 1);
	if (new_s)
	{
		while (*s1)
			*new_s++ = *s1++;
		while (*s2)
			*new_s++ = *s2++;
		*new_s = 0;
		return (new_s - s_len);
	}
	return (0);
}
