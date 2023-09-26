/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stage2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:09 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 16:39:11 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stage2_copy_line_part(void *command_content)
{
	int		command_length;
	t_pars	*content;

	if (!command_content)
		return ;
	content = (t_pars *)command_content;
	if (content->end_line)
		command_length = content->end_line - content->start_line
			+ 1 + content->start;
	else
		command_length = ft_strlen(content->start_line) + content->start + 1;
	content->command_copy = ft_calloc(command_length, sizeof(char));
	if (!content->command_copy)
		return ;
	if (content->start_stage1_divider)
	{
		ft_strlcpy(content->command_copy, content->start_line + 1,
			command_length);
	}
	else
		ft_strlcpy(content->command_copy, content->start_line, command_length);
}
