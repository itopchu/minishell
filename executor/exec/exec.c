/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 16:28:29 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 16:28:29 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_single(t_com *com)
{
	t_ExecutionFunc	func;

	com->env->spare_exit = g_sig;
	g_sig = 0;
	if (do_files(com))
		return (restore_default_std(com->env));
	if (do_redirections(com))
		return (restore_default_std(com->env));
	if (!com->args || !com->args[0])
		return (restore_default_std(com->env));
	func = get_execution_func(com->args[0]);
	if (func)
		g_sig = func(com);
	return (restore_default_std(com->env));
}

static int	get_last_return(pid_t last)
{
	int		status;
	pid_t	ret;

	ret = waitpid(last, &status, 0);
	while (wait(NULL) != -1)
		;
	if (ret == -1)
		error_exit("waitpid", errno);
	if (WIFEXITED(ret))
		g_sig = WEXITSTATUS(ret);
	else if (WIFSIGNALED(ret))
		g_sig = WTERMSIG(ret) + 128;
	return (g_sig);
}

static int	exec_multi(t_env *e)
{
	t_pipe_helper	help;
	t_com			*tmp;
	pid_t			pid;
	pid_t			last_pid;

	do_helper_assign(&help);
	tmp = e->command;
	last_pid = -1;
	while (tmp)
	{
		if (tmp->next)
			if (pipe(help.curr) < 0)
				return (do_exec_error(&help, "pipe"));
		pid = fork();
		last_pid = pid;
		if (pid < 0)
			return (do_exec_error(&help, "fork"));
		else if (pid == 0)
			exit(do_child_process(tmp, &help));
		do_helper_update(&help);
		tmp = tmp->next;
	}
	do_close_helper(&help);
	return (get_last_return(last_pid));
}

static void	do_assign_basics(t_env *e)
{
	t_com	*tmp;

	tmp = e->command;
	do_sig(PARENT);
	while (tmp)
	{
		if (tmp->pars->command_parts)
			tmp->args = tmp->pars->command_parts;
		tmp->write_fd = STDOUT_FILENO;
		tmp->read_fd = STDIN_FILENO;
		tmp->is_child = 0;
		tmp->env = e;
		tmp = tmp->next;
	}
}

void	executor(t_env *e)
{
	struct termios	attributes;

	if (!e->command)
		return ;
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~(ECHOCTL);
	do_assign_basics(e);
	if (e->command->next)
		g_sig = exec_multi(e);
	else
		g_sig = exec_single(e->command);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}
