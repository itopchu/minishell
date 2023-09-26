/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_exec_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 19:19:34 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/01 19:19:34 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_exec_check(t_com *com, char *path)
{
	struct stat	info;

	g_sig = 0;
	if (stat(path, &info) == -1)
		g_sig = failure_cond(NULL, com->args[0], \
			"No such file or directory", 127);
	else if ((info.st_mode & S_IFMT) == S_IFDIR)
		g_sig = failure_cond(NULL, com->args[1], \
		"is a directory", 126);
	else if ((info.st_mode & S_IXUSR) == 0)
		g_sig = failure_cond(NULL, com->args[0], \
		"Permission denied", 126);
	return (g_sig);
}

int	get_exec_path(t_com *com, char **buf)
{
	if (com->args[0][0] != '.' && com->args[0][0] != '/')
		return (get_path_path(com, com->args[0], buf));
	if (com->args[0][0] == '/')
	{
		*buf = ft_strdup("/");
		if (!*buf)
			return (error_exit("malloc", errno));
	}
	else
	{
		*buf = ft_strdup(com->env->lwd);
		if (!*buf)
			return (error_exit("malloc", errno));
	}
	g_sig = do_resolve(com, buf, 0);
	if (g_sig)
		return (g_sig);
	if (do_exec_check(com, *buf))
		return (do_free(buf), g_sig);
	return (0);
}
