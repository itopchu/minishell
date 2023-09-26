/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 15:29:17 by itopchu       #+#    #+#                 */
/*   Updated: 2023/08/26 15:29:17 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_mult_sum(long long *val, int add)
{
	long long	tmp;
	int			i;

	i = 0;
	tmp = *val;
	while (++i < 10)
	{
		*val += tmp;
		if ((tmp > 0 && *val < 0) || \
			(tmp < 0 && *val > 0))
			return (2);
	}
	*val += add;
	if ((add > 0 && *val < 0) || \
		(add < 0 && *val > 0))
		return (2);
	return (0);
}

static int	to_long(char *s, long long *val)
{
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	*val = (s[i] - '0') * sign;
	while (s[++i])
	{
		if (do_mult_sum(val, (s[i] - '0') * sign))
			return (2);
	}
	return (0);
}

static int	get_exit(t_com *com, char *s)
{
	long long	val;

	val = 0;
	if (to_long(s, &val))
		return (failure_cond("exit", com->args[1], \
			"numeric argument required", 255));
	val = val % 256;
	if (val < 0)
		val += 256;
	return ((int)val);
}

static int	is_all_digit(char *s)
{
	int	i;

	if (s[0] == '\0')
		return (-1);
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (-1);
	while (ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (-1);
	return (i);
}

int	execute_exit(t_com *com)
{
	int	len;

	g_sig = com->env->spare_exit;
	com->env->end = 1;
	if (!com->args[1])
		return (g_sig);
	len = is_all_digit(com->args[1]);
	if (len == -1)
		return (failure_cond("exit", com->args[1], \
			"numeric argument required", 255));
	else if (len != 0)
	{
		if (com->args[2])
			return (failure_cond("exit", NULL, "too many arguments", 1));
		else
			return (get_exit(com, com->args[1]));
	}
	return (g_sig);
}
