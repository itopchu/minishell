/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 12:05:55 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/08/31 12:05:57 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_file_norm(t_redirect_files **current,
	t_redirect_files **file, t_com *command_struct_of_interest)
{
	if (command_struct_of_interest->file)
	{
		*current = command_struct_of_interest->file;
		while ((*current)->next)
			*current = (*current)->next;
		(*current)->next = *file;
	}
	else
		command_struct_of_interest->file = *file;
}

int	add_file(t_com *com_structs, t_com *prev_com_structs, int read, int is_def)
{
	t_redirect_files	*file;
	t_redirect_files	*current;

	file = ft_calloc(1, sizeof(t_redirect_files));
	if (!file)
		return (0);
	if (prev_com_structs)
		add_file_norm(&current, &file, prev_com_structs);
	else
		add_file_norm(&current, &file, com_structs);
	file->s = com_structs->command;
	file->is_read = read;
	file->is_default = is_def;
	return (1);
}
