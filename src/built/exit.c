/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:32:19 by aagathe           #+#    #+#             */
/*   Updated: 2023/09/30 16:45:03 by aumarin          ###   ########.fr       */
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

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	print_exit_msg(t_cmd *cmds)
{
	ft_putstr_fd("minishell: ft_exit: ", 2);
	ft_putstr_fd(cmds->cmd[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	ft_exit(t_cmd *cmds, int pfd[4])
{
	int	exit_code;

	exit_code = 0;
	if (!pfd)
		write(2, "exit\n", 5);
	if (cmds->cmd[1])
	{
		if (check_num(cmds->cmd[1]))
		{
			if (cmds->cmd[2])
			{
				ft_putendl_fd("minishell: ft_exit: too many arguments", 2);
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
	free_commands(cmds);
	exit(exit_code);
}
