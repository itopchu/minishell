/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 15:29:41 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 15:29:41 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(t_com *com)
{
	int	i;

	i = -1;
	while (com->env->envp[++i])
		ft_putendl_fd(com->env->envp[i], STDOUT_FILENO);
	return (g_sig);
}
