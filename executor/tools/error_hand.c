/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_hand.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 15:00:41 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/28 17:41:02 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	failure_cond(char *type, char *command, char *error, int ret)
{
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	if (type)
	{
		ft_putstr_fd(type, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (command)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(error, STDERR_FILENO);
	g_sig = ret;
	errno = ret;
	return (ret);
}

int	error_exit(char *s, int ret)
{
	g_sig = ret;
	errno = g_sig;
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	perror(s);
	return (ret);
}

int	do_exec_error(t_pipe_helper *help, char *message)
{
	do_close_helper(help);
	while (wait(NULL) != -1)
		;
	return (error_exit(message, errno));
}

int	do_file_error(t_com *com, t_redirect_files *file)
{
	if (com->read_fd != STDIN_FILENO)
		close(com->read_fd);
	if (com->write_fd != STDOUT_FILENO)
		close(com->write_fd);
	com->read_fd = 0;
	com->write_fd = 1;
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	perror(file->s);
	g_sig = 1;
	return (g_sig);
}
