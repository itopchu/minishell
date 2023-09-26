/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 23:54:35 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/01 23:54:35 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "minishell.h"

// ╔════════════════════════════════════════════════════════════════════════╗
// ║					.c files in executor/path folder					║
// ╚════════════════════════════════════════════════════════════════════════╝
// ╭────────────────────────────────────╮
// │            get_cd_path.c           │
// ╰────────────────────────────────────╯
/*Function to resolve and check accessability of the directory to change*/
int		get_cd_path(t_com *com, char **buf);
// ╭────────────────────────────────────╮
// │           get_exec_path.c          │
// ╰────────────────────────────────────╯
/*Function to resolve and check accessability of the exec to run*/
int		get_exec_path(t_com *com, char **buf);
// ╭────────────────────────────────────╮
// │           get_path_path.c          │
// ╰────────────────────────────────────╯
/*function to receive path based executable if exists*/
int		get_path_path(t_com *com, char *s, char **buf);
// ╭────────────────────────────────────╮
// │            helper_path.c           │
// ╰────────────────────────────────────╯
/*appends left string with connector and right part of the string*/
int		append_with_con(char **left, char connector, char *right);
/*function to resolve given arg and return if it exist*/
int		do_resolve(t_com *com, char **buf, int arg_ind);
#endif