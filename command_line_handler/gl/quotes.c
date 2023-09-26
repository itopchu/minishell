/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:38:48 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 16:38:50 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*single_quote_stage1(char *line, int check, int *failed)
{
	char	*start_line;

	start_line = line + 1;
	if (*line == *"'")
	{
		line++;
		while (*line != *"'")
		{
			if (!*line)
			{
				if (check)
				{
					if (failed)
						*failed = 1;
					return (line);
				}
				else
					return (start_line);
			}
			line++;
		}
		line++;
	}
	return (line);
}

char	*double_quote_stage1(char *line, int *failed)
{
	char	*start_line;

	start_line = line + 1;
	if (*line == '"')
	{
		line++;
		while (*line != '"')
		{
			if (!*line)
			{
				if (failed)
				{
					*failed = 1;
					return (line);
				}
				else
					return (start_line);
			}
			line++;
		}
		line++;
	}
	return (line);
}

int	remove_quotes_norm(int i, char **strs, char quote)
{
	ft_memmove(*strs + i, *strs + i + 1, ft_strlen(*strs + i));
	while (*(*strs + i) != quote && *(*strs + i))
		i++;
	ft_memmove(*strs + i, *strs + i + 1, ft_strlen(*strs + i));
	return (i);
}

void	remove_quotes(t_pars *content)
{
	int		i;
	char	**strs;

	if (!content)
		return ;
	strs = content->command_parts;
	while (strs && *strs)
	{
		i = 0;
		while (!ft_strchr(WHITELINES, *(*strs + i)) && *(*strs + i))
		{
			if (*(*strs + i) == '\'')
				i = remove_quotes_norm(i, strs, '\'');
			else if (*(*strs + i) == '\"')
				i = remove_quotes_norm(i, strs, '\"');
			else
				i++;
		}
		strs++;
	}
}
