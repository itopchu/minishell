/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 15:39:38 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 15:39:38 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// name = ft_strdup("OLDPWD");
	// if (!name)
	// 	return (do_free(&s), do_free(&old), 
	//		error_exit(com->env, "malloc", errno));
	// if (!set_var(&(com->env->var_list), name, old, 1))
	// 	return (do_free(&s), error_exit(com->env, "malloc", errno));
	// export_var(com->env->var_list, "OLDPWD", 1);

static int	do_local_set_var(t_env *env, char *name, char *value)
{
	char	*new;

	new = ft_strdup(name);
	if (!new)
	{
		free(value);
		return (error_exit("malloc", errno));
	}
	if (!set_var(&(env->var_list), new, value, 1))
		return (error_exit("malloc", errno));
	export_var(env->var_list, new, 1);
	return (0);
}

static int	change_dir(char *s, t_com *com)
{
	char	*tmp;
	char	*old;

	old = ft_strdup(com->env->lwd);
	if (!old)
		return (do_free(&s), error_exit("malloc", errno));
	if (chdir(s) == -1)
		return (do_free(&s), do_free(&old), perror("chdir"), 1);
	if (do_local_set_var(com->env, "OLDPWD", old))
		return (do_free(&s), g_sig);
	if (do_local_set_var(com->env, "PWD", s))
		return (g_sig);
	tmp = ft_strdup(get_var(com->env->var_list, "PWD")->var_value);
	if (!tmp)
		return (error_exit("malloc", errno));
	free(com->env->lwd);
	com->env->lwd = tmp;
	return (0);
}

static int	check_args(t_com *com)
{
	if (!com->args[1])
	{
		g_sig = 1;
		return (-failure_cond("cd", "given", "no directory", 1));
	}
	else if (com->args[1][0] == '-')
	{
		g_sig = 2;
		failure_cond("cd", NULL, "invalid option", 2);
		return (-failure_cond("cd", "usage", "cd [dir]", 2));
	}
	return (0);
}

int	execute_cd(t_com *com)
{
	char	*buf;

	buf = NULL;
	if (check_args(com) != 0)
		return (g_sig);
	if (get_cd_path(com, &buf))
		return (g_sig);
	return (change_dir(buf, com));
}
