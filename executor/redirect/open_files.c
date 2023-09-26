/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_files.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 14:56:18 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 23:37:33 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_open_write(t_com *com, t_redirect_files *file)
{
	if (file->is_default)
		file->fd = open(file->s, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	else
		file->fd = open(file->s, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (file->fd < 0)
		return (do_file_error(com, file));
	return (0);
}

static int	do_open_read(t_com *com, t_redirect_files *file)
{
	file->fd = open(file->s, O_RDONLY, 0777);
	if (file->fd < 0)
		return (do_file_error(com, file));
	return (0);
}

int	do_files(t_com *com)
{
	t_redirect_files	*file;

	file = com->file;
	while (file)
	{
		if (file->is_read)
		{
			if (do_open_read(com, file))
				return (g_sig);
			if (com->read_fd != STDIN_FILENO)
				close(com->read_fd);
			com->read_fd = file->fd;
		}
		else
		{
			if (do_open_write(com, file))
				return (g_sig);
			if (com->write_fd != STDOUT_FILENO)
				close(com->write_fd);
			com->write_fd = file->fd;
		}
		file = file->next;
	}
	return (0);
}
