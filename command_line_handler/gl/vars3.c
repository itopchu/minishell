/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vars3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:44:24 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 16:44:26 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*combine_vars(t_var *current)
{
	int		total_size;
	char	*combined;

	total_size = 2;
	if (current->var_name)
		total_size += ft_strlen(current->var_name);
	if (current->var_value)
		total_size += ft_strlen(current->var_value);
	combined = ft_calloc(total_size, sizeof(char));
	if (!combined)
		return (0);
	ft_strlcpy(combined, current->var_name, total_size);
	if (current->var_value)
	{
		ft_strlcat(combined, "=", total_size);
		ft_strlcat(combined, current->var_value, total_size);
	}
	return (combined);
}

int	replace_values(t_var *current, char *var_name,
		char *var_value, int replace_var_name)
{
	if (replace_var_name)
	{
		free(current->var_name);
		current->var_name = var_name;
	}
	if (current->var_value)
		free(current->var_value);
	current->var_value = var_value;
	if (current->combined)
		free(current->combined);
	current->combined = combine_vars(current);
	return (1);
}

int	set_var_norm(char *var_name, char *var_value,
	int replace_var_name, t_list **var_list)
{
	t_var	*current;

	current = ft_calloc(1, sizeof(t_var));
	if (!current)
		return (0);
	current->var_name = var_name;
	current->var_value = var_value;
	current->combined = combine_vars(current);
	if (replace_var_name == 2)
		current->export = 1;
	ft_lstadd_back(var_list, ft_lstnew((void *)current));
	return (1);
}

int	set_var(t_list **var_list, char *var_name,
		char *var_value, int replace_var_name)
{
	t_var	*current;
	t_list	*current_var;

	current_var = *var_list;
	while (current_var)
	{
		current = (t_var *)(current_var->content);
		if (!ft_strncmp(current->var_name, var_name, ft_strlen(var_name)))
		{
			if (!var_value)
			{
				free(var_value);
				free(var_name);
				return (1);
			}
			else
				return (replace_values(current, var_name, var_value,
						replace_var_name));
		}
		current_var = current_var->next;
	}
	return (set_var_norm(var_name, var_value, replace_var_name, var_list));
}
