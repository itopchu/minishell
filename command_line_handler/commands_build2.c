/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_build2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 17:06:17 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/28 08:03:39 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	delete_file_structs(t_redirect_files *file)
// {
// 	t_redirect_files	*to_del;

// 	while (file)
// 	{
// 		to_del = file;
// 		file = file->next;
// 		if (to_del->delimiter)
// 			free(to_del->delimiter);
// 		if (to_del->s != to_del->delimiter)
// 		{
// 			free(to_del->s);
// 			to_del->s = NULL;
// 		}
// 		free(to_del);
// 	}
// }

void	delete_command_struct(t_com *command_structs, int transfer)
{
	if (command_structs->file)
		do_file_clean(command_structs);
	if (command_structs->pars)
		delete_command(command_structs->pars, transfer);
	free(command_structs);
}

t_com	*clear_command_structs(t_com *command_structs)
{
	t_com	*next_struct;

	while (command_structs)
	{
		next_struct = command_structs->next;
		delete_command_struct(command_structs, 0);
		command_structs = next_struct;
	}
	return (0);
}
