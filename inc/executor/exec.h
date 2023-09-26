/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 17:00:19 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/11 17:00:19 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// ╔════════════════════════════════════════════════════════════════════════╗
// ║					.c files in executor/exec folder					║
// ╚════════════════════════════════════════════════════════════════════════╝
// ╭────────────────────────────────────╮
// │            exec_helper.c           │
// ╰────────────────────────────────────╯
/*Function shortener: basic -1 assignment for helper*/
void			do_helper_assign(t_pipe_helper *helper);
/*Closes remaining pipes*/
void			do_close_helper(t_pipe_helper *helper);
/*Closes and replaces prev and current pipe*/
void			do_helper_update(t_pipe_helper *helper);
/*Function shortener: sets is_child does pipe with dup2*/
int				do_child_process(t_com *com, t_pipe_helper *helper);
/*gives the builtin if so otherwise will give executable*/
t_ExecutionFunc	get_execution_func(char *com);
// ╭────────────────────────────────────╮
// │               exec.c               │
// ╰────────────────────────────────────╯
/*every command is run by this function*/
int				exec_single(t_com *com);
/*main function to step into the execution part*/
void			executor(t_env *e);
// ╭────────────────────────────────────╮
// │        exec_expand_helper.c        │
// ╰────────────────────────────────────╯
#endif