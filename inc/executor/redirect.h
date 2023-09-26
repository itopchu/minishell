/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 17:24:39 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/11 17:24:39 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

// ╔════════════════════════════════════════════════════════════════════════╗
// ║					.c files in executor/redirect folder				║
// ╚════════════════════════════════════════════════════════════════════════╝
// ╭────────────────────────────────────╮
// │             here_doc.c             │
// ╰────────────────────────────────────╯
/*reads in to pipe to use later in childs
if SIGINT returns SIGINT else 0*/
int		do_here_doc(t_env *env, t_redirect_files *file);
char	*heredoc_name(int file_number);
// ╭────────────────────────────────────╮
// │            open_files.c            │
// ╰────────────────────────────────────╯
/*opens given files before execution*/
int		do_files(t_com *com);
// ╭────────────────────────────────────╮
// │           redirections.c           │
// ╰────────────────────────────────────╯
/*dup2's read_fd and write_fd in command execution*/
int		do_redirections(t_com *com);
/*if STDIN or STDOUT is not a terminal
will set back to reserved default_std in env struct saved*/
int		restore_default_std(t_env *env);

#endif