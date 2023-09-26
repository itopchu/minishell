/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cd_path.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 21:25:40 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/01 21:25:40 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_check_dir(t_com *com, char *abs)
{
	struct stat	info;

	if (stat(abs, &info) == -1)
	{
		if (errno == ENOENT)
			failure_cond("cd", com->args[1], \
				"No such file or directory", ENOENT);
		else
			failure_cond("cd", abs, "Permission denied.", EACCES);
		g_sig = 1;
	}
	else if ((info.st_mode & S_IFMT) != S_IFDIR)
	{
		g_sig = failure_cond("cd", com->args[1], \
			"Not a directory", 1);
	}
	else
		return (0);
	do_free(&abs);
	return (1);
}

int	get_cd_path(t_com *com, char **buf)
{
	if (com->args[1][0] == '/')
	{
		*buf = ft_strdup("/");
		if (!*buf)
			return (error_exit("malloc", errno));
	}
	else
	{
		*buf = ft_strdup(com->env->lwd);
		if (!(*buf))
			return (error_exit("malloc", errno));
	}
	g_sig = do_resolve(com, buf, 1);
	if (g_sig)
		return (g_sig);
	return (do_check_dir(com, *buf));
}
