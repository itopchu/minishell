/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/08 01:57:35 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/08 01:57:35 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// # define SHOW_PARS_OUTPUT 0
// # define SHOW_PARS_INFO 0
// # define ECHO_INPUT 0
// # define SHOW_ENVPP 0
# define STAGE1DIVIDERS "|><"
# define VAR_CLOSERS " \"$"
# define VAR_ENDERS " \"'$"
# define WHITELINES " "
# define QUOTES "'\""
# define IGNORE 5
# define HEREDOC 4
# define PARENT 3
# define CHILD 2
# define MAIN 1
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include "enum.h"
# include "executor/builtins.h"
# include "executor/exec.h"
# include "executor/executable.h"
# include "executor/path.h"
# include "executor/redirect.h"
# include "executor/tools.h"
# include "env_tools/env_tools.h"
# include "parser.h"
# include "parent.h"
#endif