/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 17:25:43 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 21:18:49 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**count_n_parts(int n_parts, t_com *commands_structs,
			t_com *prev_command_struct)
{
	char	**command_parts;

	if (!commands_structs || !prev_command_struct)
		return (0);
	command_parts = commands_structs->pars->command_parts;
	if (!command_parts)
		return (0);
	n_parts = 0;
	while (command_parts && *command_parts++)
		n_parts++;
	command_parts = prev_command_struct->pars->command_parts;
	while (command_parts && *command_parts++)
		n_parts++;
	command_parts = ft_calloc(n_parts, sizeof(char *));
	return (command_parts);
}

int	add_part_to_prev(t_com *commands_structs, t_com *prev_command_struct)
{
	int		n_parts;
	char	**command_parts;

	command_parts = count_n_parts(0, commands_structs, prev_command_struct);
	if (!command_parts)
		return (0);
	n_parts = -1;
	while (prev_command_struct->pars->command_parts
		&& *(prev_command_struct->pars->command_parts + ++n_parts))
		*(command_parts + n_parts) = *(prev_command_struct->pars->command_parts
				+ n_parts);
	if (n_parts < 0)
		n_parts = 0;
	if (prev_command_struct->pars->command_parts)
		free(prev_command_struct->pars->command_parts);
	prev_command_struct->pars->command_parts = command_parts;
	if (commands_structs)
		command_parts = (commands_structs->pars->command_parts + 1);
	while (commands_structs && *command_parts)
	{
		*(prev_command_struct->pars->command_parts
				+ n_parts++) = *command_parts;
		*command_parts++ = 0;
	}
	return (1);
}

int	input_file(t_com *commands_structs, t_com *prev_command_struct,
	t_env *env, int *failed)
{
	if (commands_structs->pars->end_stage1_divider == '<'
		&& !commands_structs->command)
	{
		if (!add_heredoc(commands_structs, prev_command_struct, env, failed))
			return (0);
	}
	else if (!add_read_file(commands_structs, prev_command_struct))
		return (0);
	return (1);
}

int	output_file(t_com *commands_structs, t_com *prev_command_struct)
{
	if (commands_structs->pars->end_stage1_divider == '>'
		&& !commands_structs->command)
	{
		if (!add_append_write_file(commands_structs,
				prev_command_struct))
			return (0);
	}
	else if (!add_write_file(commands_structs, prev_command_struct))
		return (0);
	return (1);
}

int	add_file_data(t_com *commands_structs,
	t_com *prev_command_struct, t_env *env, int *failed)
{
	while (commands_structs)
	{
		if (commands_structs->pars->start_stage1_divider == '<')
		{
			if (!input_file(commands_structs, prev_command_struct, env, failed))
				return (0);
		}
		else if (commands_structs->pars->start_stage1_divider == '>')
		{
			if (!output_file(commands_structs, prev_command_struct))
				return (0);
		}
		else
			prev_command_struct = commands_structs;
		if (prev_command_struct)
			commands_structs = prev_command_struct->next;
		else
			commands_structs = commands_structs->next;
	}
	return (1);
}
