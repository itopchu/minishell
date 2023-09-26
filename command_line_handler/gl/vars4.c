/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vars4.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 11:55:00 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/08/31 11:55:02 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_string(char *from, char *till, char **dst)
{
	*dst = ft_calloc(till - from + 1, sizeof(char));
	if (!*dst)
		return (0);
	ft_strlcpy(*dst, from, till - from + 1);
	return (1);
}

void	extract_new_vars_norm(char **var_name, char **var_value,
	int add_to_list, t_pars *content)
{
	if (*var_name && *var_value && add_to_list)
		set_var(&content->var_list, *var_name, *var_value, 1);
	else if (*var_name && add_to_list)
		set_var(&content->var_list, *var_name, *var_value, 2);
	else
	{
		if (*var_name)
			free(*var_name);
		if (*var_value)
			free(*var_value);
	}
	*var_name = 0;
	*var_value = 0;
}

void	extract_new_vars(void *command_content, int add_to_list)
{
	t_pars	*content;
	char	*var_name;
	char	*var_value;
	char	*line;

	var_name = 0;
	var_value = 0;
	content = (t_pars *)command_content;
	line = content->command_copy;
	while (line)
	{
		line = extract_new_var(line, &var_name, &var_value);
		if (line != content->command_copy && line)
		{
			free(content->command_copy);
			content->command_copy = line;
		}
		extract_new_vars_norm(&var_name, &var_value, add_to_list, content);
	}
	if (line != content->command_copy && line)
	{
		free(content->command_copy);
		content->command_copy = line;
	}
}

int	check_exit_code(t_var *exit_code)
{
	if (!exit_code->var_name || !exit_code->var_value)
	{
		if (exit_code->var_name)
			free(exit_code->var_name);
		if (exit_code->var_value)
			free(exit_code->var_value);
		free(exit_code);
		return (0);
	}
	*exit_code->var_name = '?';
	*exit_code->var_value = '0';
	exit_code->export = 0;
	return (1);
}

int	setup_var_list(t_list **var_list)
{
	t_var	*exit_code;

	*var_list = ft_calloc(1, sizeof(t_list));
	if (!var_list)
		return (0);
	exit_code = ft_calloc(1, sizeof(t_var));
	(*var_list)->content = exit_code;
	if (!exit_code)
	{
		free(*var_list);
		return (0);
	}
	exit_code->var_name = ft_calloc(2, sizeof(char));
	exit_code->var_value = ft_calloc(2, sizeof(char));
	return (check_exit_code(exit_code));
}
