/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/05 03:30:21 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/05 03:30:21 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

/* in command_line_handler/parent.h there are flags
to give debugging information if wanted. defined 0 or 1 */
// void	check_leaks(void)
// {
// 	char	*int_pid;
// 	char	pid[30];

// 	ft_strlcpy(pid, "leaks ", 30);
// 	int_pid = ft_itoa(getpid());
// 	ft_strlcat(pid, int_pid, 30);
// 	free(int_pid);
// 	system(pid);
// }

int	parse_input(t_env *env, int *failed)
{
	*failed = 0;
	do_heredoc_clean(env);
	do_command_clean(env);
	env->command = get_input(env->var_list, &env->end, env, failed);
	if (make_envp(env))
	{
		*failed = 1;
		return (!(*failed));
	}
	if (!*failed)
		*failed = check_command(env);
	if (*failed == 2)
		g_sig = failure_cond(NULL, NULL, "parser error", 258);
	return (!(*failed));
}

int	add_underscore(t_com *command_structs, t_env *env)
{
	char	**str;
	char	*var_value;
	char	*var_name;

	if (!command_structs || command_structs->next)
		return (1);
	str = command_structs->pars->command_parts;
	if (!str || !*str)
		return (1);
	while (*str)
		str++;
	str--;
	var_value = ft_strdup(*str);
	if (!var_value)
		return (0);
	var_name = ft_strdup("_");
	if (!var_name)
		return (free(var_value), 0);
	if (!set_var(&env->var_list, var_name, var_value, 1))
		return (1);
	get_var(env->var_list, var_name)->export = 1;
	return (1);
}

int	main(int ac, char **av, char **envpp)
{
	t_env	env;
	int		failed;

	if (ac != 1 || av[1])
		return (failure_cond("input", "command substitution", \
			"not supported", 127));
	if (init_env(&env, envpp))
		return (errno);
	while (!env.end)
	{
		do_sig(MAIN);
		if (!parse_input(&env, &failed) && !failed)
			break ;
		if (!failed)
			executor(&env);
		add_underscore(env.command, &env);
	}
	do_env_clean(&env);
	return (g_sig % 256);
}
