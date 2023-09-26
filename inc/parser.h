/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:38:36 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/08/30 12:35:45 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

//parcer_processor.c
t_list	*process_input(char **line, t_list *var_list, int *failed);

//helpers.c
void	delete_command(void *content, int parser);
// void	show_commands(t_list *commands);
// void	show_command(void *content);
void	ask_for_more(char **line);

//quotes.c
char	*single_quote_stage1(char *line, int check, int *failed);
char	*double_quote_stage1(char *line, int *failed);
void	remove_quotes(t_pars *content);

//stage1.c
char	*find_stage1_dividers(char *line, t_list **commands,
			int start, t_list *var_list);

//stage2.c
void	stage2_copy_line_part(void *command_content);

//stage3.c
void	stage3_var_handling(void *command_content);

//stage4.c
void	stage4_whiteline_remove(void *command_content);

//vars.c
t_list	*find_var(t_list *var_list, char *var_name);
t_var	*get_var(t_list *var_list, char *var_name);
int		set_var(t_list **var_list, char *var_name, \
			char *var_value, int replace_var_name);
void	extract_new_vars(void *command_content, int add_to_list);
void	find_and_delete(char *var_name, t_list **var_list);
void	delete_var(void *var_content);
int		setup_var_list(t_list **var_list);
int		export_var(t_list *var_list, char *var_name, int set_unset);
char	*extract_new_var(char *line, char **var_name, char **var_value);
int		copy_string(char *from, char *till, char **dst);
void	heredoc_var_replace(char **line, t_list *var_list);

#endif
