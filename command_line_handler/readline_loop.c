/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readline_loop.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 17:26:02 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/08/03 15:29:10 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*input_loop(int *end)
{
	char	*input;

	rl_on_new_line();
	input = readline("minishell$ ");
	if (!input)
	{
		rl_clear_history();
		*end = 1;
		return (0);
	}
	if (!*input)
	{
		free(input);
		return (input_loop(end));
	}
	add_history(input);
	return (input);
}

void	free_commands_list(t_list *commands, int del_premature)
{
	t_list	*to_del;

	while (commands)
	{
		to_del = commands;
		if (del_premature)
			delete_command(to_del->content, 0);
		commands = commands->next;
		free(to_del);
	}
}

/*
void	show_commands_structs(t_com *commands_structs)
{
	ft_printf("SHOW COMMANDS\n");
	while (commands_structs)
	{
		ft_printf("com struct:_com:%s", commands_structs->command);
		commands_structs = commands_structs->next;
	}
}
*/

void	clear_last_empty(t_com **commands_struct)
{
	t_com	*curr_commands_struct;
	t_com	*prev_commands_struct;

	prev_commands_struct = 0;
	curr_commands_struct = *commands_struct;
	while (curr_commands_struct && curr_commands_struct->pars->command_parts)
	{
		prev_commands_struct = curr_commands_struct;
		curr_commands_struct = curr_commands_struct->next;
	}
	if (curr_commands_struct && prev_commands_struct)
	{
		delete_command_struct(curr_commands_struct, 0);
		if (prev_commands_struct)
			prev_commands_struct->next = 0;
	}
}

t_com	*get_input(t_list *var_list, int *end, t_env *env, int *failed)
{
	char	*input;
	t_list	*commands;
	t_com	*commands_structs;

	input = input_loop(end);
	if (!input)
	{
		printf("exit\n");
		return (0);
	}
	commands = process_input(&input, var_list, failed);
	if (input)
		free(input);
	if (!commands)
		return (0);
	commands_structs = build_command_structs(commands);
	free_commands_list(commands, 0);
	if (!commands_structs)
		return (commands_structs);
	if (!add_file_data(commands_structs, 0, env, failed))
		*failed = 1;
	return (commands_structs);
}
