/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 16:18:25 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 16:18:25 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_add_arg(char ***arg, char **line)
{
	char	**new_arg;
	int		len;

	if (!(*line))
		return (0);
	len = -1;
	while ((*arg)[++len])
		;
	new_arg = malloc(sizeof(char *) * (len + 2));
	if (!new_arg)
		return (errno);
	new_arg[len] = *line;
	new_arg[len + 1] = NULL;
	len = -1;
	while ((*arg)[++len])
		new_arg[len] = (*arg)[len];
	free(*arg);
	*arg = new_arg;
	return (0);
}

int	do_strlen_var(char *s, int var)
{
	int	i;

	if (!s)
		return (-1);
	i = -1;
	while (s[++i] != (char)var)
		if (!s[i])
			return (-1);
	return (i);
}

int	do_extract_var(char *s, char **name, char **value)
{
	int	len;

	if (!s)
		return (0);
	len = do_strlen_var(s, '=');
	if (len == -1)
	{
		*name = ft_strdup(s);
		if (!(*name))
			return (errno);
		return (0);
	}
	*name = ft_strndup(s, len);
	if (!*name)
		return (errno);
	if (s[len + 1] == '\0')
		*value = ft_calloc(1, sizeof(char));
	else
		*value = ft_strdup(&s[len + 1]);
	if (!*value)
		return (do_free(name), errno);
	return (0);
}

t_var	*do_get_var(t_list *list, char *s)
{
	while (list)
	{
		if (!ft_strcmp(((t_var *)list->content)->var_name, s))
			return ((t_var *)list->content);
		list = list->next;
	}
	return (NULL);
}
