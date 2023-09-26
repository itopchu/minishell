/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 15:05:44 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/02 00:06:18 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prepare_args(char *s, t_com *com, char ***args)
{
	char	*command;
	char	*tmp;
	int		i;

	command = ft_strdup(s);
	if (!command || do_add_arg(args, &command))
		return (do_free(&command), error_exit("malloc", errno));
	i = 0;
	while (com->args[++i])
	{
		tmp = ft_strdup(com->args[i]);
		if (!tmp || do_add_arg(args, &tmp))
			return (do_free(&command), error_exit("malloc", errno));
	}
	return (0);
}

static int	ft_run(t_com *com)
{
	char	**args;
	char	*path;

	do_sig(CHILD);
	path = NULL;
	if (get_exec_path(com, &path))
		return (g_sig);
	args = malloc(sizeof(char *));
	if (!args)
		return (do_free(&path), error_exit("malloc", errno));
	args[0] = NULL;
	if (prepare_args(path, com, &args))
		return (ft_free2m(args), do_free(&path), errno);
	execve(path, args, com->env->envp);
	error_exit("execve", errno);
	return (ft_free2m(args), do_free(&path), errno);
}

int	execute_exe(t_com *com)
{
	pid_t	pid;
	int		status;

	if (!com)
		return (0);
	if (com->is_child)
		exit(ft_run(com));
	pid = fork();
	if (pid == -1)
		return (error_exit("fork", errno));
	if (pid == 0)
		exit(ft_run(com));
	do_sig(PARENT);
	if (waitpid(pid, &status, 0) == -1)
		return (error_exit("waitpid", errno));
	if ((status & 0x7f) == 0)
		g_sig = (status >> 8) & 0xff;
	return (g_sig);
}
