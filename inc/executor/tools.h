/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 17:16:17 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/11 17:16:17 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "minishell.h"

// ╔════════════════════════════════════════════════════════════════════════╗
// ║					.c files in executor/tools folder					║
// ╚════════════════════════════════════════════════════════════════════════╝
// ╭────────────────────────────────────╮
// │             do_free.c              │
// ╰────────────────────────────────────╯
/*protected free function and sets to NULL*/
void	do_free(char **var);
// ╭────────────────────────────────────╮
// │            error_hand.c            │
// ╰────────────────────────────────────╯
/*prints failure for unwanted inputs and updates errno and returns errno*/
int		failure_cond(char *type, char *command, char *error, int ret);
/*prints error message for systemcalls sets exit value to errno
if "ret" is 0 will return 0*/
int		error_exit(char *s, int ret);
/*incase of failure in exec_multi function this function is called
to close FD's and collect child processes*/
int		do_exec_error(t_pipe_helper *help, char *message);
/*Error case for redirections.c functions*/
int		do_file_error(t_com *com, t_redirect_files *file);
// ╭────────────────────────────────────╮
// │              signal.c              │
// ╰────────────────────────────────────╯
/*
signal handler for given mode 
MAIN
CHILD
PARENT
*/
void	do_sig(int mode);
// ╭────────────────────────────────────╮
// │               var.c                │
// ╰────────────────────────────────────╯
/*Used to create arg array for execve*/
int		do_add_arg(char ***arg, char **line);
/*Instead of looking for \0 looks for given int value of char*/
int		do_strlen_var(char *s, int var);
/*converts given string to exportable var*/
int		do_extract_var(char *s, char **name, char **value);
/*returns a pointer to asked var else NULL*/
t_var	*do_get_var(t_list *list, char *s);
// ╭────────────────────────────────────╮
// │             do_uatoi.c             │
// ╰────────────────────────────────────╯
/*converts given string to 0 >= return < INT_MAX*/
int		do_uatoi(char *s);
#endif