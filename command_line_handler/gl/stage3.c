/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stage3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzeeuw-v <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:20 by jzeeuw-v      #+#    #+#                 */
/*   Updated: 2023/07/27 16:39:21 by jzeeuw-v      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_norm_struct
{
	char	*line;
	char	**org_line;
	t_list	*var_list;
}				t_norm_struct;

int	replace_var(char *line, char *var, char *var_end, t_norm_struct *content)
{
	char	*new_line;
	size_t	new_str_len;
	t_list	*var_struct;
	int		offset;

	var_struct = find_var(content->var_list, var);
	if (var_struct)
		var = ((t_var *)var_struct->content)->var_value;
	else
		var = "";
	new_str_len = (line - *content->org_line) + ft_strlen(var_end) + 1;
	if (var)
		new_str_len += ft_strlen(var);
	new_line = ft_calloc(new_str_len, sizeof(char));
	if (!new_line)
		return (0);
	ft_strlcpy(new_line, *content->org_line, (line - *content->org_line));
	if (var)
		ft_strlcat(new_line, var, new_str_len);
	ft_strlcat(new_line, var_end, new_str_len);
	offset = (line - content->line) + ft_strlen(var) - 1;
	free(*content->org_line);
	*content->org_line = new_line;
	content->line = new_line + offset;
	return (1);
}

int	isolate_and_replace_var(char *line, t_norm_struct *content)
{
	int		var_size;
	int		return_code;
	char	*var;
	char	*var_end;

	var_end = line;
	if (!(*var_end == '?') && (ft_isalpha(*var_end) || *var_end == '_'))
		while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
			var_end++;
	else
		var_end++;
	var_size = var_end - line + 1;
	var = ft_calloc(var_size, sizeof(char));
	if (!var)
		return (0);
	ft_strlcpy(var, line, var_size);
	return_code = replace_var(line, var, var_end, content);
	free(var);
	return (return_code);
}

int	search_and_replace_vars(t_norm_struct *content, int double_quoted, \
	char *line, char *bcp_line)
{
	while (line && *line)
	{
		if (*line == '"' && double_quoted != -2)
			double_quoted = (double_quoted % 2) + 1;
		if (*line == '$')
		{
			if (*(line + 1) && (ft_isalnum(*(line + 1)) || \
				*(line + 1) == '_' || *(line + 1) == '?'))
			{
				if (!isolate_and_replace_var(line + 1, content))
					return (0);
				else
					return (search_and_replace_vars(content, double_quoted,
							content->line, 0));
			}
		}
		bcp_line = line;
		if (!(double_quoted % 2))
			bcp_line = single_quote_stage1(line, 0, 0);
		if (bcp_line == line && line && *line)
			line++;
		else if (line && *line)
			line = bcp_line;
	}
	return (1);
}

void	heredoc_var_replace(char **line, t_list *var_list)
{
	t_norm_struct	norm_content;

	norm_content.line = 0;
	if (line)
		norm_content.line = *line;
	norm_content.org_line = line;
	norm_content.var_list = var_list;
	search_and_replace_vars(&norm_content, -2, norm_content.line, NULL);
}

void	stage3_var_handling(void *command_content)
{
	t_pars			*content;
	t_norm_struct	norm_content;

	content = (t_pars *)command_content;
	norm_content.line = content->command_copy;
	norm_content.org_line = &content->command_copy;
	norm_content.var_list = content->var_list;
	search_and_replace_vars(&norm_content, 0, norm_content.line, NULL);
}
