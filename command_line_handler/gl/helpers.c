/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:37:03 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 16:37:08 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ask_for_more(char **line)
{
	int		nl_len;
	char	*add;
	char	*new_line;

	add = readline("<");
	if (!add)
	{
		free(*line);
		*line = 0;
		return ;
	}
	add_history(add);
	nl_len = ft_strlen(*line) + ft_strlen(add) + 2;
	new_line = ft_calloc(nl_len, sizeof(char));
	if (new_line)
	{
		ft_strlcpy(new_line, *line, nl_len);
		ft_strlcat(new_line, "\n", nl_len);
		ft_strlcat(new_line, add, nl_len);
	}
	free(add);
	free(*line);
	*line = new_line;
}

/*
void	show_command(void *content)
{
	t_pars	*command;
	char	**parts;

	command = (t_pars *)content;
	ft_printf("%p\n", content);
	if (command)
	{
		ft_printf("Command: df=%c, dt=%c, from:%p, till:%p\n",
			command->start_stage1_divider, command->end_stage1_divider,
			command->start_line, command->end_line);
		if (command->var_list)
			ft_printf("var_list: %p\n", command->var_list);
		if (command->command_copy && command->start_line)
			ft_printf("Clean copy:_%s_\n", command->command_copy);
		if (command->command_parts)
		{
			parts = command->command_parts;
			ft_printf("parts present\n");
			while (*parts)
				ft_printf("%s\n", parts);
		}
	}
}

void	show_var(void *var_content)
{
	t_var	*var;

	var = (t_var *)var_content;
	if (var)
	{
		ft_printf("%s=%s\n", var->var_name, var->var_value);
	}
}

void	show_commands(t_list *commands)
{
	ft_printf("-----Showing commands------\n");
	if (commands)
	{
		ft_lstiter(commands, &show_command);
		ft_printf("-----Showing vars----------\n");
		if (((t_pars *)commands->content)->var_list)
			ft_lstiter(((t_pars *)commands->content)->var_list, &show_var);
	}
	ft_printf("---------------------------\n");
}
*/

void	delete_command(void *command_content, int transfer)
{
	t_pars	*content;
	char	**command_parts;

	if (!command_content)
		return ;
	content = (t_pars *)command_content;
	if (content->command_copy)
		free(content->command_copy);
	if (content->command_line)
		free(content->command_line);
	if (content->command_parts)
	{
		command_parts = content->command_parts;
		while (*command_parts && !transfer)
			free(*command_parts++);
		free(content->command_parts);
	}
	free(content);
}
