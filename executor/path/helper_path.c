/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resolve_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 19:31:29 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 19:31:29 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_deduct(char **split, int index, char *str, char delim)
{
	char	*last_delim;
	int		count;

	count = 0;
	while (split[index] && !ft_strcmp(split[index], ".."))
	{
		count++;
		last_delim = ft_strrchr(str, delim);
		if (last_delim == str)
		{
			str[1] = '\0';
			return (count);
		}
		else if (last_delim)
			*last_delim = '\0';
		else
			return (count);
		index++;
	}
	return (count);
}

int	append_with_con(char **left, char connector, char *right)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(*left);
	len2 = 0;
	if (right)
		len2 = ft_strlen(right);
	new = malloc(sizeof(char) * (len1 + len2 + (connector != 0) + 1));
	if (!new)
		return (1);
	ft_strlcpy(new, *left, len1 + 1);
	if (connector != 0)
		new[len1] = connector;
	if (len2)
		ft_strlcpy(new + len1 + (connector != 0), right, len2 + 1);
	new[len1 + len2 + (connector != 0)] = '\0';
	if (*left)
		do_free(left);
	*left = new;
	return (0);
}

static int	do_append_helper(t_com *com, char **buf, char **split, int i)
{
	char	con;

	con = '/';
	if (!ft_strcmp(*buf, "/"))
		con = 0;
	if (append_with_con(buf, con, split[i]))
		return (ft_free2m(split), do_free(buf), error_exit("malloc", errno));
	if (split[i + 1] && access(*buf, F_OK) < 0)
		return (1);
	return (0);
}

int	do_resolve(t_com *com, char **buf, int arg_ind)
{
	char	**split;
	int		i;

	split = ft_split(com->args[arg_ind], '/');
	if (!split)
		return (do_free(buf), error_exit("malloc", errno));
	i = -1;
	while (split[++i])
	{
		if (!ft_strcmp(split[i], "."))
			;
		else if (!ft_strcmp(split[i], ".."))
			i += do_deduct(split, i, *buf, '/') - 1;
		else if (do_append_helper(com, buf, split, i))
			return (ft_free2m(split), do_free(buf), failure_cond(NULL, \
					com->args[arg_ind], "No such file or directory", 127));
	}
	ft_free2m(split);
	return (0);
}
