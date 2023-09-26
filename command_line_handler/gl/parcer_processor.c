/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer_processor.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:38:13 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 16:38:17 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*stage_1(char **start_line, t_list *commands,
	t_list *var_list, int failed)
{
	char	*line;

	line = *start_line;
	line = find_stage1_dividers(line, &commands, 1, var_list);
	while (line && *line)
	{
		line = single_quote_stage1(line, 1, &failed);
		line = double_quote_stage1(line, &failed);
		if (*line)
			line = find_stage1_dividers(line, &commands, 0, var_list);
		if (!line)
			exit(1);
		if (*line && *line != '\'' && *line != '\"')
			line++;
	}
	if (failed)
	{
		ask_for_more(start_line);
		free_commands_list(commands, 1);
		if (!*start_line)
			return (0);
		failed = 0;
		return (stage_1(start_line, 0, var_list, 0));
	}
	return (commands);
}

t_list	*stage_2(t_list *commands)
{
	ft_lstiter(commands, &stage2_copy_line_part);
	return (commands);
}

t_list	*stage_3(t_list *commands)
{
	t_list	*commands_it;

	ft_lstiter(commands, &stage3_var_handling);
	extract_new_vars(commands->content, 1);
	commands_it = commands->next;
	while (commands_it)
	{
		extract_new_vars(commands_it->content, 0);
		commands_it = commands_it->next;
	}
	return (commands);
}

t_list	*stage_4(t_list *commands)
{
	ft_lstiter(commands, &stage4_whiteline_remove);
	return (commands);
}

t_list	*process_input(char **line, t_list *var_list, int *failed)
{
	t_list	*commands;

	commands = 0;
	*failed = do_update_exitmark(var_list);
	if (*failed)
		return (0);
	commands = stage_1(line, commands, var_list, 0);
	if (!*line)
	{
		*failed = 1;
		return (commands);
	}
	commands = stage_2(commands);
	commands = stage_3(commands);
	commands = stage_4(commands);
	return (commands);
}
