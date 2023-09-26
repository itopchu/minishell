/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stage1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:01 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 16:39:03 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define STAGE1DIVIDERS "|><"

void	link_new_command(t_list **commands, t_list *new_item,
			char *line, int start)
{
	t_pars	*last_command;

	if (*commands)
	{
		last_command = (t_pars *)ft_lstlast(*commands)->content;
		last_command->end_stage1_divider = *line;
		last_command->end_line = line - 1;
	}
	((t_pars *)((new_item)->content))->start_line = line;
	if (!start)
		((t_pars *)((new_item)->content))->start_stage1_divider = *line;
	((t_pars *)((new_item)->content))->start = start;
	ft_lstadd_back(commands, new_item);
}

char	*find_stage1_dividers(char *line, t_list **commands,
			int start, t_list *var_list)
{
	char	*divider;
	t_pars	*sub_command;
	t_list	*new_item;

	divider = ft_strchr(STAGE1DIVIDERS, *line);
	if (divider || start)
	{
		sub_command = (t_pars *)ft_calloc(1, sizeof(t_pars));
		if (!sub_command)
			return (0);
		sub_command->var_list = var_list;
		new_item = ft_lstnew((void *)sub_command);
		if (!new_item)
		{
			free(sub_command);
			return (0);
		}
		link_new_command(commands, new_item, line, start);
	}
	return (line);
}
