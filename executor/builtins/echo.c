/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 15:38:04 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 15:38:04 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_check_ommit(t_com *com, int *i)
{
	int	ret;
	int	j;

	ret = 0;
	while (com->args[++(*i)])
	{
		j = 0;
		if (com->args[*i][j] == '-' && com->args[*i][j + 1] == 'n')
		{
			while (com->args[*i][++j] == 'n')
				;
			if (!com->args[*i][j])
				ret = 1;
			else
				break ;
		}
		else
			break ;
	}
	return (ret);
}

int	execute_echo(t_com *com)
{
	int		ommit;
	int		i;

	i = 0;
	ommit = do_check_ommit(com, &i);
	while (com->args[i])
	{
		ft_putstr_fd(com->args[i], STDOUT_FILENO);
		if (com->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!ommit)
		write(STDOUT_FILENO, "\n", 1);
	return (g_sig);
}
