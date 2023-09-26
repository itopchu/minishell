/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 11:00:24 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 21:32:45 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARENT_H
# define PARENT_H
# include "minishell.h"

//main.c
// void	check_leaks(void);

//chech_commands.c
int		check_command(t_env *env);

//readline_loop.c
char	*input_loop(int *end);
t_com	*get_input(t_list *var_list, int *end, t_env *env, int *failed);
void	free_commands_list(t_list *commands, int del_premature);

//env_keeper.c
int		add_envpp_to_var_list(t_list *var_list, char **envpp);

//commands_build.c
t_com	*build_command_structs(t_list *commands);
t_com	*clear_command_structs(t_com *command_structs);
void	delete_command_struct(t_com *command_structs, int transfer);
void	fill_command_option_rest(t_com *commands_structs);

//file, file2.c and file3
char	**count_n_parts(int n_parts, t_com *commands_structs,
			t_com *prev_command_struct);
int		add_part_to_prev(t_com *commands_structs, t_com *prev_command_struct);
int		add_file_data(t_com *commands_structs, \
			t_com *prev_command_struct, t_env *env, int *failed);
int		add_read_file(t_com *commands_structs, t_com *prev_command_struct);
int		add_heredoc(t_com *commands_structs, \
			t_com *prev_command_struct, t_env *env, int *failed);
int		add_append_write_file(t_com *commands_structs, \
			t_com *prev_command_struct);
int		add_write_file(t_com *commands_structs, t_com *prev_command_struct);
int		add_file(t_com *com_structs, t_com *prev_com_structs, \
		int read, int is_def);

#endif
