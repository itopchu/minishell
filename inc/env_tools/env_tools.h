/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_tools.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 11:24:40 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/05 11:24:40 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TOOLS_H
# define ENV_TOOLS_H

# include "minishell.h"

// ╔════════════════════════════════════════════════════════════════════════╗
// ║					.c files in env_tools folder						║
// ╚════════════════════════════════════════════════════════════════════════╝
// ╭────────────────────────────────────╮
// │           command_clean.c          │
// ╰────────────────────────────────────╯
/*cleans the file structs of given command*/
void				do_file_clean(t_com *com);
/*cleans the pars structs of given command*/
void				do_pars_clean(t_com *com);
/*cleans the command structs of given env*/
void				do_command_clean(t_env *env);
// ╭────────────────────────────────────╮
// │             env_clean.c            │
// ╰────────────────────────────────────╯
/*cleans char **envp from given env*/
void				do_envp_clean(t_env *env);
/*cleans var_list of given env*/
void				do_var_clean(t_env *env);
/*unlinks here_doc files*/
void				do_heredoc_clean(t_env *env);
/*cleans given env*/
void				do_env_clean(t_env *env);
// ╭────────────────────────────────────╮
// │             env_init.c             │
// ╰────────────────────────────────────╯
/*inits spare file descriptors in env*/
int					init_default_std(t_env *env);
/*inits env for start*/
int					init_env(t_env *env, char **envp);
// ╭────────────────────────────────────╮
// │             make_envp.c            │
// ╰────────────────────────────────────╯
/*Updates exit status after readline is done for $?*/
int					do_update_exitmark(t_list *var_list);
/*reinits envp depending on t_var list*/
int					make_envp(t_env *env);
#endif