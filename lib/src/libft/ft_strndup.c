/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/16 00:48:48 by itopchu       #+#    #+#                 */
/*   Updated: 2023/07/16 00:48:48 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t n)
{
	size_t	len;
	char	*new;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (n < len)
		len = n;
	new = malloc(sizeof(char) * (len + 1));
	ft_memcpy(new, str, len);
	new[len] = '\0';
	return (new);
}
