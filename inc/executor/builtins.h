/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 17:36:51 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/11 17:36:51 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// ╔════════════════════════════════════════════════════════════════════════╗
// ║					.c files in executor/builtins folder				║
// ╚════════════════════════════════════════════════════════════════════════╝
// ╭────────────────────────────────────╮
// │                cd.c                │
// ╰────────────────────────────────────╯
/*main execution function for cd builtin*/
int		execute_cd(t_com *com);
// ╭────────────────────────────────────╮
// │               echo.c               │
// ╰────────────────────────────────────╯
/*main execution function for echo builtin*/
int		execute_echo(t_com *com);
// ╭────────────────────────────────────╮
// │                env.c               │
// ╰────────────────────────────────────╯
int		execute_env(t_com *com);
// ╭────────────────────────────────────╮
// │               exit.c               │
// ╰────────────────────────────────────╯
/*main execution function for exit builtin*/
int		execute_exit(t_com *com);
// ╭────────────────────────────────────╮
// │              export.c              │
// ╰────────────────────────────────────╯
/*Validity check for env variables*/
int		do_check_validity(char *s);
/*main execution function for export builtin*/
int		execute_export(t_com *com);
// ╭────────────────────────────────────╮
// │                pwd.c               │
// ╰────────────────────────────────────╯
/*main execution function for pwd builtin*/
int		execute_pwd(t_com *com);
// ╭────────────────────────────────────╮
// │               unset.c              │
// ╰────────────────────────────────────╯
/*removes all given parameters from envp*/
int		execute_unset(t_com *com);
#endif