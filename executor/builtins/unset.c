/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 14:08:47 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 14:08:47 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_unset(t_com *com)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	name = NULL;
	value = NULL;
	while (com->args[++i])
	{
		if (do_extract_var(com->args[i], &name, &value))
			return (error_exit("malloc", errno));
		find_and_delete(name, &(com->env->var_list));
		do_free(&name);
		do_free(&value);
	}
	return (g_sig);
}
