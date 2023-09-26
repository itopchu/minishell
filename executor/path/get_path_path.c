/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 17:32:02 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/01 17:32:02 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_path_resolve(t_com *com, char **split, char *s, char **buf)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		*buf = ft_strdup(split[i]);
		if (!*buf || append_with_con(buf, '/', s))
			return (do_free(buf), error_exit("malloc", errno));
		if (access(*buf, X_OK) == 0)
			return (0);
		do_free(buf);
	}
	g_sig = 127;
	return (failure_cond(NULL, com->args[0], "command not found", 127));
}

int	get_path_path(t_com *com, char *s, char **buf)
{
	char	**split;
	t_var	*path;

	path = do_get_var(com->env->var_list, "PATH");
	if (!path || !path->var_value)
		return (do_free(buf), failure_cond(NULL, com->args[0], \
				"No such file or directory", 127));
	split = ft_split(path->var_value, ':');
	if (!split)
		return (do_free(buf), error_exit("malloc", errno));
	if (get_path_resolve(com, split, s, buf))
		return (ft_free2m(split), g_sig);
	ft_free2m(split);
	return (0);
}
