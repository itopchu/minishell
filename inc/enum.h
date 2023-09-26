/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enum.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/08 01:57:53 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/08 01:57:53 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H
# include "minishell.h"

extern int	g_sig;

typedef struct s_pars
{
	int		start;
	char	start_stage1_divider;
	char	end_stage1_divider;
	char	*start_line;
	char	*end_line;
	char	*command_line;
	char	*command_copy;
	char	**command_parts;
	t_list	*var_list;
}				t_pars;

typedef struct s_var
{
	char	*var_name;
	char	*var_value;
	char	*combined;
	int		export;
}				t_var;

typedef struct s_env
{
	int					default_std[2];
	int					end;
	int					spare_exit;
	int					heredoc_n;
	struct s_com		*command;
	char				*lwd;
	char				**envp;
	t_list				*var_list;
}	t_env;

typedef struct s_redirect_files
{
	char					*delimiter;
	int						is_read;
	int						is_default;
	int						fd;
	char					*s;
	struct s_redirect_files	*next;
	int						heredoc_no_expand;
}	t_redirect_files;

typedef struct s_pipe_helper
{
	int	curr[2];
	int	old_in;
}	t_pipe_helper;

typedef struct s_com
{
	int					is_child;
	t_env				*env;
	t_redirect_files	*file;
	int					write_fd;
	int					read_fd;
	char				**args;
	struct s_com		*next;
	struct s_pars		*pars;
	char				*command;
}	t_com;

typedef int	(*t_ExecutionFunc)(t_com*);

#endif