/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vars2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:44:16 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 16:44:17 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_var_handle(char **start, char **line)
{
	*start = *line + 1;
	if (**start == '"')
	{
		*start = *start;
		*line += 2;
		while (**line != '"')
			(*line)++;
		(*line)++;
		return (1);
	}
	else if (**start == '\'')
	{
		*start = *start;
		*line += 2;
		while (**line != '\'')
			(*line)++;
		(*line)++;
		return (1);
	}
	return (0);
}

char	*copy_var_from_expr(char *start, char *line,
	char **var_name, char **var_value)
{
	char	*new_line;

	if (ft_strchr(VAR_CLOSERS, *line))
		start = line + 1;
	while (*line != '=')
		line++;
	if (!copy_string(start, line, var_name))
		return (0);
	if (!quotes_var_handle(&start, &line))
		while (*line && !ft_strchr(VAR_CLOSERS, *line))
			line++;
	if (!copy_string(start, line, var_value))
	{
		free(*var_name);
		return (0);
	}
	new_line = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!new_line)
		return (0);
	ft_strlcpy(new_line, line, ft_strlen(line) + 1);
	return (new_line);
}

char	*extract_new_var(char *line, char **var_name,
	char **var_value)
{
	char	*start;

	start = line;
	if (!line || !*line)
		return (0);
	while (ft_strchr(WHITELINES, *line) && *line)
		line++;
	while (!ft_strchr(WHITELINES, *line) && *line)
	{
		if (*line == '=')
		{
			while (*line && line > start && (ft_isalnum(*line) || *line == '_'))
				line--;
			return (copy_var_from_expr(start, line, var_name, var_value));
		}
		line++;
	}
	return (0);
}
