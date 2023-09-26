/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vars.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:44:08 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 16:44:10 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*find_var(t_list *var_list, char *var_name)
{
	while (var_list)
	{
		if (!ft_strcmp(var_name, ((t_var *)(var_list->content))->var_name))
			return (var_list);
		var_list = var_list->next;
	}
	return (0);
}

t_var	*get_var(t_list *var_list, char *var_name)
{
	t_list	*var;

	var = find_var(var_list, var_name);
	if (var)
		return ((t_var *)var->content);
	return (NULL);
}

void	delete_var(void *var_content)
{
	t_var	*content;

	if (!var_content)
		return ;
	content = var_content;
	if (content->var_name)
		free(content->var_name);
	if (content->var_value)
		free(content->var_value);
	if (content->combined)
		free(content->combined);
	free(content);
}

void	find_and_delete(char *var_name, t_list **var_list)
{
	t_list	*current;
	t_list	*to_del;

	current = *var_list;
	if (!ft_strcmp(var_name, ((t_var *)((*var_list)->content))->var_name))
	{
		*var_list = current->next;
		ft_lstdelone(current, &delete_var);
		return ;
	}
	while (current)
	{
		if (current->next && !ft_strcmp(var_name,
				((t_var *)(current->next->content))->var_name))
		{
			to_del = current->next;
			current->next = current->next->next;
			ft_lstdelone(to_del, &delete_var);
			return ;
		}
		current = current->next;
	}
}

int	export_var(t_list *var_list, char *var_name, int set_unset)
{
	var_list = find_var(var_list, var_name);
	if (var_list)
	{
		((t_var *)var_list->content)->export = set_unset;
		return (1);
	}
	return (0);
}
