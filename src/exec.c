/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:45:06 by ypages            #+#    #+#             */
/*   Updated: 2023/04/26 09:56:06 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_value(t_line *line)
{
	if (line->next)
		return (line->next->value);
	else
		return (NULL);
}

int	ft_exec(t_line *line)
{
	if (!line)
		return (NOK);
	while (line)
	{
		if (line->type == BUILTIN)
		{
			if (!ft_strncmp(line->value, "cd", ft_strlen(line->value)))
				ft_cd(get_next_value(line));
			else if (!ft_strncmp(line->value, "pwd", ft_strlen(line->value)))
				ft_pwd();
			else if (!ft_strncmp(line->value, "echo", ft_strlen(line->value)))
				ft_echo(line->next->value, 0);
			else if (!ft_strncmp(line->value, "env", ft_strlen(line->value)))
				break ;
			else if (!ft_strncmp(line->value, "export", ft_strlen(line->value)))
				break ;
			else if (!ft_strncmp(line->value, "unset", ft_strlen(line->value)))
				break ;
			else
				perror("minishell: command not found");
		}
		line = line->next;
	}
	return (OK);
}
