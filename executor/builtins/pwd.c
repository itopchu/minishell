/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 14:11:11 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 14:11:11 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_args(t_com *com)
{
	if (com->args[1] && com->args[1][0] == '-')
	{
		failure_cond("pwd", com->args[1], "invalid option", 2);
		failure_cond("pwd", "usage", "pwd", 2);
		return (2);
	}
	return (0);
}

int	execute_pwd(t_com *com)
{
	g_sig = check_args(com);
	if (g_sig)
		return (g_sig);
	ft_putendl_fd(com->env->lwd, STDOUT_FILENO);
	return (g_sig);
}
