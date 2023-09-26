/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 17:25:49 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/08/08 03:47:52 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_read_file(t_com *commands_structs, t_com *prev_command_struct)
{
	if (!add_file(commands_structs, prev_command_struct, 1, 1))
		return (0);
	if (prev_command_struct)
	{
		add_part_to_prev(commands_structs, prev_command_struct);
		prev_command_struct->next = commands_structs->next;
		fill_command_option_rest(prev_command_struct);
		delete_command_struct(commands_structs, 1);
	}
	return (1);
}

void	add_heredoc_norm(t_com *c_structs, t_com *prev_c_structs, int *failed)
{
	if (c_structs->command)
	{
		if (prev_c_structs && prev_c_structs->file)
		{
			if (prev_c_structs->file->delimiter)
				free(prev_c_structs->file->delimiter);
			if (c_structs->pars && c_structs->pars->command_copy
				&& (ft_strchr(c_structs->pars->command_copy, '"')
					|| ft_strchr(c_structs->pars->command_copy, '\'')))
				prev_c_structs->file->heredoc_no_expand = 1;
			prev_c_structs->file->delimiter = ft_strdup(
					c_structs->command);
		}
	}
	else
		*failed = 1;
}

int	add_heredoc(t_com *commands_structs, t_com *prev_command_struct,
	t_env *env, int *failed)
{
	t_com	*to_del;

	to_del = commands_structs;
	commands_structs = commands_structs->next;
	delete_command_struct(to_del, 0);
	if (!commands_structs
		|| !add_file(commands_structs, prev_command_struct, 0, 0))
		return (0);
	add_heredoc_norm(commands_structs, prev_command_struct, failed);
	if (prev_command_struct)
	{
		add_part_to_prev(commands_structs, prev_command_struct);
		prev_command_struct->next = commands_structs->next;
		fill_command_option_rest(prev_command_struct);
		delete_command_struct(commands_structs, 1);
		if (!*failed)
			return (do_here_doc(env, prev_command_struct->file));
	}
	return (1);
}

int	add_append_write_file(t_com *commands_structs, t_com *prev_command_struct)
{
	t_com	*to_del;

	to_del = commands_structs;
	commands_structs = commands_structs->next;
	delete_command_struct(to_del, 0);
	if (!commands_structs
		|| !add_file(commands_structs, prev_command_struct, 0, 0))
		return (0);
	if (prev_command_struct)
	{
		add_part_to_prev(commands_structs, prev_command_struct);
		prev_command_struct->next = commands_structs->next;
		fill_command_option_rest(prev_command_struct);
		delete_command_struct(commands_structs, 1);
	}
	return (1);
}

int	add_write_file(t_com *commands_structs, t_com *prev_command_struct)
{
	if (!add_file(commands_structs, prev_command_struct, 0, 1))
		return (0);
	if (prev_command_struct)
	{
		add_part_to_prev(commands_structs, prev_command_struct);
		prev_command_struct->next = commands_structs->next;
		fill_command_option_rest(prev_command_struct);
		delete_command_struct(commands_structs, 1);
	}
	return (1);
}
