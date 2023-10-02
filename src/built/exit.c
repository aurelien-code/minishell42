/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:32:19 by aagathe           #+#    #+#             */
/*   Updated: 2023/10/02 18:49:55 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_atoi(char *str)
{
	int	nb;

	nb = ft_atoi(str);
	return ((unsigned char) nb);
}

static int	check_num(char *str)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v')
		str++;
	if ((str[i] == '-' && ++neg) || str[i] == '+')
		str++;
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v')
		str++;
	if (str[i])
		return (0);
	if (i > 19
		|| (!neg && i == 19 && ft_strncmp(str, "9223372036854775807", 19) > 0)
		|| (neg && i == 19 && ft_strncmp(str, "9223372036854775808", 19) > 0))
		return (0);
	return (1);
}

void	print_exit_msg(t_cmd *cmds)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmds->cmd[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	ft_exit(t_cmd *cmds, char **cpy_env, int fork)
{
	int	exit_code;

	exit_code = 0;
	if (!fork)
		write(2, "exit\n", 5);
	if (cmds->cmd[1])
	{
		if (check_num(cmds->cmd[1]))
		{
			if (cmds->cmd[2])
			{
				ft_putendl_fd("minishell: exit: too many arguments", 2);
				return (1);
			}
			else
				exit_code = exit_atoi(cmds->cmd[1]);
		}
		else
		{
			print_exit_msg(cmds);
			exit_code = 2;
		}
	}
	ft_free_cpy_env(cpy_env);
	free_commands(cmds);
	exit(exit_code);
}
