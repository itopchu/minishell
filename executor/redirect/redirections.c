/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 14:57:00 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/10 21:24:22 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_redirections(t_com *com)
{
	if (!isatty(com->read_fd) && com->read_fd != STDIN_FILENO)
	{
		if (dup2(com->read_fd, STDIN_FILENO) == -1)
		{
			close(com->read_fd);
			if (!isatty(com->write_fd))
				close(com->write_fd);
			return (error_exit("dup2", errno));
		}
		close(com->read_fd);
	}
	if (!isatty(com->write_fd) && com->write_fd != STDOUT_FILENO)
	{
		if (dup2(com->write_fd, STDOUT_FILENO) == -1)
		{
			close(com->write_fd);
			return (error_exit("dup2", errno));
		}
		close(com->write_fd);
	}
	return (0);
}

int	restore_default_std(t_env *env)
{
	if (isatty(STDIN_FILENO) == 0)
	{
		if (dup2(env->default_std[0], STDIN_FILENO) == -1)
		{
			env->end = 1;
			return (error_exit("dup2", errno));
		}
	}
	if (isatty(STDOUT_FILENO) == 0)
	{
		if (dup2(env->default_std[1], STDOUT_FILENO) == -1)
		{
			env->end = 1;
			return (error_exit("dup2", errno));
		}
	}
	return (g_sig);
}
