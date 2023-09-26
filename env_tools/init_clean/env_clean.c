/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_clean.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 16:25:27 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/04 16:25:27 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_envp_clean(t_env *env)
{
	if (env->envp)
		free(env->envp);
	env->envp = NULL;
}

void	do_var_clean(t_env *env)
{
	t_list	*list_cur;
	t_var	*var_cur;

	list_cur = env->var_list;
	while (list_cur)
	{
		var_cur = (t_var *)list_cur->content;
		if (var_cur)
		{
			if (var_cur->var_name)
				do_free(&var_cur->var_name);
			if (var_cur->var_value)
				do_free(&var_cur->var_value);
			if (var_cur->combined)
				do_free(&var_cur->combined);
			free(var_cur);
		}
		env->var_list = env->var_list->next;
		free(list_cur);
		list_cur = env->var_list;
	}
	env->var_list = NULL;
}

void	do_heredoc_clean(t_env *env)
{
	t_com				*c_com;
	t_redirect_files	*c_file;

	c_com = env->command;
	while (c_com)
	{
		c_file = c_com->file;
		while (c_file)
		{
			if (c_file->is_read && !c_file->is_default && c_file->s)
			{
				unlink(c_file->s);
				env->heredoc_n--;
			}
			c_file = c_file->next;
		}
		c_com = c_com->next;
	}
}

void	do_env_clean(t_env *env)
{
	if (env->lwd)
		do_free(&env->lwd);
	do_heredoc_clean(env);
	do_command_clean(env);
	do_var_clean(env);
	do_envp_clean(env);
	if (env->default_std[0] != -1)
	{
		close(env->default_std[0]);
		env->default_std[0] = -1;
	}
	if (env->default_std[1] != -1)
	{
		close(env->default_std[1]);
		env->default_std[1] = -1;
	}
}
