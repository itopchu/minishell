/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_clean.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 16:27:36 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/04 16:27:36 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_file_clean(t_com *com)
{
	t_redirect_files	*cur;

	if (!com)
		return ;
	cur = com->file;
	while (cur)
	{
		if (cur->delimiter)
			do_free(&cur->delimiter);
		if (cur->s)
			do_free(&cur->s);
		com->file = com->file->next;
		free(cur);
		cur = com->file;
	}
	com->file = NULL;
}

void	do_pars_clean(t_com *com)
{
	t_pars	*cur;

	if (!com->pars)
		return ;
	cur = com->pars;
	if (cur->command_line)
		do_free(&cur->command_line);
	if (cur->command_copy)
		do_free(&cur->command_copy);
	ft_free2m(cur->command_parts);
	free(com->pars);
	com->pars = NULL;
}

void	do_command_clean(t_env *env)
{
	t_com	*cur;

	cur = env->command;
	while (cur)
	{
		do_file_clean(cur);
		do_pars_clean(cur);
		env->command = env->command->next;
		free(cur);
		cur = env->command;
	}
	env->command = NULL;
}
