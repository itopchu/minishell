/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_envp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 15:05:35 by itopchu       #+#    #+#                 */
/*   Updated: 2023/09/05 15:05:35 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	show_envpp(char **envpp_edited)
// {
// 	if (SHOW_ENVPP && envpp_edited)
// 	{
// 		ft_printf("\n\nSHOWING ENVPP:\n");
// 		while (*envpp_edited)
// 			ft_printf("%s\n", *envpp_edited++);
// 	}
// }

int	do_update_exitmark(t_list *var_list)
{
	char	*itoa;
	t_var	*var;

	itoa = ft_itoa(g_sig);
	if (!itoa)
		return (error_exit("malloc", errno));
	if (!set_var(&var_list, "?", itoa, 0))
		return (error_exit("malloc", errno));
	var = get_var(var_list, "?");
	if (var)
		var->export = 0;
	return (0);
}

static int	build_envp(t_env *env, size_t size)
{
	t_list	*cur;
	size_t	i;

	do_envp_clean(env);
	env->envp = ft_calloc(size + 1, sizeof(char *));
	if (!env->envp)
		return (error_exit("malloc", errno));
	cur = env->var_list;
	i = 0;
	while (cur)
	{
		if (((t_var *)cur->content)->export
			&& ((t_var *)cur->content)->var_value)
			env->envp[i++] = ((t_var *)cur->content)->combined;
		cur = cur->next;
	}
	return (0);
}

int	make_envp(t_env *env)
{
	t_list	*cur;
	size_t	size;
	t_var	*content;

	cur = env->var_list;
	size = 0;
	while (cur)
	{
		content = (t_var *)cur->content;
		if (content && content->export)
			size++;
		cur = cur->next;
	}
	if (build_envp(env, size))
		return (errno);
	return (0);
}
