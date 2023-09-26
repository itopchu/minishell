/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 14:13:06 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 14:13:06 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_export_add(t_com *com, int i)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if (do_extract_var(com->args[i], &name, &value))
		return (error_exit("malloc", errno));
	if (!set_var(&(com->env->var_list), name, value, 1))
		return (error_exit("malloc", errno));
	export_var(com->env->var_list, name, 1);
	return (0);
}

int	do_check_validity(char *s)
{
	int	i;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (1);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			break ;
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_')
			return (1);
	}
	return (0);
}

static int	do_export(t_com *com)
{
	int	check;
	int	i;

	i = 0;
	while (com->args[++i])
	{
		check = do_check_validity(com->args[i]);
		if (check == 1)
		{
			g_sig = 1;
			ft_putstr_fd("-minishell: export `", STDERR_FILENO);
			ft_putstr_fd(com->args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		}
		else if (check == 0 && do_export_add(com, i))
			return (errno);
	}
	return (g_sig);
}

void	do_export_print(t_com *com)
{
	t_list	*list;
	t_var	*var;

	list = com->env->var_list;
	while (list)
	{
		if ((((t_var *)list->content)->export))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(((t_var *)(list->content))->var_name, STDOUT_FILENO);
			var = ((t_var *)(list->content));
			if (var->var_value != NULL)
			{
				ft_putstr_fd("=", STDOUT_FILENO);
				ft_putstr_fd("\"", STDOUT_FILENO);
				ft_putstr_fd(var->var_value, STDOUT_FILENO);
				ft_putstr_fd("\"", STDOUT_FILENO);
			}
			write(STDOUT_FILENO, "\n", 1);
		}
		list = list->next;
	}
}

int	execute_export(t_com *com)
{
	if (!com->args || !com->args[0])
		return (0);
	if (com->args[1])
		return (do_export(com));
	do_export_print(com);
	return (0);
}
