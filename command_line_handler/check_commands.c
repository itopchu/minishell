/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 13:30:55 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/09/05 15:35:08 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file(t_redirect_files *c_file)
{
	if (!c_file)
		return (0);
	while (c_file)
	{
		if (!c_file->s)
			return (1);
		c_file = c_file->next;
	}
	return (0);
}

int	check_command(t_env *env)
{
	t_com	*c_command;

	if (!env->envp || !env->command)
		return (1);
	c_command = env->command;
	while (c_command)
	{
		if (check_file(c_command->file))
			return (2);
		if (!c_command->command && c_command->next)
			return (2);
		c_command = c_command->next;
	}
	return (0);
}
