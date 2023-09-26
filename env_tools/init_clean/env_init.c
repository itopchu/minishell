/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 17:40:23 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/04 17:40:23 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_shlvl_update(t_env *env)
{
	t_var	*shlvl;
	char	*name;
	char	*value;

	shlvl = get_var(env->var_list, "SHLVL");
	if (!shlvl || !shlvl->var_value)
	{
		name = ft_strdup("SHLVL");
		if (!name)
			return (error_exit("malloc", errno));
		value = ft_strdup("1");
		if (!value)
			return (do_free(&name), error_exit("malloc", errno));
		if (!set_var(&(env->var_list), name, value, 1))
			return (error_exit("malloc", errno));
	}
	else
	{
		value = ft_itoa(do_uatoi(shlvl->var_value) + 1);
		if (!value || !set_var(&(env->var_list), "SHLVL", value, 0))
			return (error_exit("malloc", errno));
	}
	return (0);
}

int	init_default_std(t_env *env)
{
	env->default_std[0] = -1;
	env->default_std[1] = -1;
	env->default_std[0] = dup(STDIN_FILENO);
	if (env->default_std[0] == -1)
		return (error_exit("dup", errno));
	env->default_std[1] = dup(STDOUT_FILENO);
	if (env->default_std[1] == -1)
	{
		close(env->default_std[0]);
		env->default_std[0] = -1;
		return (error_exit("dup", errno));
	}
	return (0);
}

int	setup_lwd(t_env *env)
{
	env->lwd = getcwd(NULL, 0);
	if (!env->lwd)
		g_sig = failure_cond(NULL, "getcwd", \
				"current working directory cannot be found", 1);
	return (0);
}

static void	init_null_env(t_env *env)
{
	env->var_list = NULL;
	env->command = NULL;
	env->envp = NULL;
	env->lwd = NULL;
	env->end = 0;
	env->heredoc_n = 0;
	env->spare_exit = 0;
	g_sig = 0;
}

int	init_env(t_env *env, char **envp)
{
	init_null_env(env);
	if (init_default_std(env))
		return (g_sig);
	if (setup_lwd(env) || \
		!setup_var_list(&env->var_list) || \
		!add_envpp_to_var_list(env->var_list, envp))
		return (do_env_clean(env), error_exit("malloc", errno));
	if (do_shlvl_update(env))
		return (do_env_clean(env), errno);
	return (0);
}
