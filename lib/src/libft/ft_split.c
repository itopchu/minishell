/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 17:02:59 by itopchu       #+#    #+#                 */
/*   Updated: 2022/10/08 17:02:59 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	ft_free_local_2m(char **data)
{
	int	i;

	if (!data)
		return ;
	i = -1;
	while (data[++i])
		free(data[i]);
	free(data);
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	while (s[++i])
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			ret++;
	return (ret);
}

static int	ft_con_word(char **to_connect, const char *s, int i, int *start)
{
	int	len;

	len = i - *start + 1;
	*to_connect = ft_substr(s, *start, len);
	if (!(*to_connect))
		return (1);
	*start = -1;
	return (0);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		start;
	int		word;
	char	**result;

	result = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!result)
		return (NULL);
	i = -1;
	word = 0;
	start = -1;
	while (s[++i])
	{
		if (s[i] != c && start == -1)
			start = i;
		if (start != -1 && (!s[i + 1] || s[i + 1] == c))
			if (ft_con_word(&result[word++], s, i, &start))
				return (ft_free_local_2m(result), NULL);
	}
	result[word] = NULL;
	return (result);
}
