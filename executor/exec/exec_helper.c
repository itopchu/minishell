/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_helper.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 16:21:18 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 16:21:18 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_helper_assign(t_pipe_helper *helper)
{
	helper->curr[0] = -1;
	helper->curr[1] = -1;
	helper->old_in = -1;
}

void	do_close_helper(t_pipe_helper *helper)
{
	if (helper->curr[0] != -1)
		close(helper->curr[0]);
	helper->curr[0] = -1;
	if (helper->curr[1] != -1)
		close(helper->curr[1]);
	helper->curr[1] = -1;
	if (helper->old_in != -1)
		close(helper->old_in);
	helper->old_in = -1;
}

void	do_helper_update(t_pipe_helper *helper)
{
	if (helper->curr[1] != -1)
		close(helper->curr[1]);
	if (helper->old_in != -1)
		close(helper->old_in);
	helper->old_in = helper->curr[0];
	helper->curr[0] = -1;
	helper->curr[1] = -1;
}

int	do_child_process(t_com *com, t_pipe_helper *helper)
{
	do_sig(CHILD);
	com->is_child = 1;
	if (helper->curr[0] != -1)
		close(helper->curr[0]);
	helper->curr[0] = -1;
	if (helper->old_in != -1)
	{
		if (dup2(helper->old_in, STDIN_FILENO) == -1)
			return (do_exec_error(helper, "dup2"));
		close(helper->old_in);
	}
	if (helper->curr[1] != -1)
	{
		if (dup2(helper->curr[1], STDOUT_FILENO) == -1)
			return (do_exec_error(helper, "dup2"));
		close(helper->curr[1]);
	}
	return (exec_single(com));
}

t_ExecutionFunc	get_execution_func(char *com)
{
	if (!com || !com[0])
		return (NULL);
	if (!ft_strcmp(com, "echo"))
		return (execute_echo);
	else if (!ft_strcmp(com, "cd"))
		return (execute_cd);
	else if (!ft_strcmp(com, "pwd"))
		return (execute_pwd);
	else if (!ft_strcmp(com, "exit"))
		return (execute_exit);
	else if (!ft_strcmp(com, "env"))
		return (execute_env);
	else if (!ft_strcmp(com, "unset"))
		return (execute_unset);
	else if (!ft_strcmp(com, "export"))
		return (execute_export);
	return (execute_exe);
}
