/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stage4.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:43:54 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 16:43:55 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_parts(char *com_copy)
{
	int	n_parts;

	n_parts = 0;
	while (*com_copy)
	{
		while (ft_strchr(WHITELINES, *com_copy) && *com_copy)
			com_copy++;
		if (!*com_copy)
			break ;
		while (!ft_strchr(WHITELINES, *com_copy)
			&& *com_copy)
		{
			if (*com_copy && *com_copy != '\'' && *com_copy != '\"')
				com_copy++;
			com_copy = double_quote_stage1(com_copy, 0);
			com_copy = single_quote_stage1(com_copy, 0, 0);
		}
		n_parts++;
	}
	return (n_parts);
}

static char	*count_part_len_norm(char *command_copy)
{
	char	*end_part;

	end_part = command_copy;
	while (!ft_strchr(WHITELINES, *end_part)
		&& *end_part)
	{
		if (*end_part && *end_part != '\'' && *end_part != '\"')
			end_part++;
		end_part = double_quote_stage1(end_part, 0);
		end_part = single_quote_stage1(end_part, 0, 0);
	}
	return (end_part);
}

int	count_part_len(char *command_copy, char **command_parts)
{
	int		total_len;
	char	*end_part;

	total_len = 0;
	while (*command_copy)
	{
		while (ft_strchr(WHITELINES, *command_copy) && *command_copy)
			command_copy++;
		if (!*command_copy)
			return (total_len);
		end_part = count_part_len_norm(command_copy);
		if (end_part > command_copy)
			*command_parts = ft_calloc(end_part - command_copy + 2,
					sizeof(char));
		if (!*command_parts)
			return (0);
		ft_strlcpy(*command_parts, command_copy, end_part - command_copy + 1);
		total_len += end_part - command_copy + 1;
		command_copy = end_part;
		command_parts++;
	}
	return (total_len);
}

void	remove_whitelines_and_split(t_pars *content)
{
	int		n;
	char	**command_parts;

	n = count_parts(content->command_copy);
	if (!n)
		return ;
	content->command_parts = ft_calloc(n + 1, sizeof(char *));
	if (!content->command_parts)
		return ;
	n = count_part_len(content->command_copy, content->command_parts);
	if (!n)
		return ;
	free(content->command_copy);
	content->command_copy = ft_calloc(n + 1, sizeof(char));
	command_parts = content->command_parts;
	while (*command_parts)
	{
		if (command_parts != content->command_parts)
			ft_strlcat(content->command_copy, " ", n);
		ft_strlcat(content->command_copy, (*command_parts), n);
		command_parts++;
	}
	return ;
}

void	stage4_whiteline_remove(void *command_content)
{
	t_pars	*content;

	content = (t_pars *)command_content;
	remove_whitelines_and_split(content);
	remove_quotes(content);
}
