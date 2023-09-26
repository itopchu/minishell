/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 14:54:32 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/06 00:54:32 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HDC_D "/tmp/heredoc_buffer_buzzers2_minishell"

extern int	g_sig;

char	*heredoc_name(int file_number)
{
	int		str_len;
	char	*number;
	char	*file_name;

	number = ft_itoa(file_number);
	if (!number)
		return (0);
	str_len = ft_strlen(number) + ft_strlen(HDC_D) + 1;
	file_name = ft_calloc(str_len, sizeof(char));
	if (file_name)
	{
		ft_strlcat(file_name, HDC_D, str_len);
		ft_strlcat(file_name, number, str_len);
	}
	free(number);
	return (file_name);
}

int	norm_set_file(t_env *env, t_redirect_files *file)
{
	int	fd;

	while (file->next)
		file = file->next;
	if (file->s)
		free(file->s);
	file->s = heredoc_name(env->heredoc_n);
	if (!file->s)
		return (-1);
	env->heredoc_n++;
	file->is_read = 1;
	file->is_default = 0;
	fd = open(file->s, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	return (fd);
}

int	do_here_doc_child(t_env *env, t_redirect_files *file,
	int fd, size_t len_delimmeter)
{
	char	*line;

	line = readline("> ");
	if (!file->heredoc_no_expand)
		heredoc_var_replace(&line, env->var_list);
	while (line && (ft_strcmp(file->delimiter, line)
			|| ft_strlen(line) != len_delimmeter))
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
		if (!file->heredoc_no_expand)
			heredoc_var_replace(&line, env->var_list);
	}
	if (line)
		free(line);
	do_env_clean(env);
	g_sig = 0;
	exit(0);
}

int	do_here_doc(t_env *env, t_redirect_files *file)
{
	pid_t	pid;
	int		fd;
	size_t	len_delimmeter;
	int		status;

	do_sig(IGNORE);
	fd = norm_set_file(env, file);
	if (fd == -1)
		return (0);
	len_delimmeter = 0;
	if (file->delimiter)
		len_delimmeter = ft_strlen(file->delimiter);
	pid = fork();
	if (!pid)
	{
		do_sig(HEREDOC);
		do_here_doc_child(env, file, fd, len_delimmeter);
	}
	waitpid(pid, &status, 0);
	close(fd);
	if ((status & 0x7f) == 0)
		g_sig = (status >> 8) & 0xff;
	do_sig(MAIN);
	return (!status);
}
