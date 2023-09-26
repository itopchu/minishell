/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_keeper.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 17:06:40 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 17:06:42 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_envpp_to_var_list(t_list *var_list, char **envpp)
{
	char	*new_line;
	char	*var_name;
	char	*var_value;

	while (envpp && *envpp)
	{
		new_line = extract_new_var(*envpp, &var_name, &var_value);
		if (new_line)
			free(new_line);
		if (var_name && var_value)
		{
			if (!set_var(&var_list, var_name, var_value, 1))
				return (0);
		}
		else
			return (0);
		export_var(var_list, var_name, 1);
		envpp++;
	}
	return (1);
}

// char	**build_envpp(int n, t_list *var_list, char **envpp_edited)
// {
// 	char	**start_envpp;

// 	envpp_edited = ft_calloc(n, sizeof(char *));
// 	start_envpp = envpp_edited;
// 	if (!envpp_edited)
// 		return (0);
// 	while (var_list)
// 	{
// 		if (((t_var *)var_list->content)->export
// 			&& ((t_var *)var_list->content)->var_value)
// 			*envpp_edited++ = ((t_var *)var_list->content)->combined;
// 		var_list = var_list->next;
// 	}
// 	*envpp_edited = 0;
// 	return (start_envpp);
// }

// void	show_envpp(char **envpp_edited)
// {
// 	if (SHOW_ENVPP && envpp_edited)
// 	{
// 		ft_printf("\n\nSHOWING ENVPP:\n");
// 		while (*envpp_edited)
// 			ft_printf("%s\n", *envpp_edited++);
// 	}
// }

// char	**make_envpp(t_list *var_list, char **envpp_edited)
// {
// 	int		n;
// 	t_list	*current_var;

// 	if (envpp_edited)
// 	{
// 		free(envpp_edited);
// 		envpp_edited = 0;
// 	}
// 	n = 1;
// 	current_var = var_list;
// 	while (current_var)
// 	{
// 		if (((t_var *)current_var->content)->export)
// 			n++;
// 		current_var = current_var->next;
// 	}
// 	envpp_edited = build_envpp(n, var_list, envpp_edited);
// 	if (SHOW_ENVPP)
// 		show_envpp(envpp_edited);
// 	return (envpp_edited);
// }
