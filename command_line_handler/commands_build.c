/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_build.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 17:05:31 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 17:05:33 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	*concetate_strings(char **command_parts)
{
	int		size;
	char	*text;
	char	**current_command;

	size = 0;
	if (!*command_parts)
		return (0);
	current_command = command_parts;
	while (*current_command)
		size += ft_strlen(*current_command++) + 1;
	text = ft_calloc(size, sizeof(char));
	current_command = command_parts;
	while (text && *current_command)
	{
		ft_strlcat(text, *current_command++, size);
		ft_strlcat(text, " ", size);
	}
	return (text);
}
*/
void	fill_command_option_rest(t_com *commands_structs)
{
	if (!commands_structs->pars)
		return ;
	if (commands_structs->pars->command_parts)
		commands_structs->command = *commands_structs->pars->command_parts;
}

/*
void	print_command_norm(int start, t_com	*commands_structs)
{
	if (SHOW_PARS_OUTPUT)
	{
		if (!start)
		{
			ft_printf("com struct:_com:%s", commands_structs->command);
		}
		else
			ft_printf("\n\nSHOWING COMMAND OUTPUT:\n");
		if (commands_structs && commands_structs->file)
			ft_printf("file number:%s_%i\n",
				commands_structs->file->s, commands_structs->file->fd);
	}
}
*/

t_com	*build_command_structs(t_list *commands)
{
	t_com	*commands_structs;
	t_com	*start_structs;

	commands_structs = 0;
	while (commands)
	{
		if (commands_structs)
		{
			commands_structs->next = ft_calloc(1, sizeof(t_com));
			commands_structs = commands_structs->next;
		}
		else
		{
			commands_structs = ft_calloc(1, sizeof(t_com));
			start_structs = commands_structs;
		}
		if (!commands_structs)
			return (clear_command_structs(commands_structs));
		commands_structs->pars = (t_pars *)commands->content;
		fill_command_option_rest(commands_structs);
		commands = commands->next;
	}
	return (start_structs);
}
