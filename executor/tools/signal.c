/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 15:03:15 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/08 02:01:39 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

static void	do_sig_c(int mode)
{
	if (mode == SIGINT)
	{
		g_sig = 130;
		printf("minishell$ %s\n", rl_line_buffer);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	do_sig_heredoc(int mode)
{
	if (mode == SIGINT)
	{
		g_sig = 1;
		printf("> %s\n", rl_line_buffer);
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(g_sig);
	}
}

void	do_sig(int mode)
{
	if (mode == MAIN)
	{
		signal(SIGINT, do_sig_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, do_sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
