/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:45:06 by ypages            #+#    #+#             */
/*   Updated: 2023/04/27 13:34:09 by aumarin          ###   ########.fr       */
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

t_env	*ft_exec(t_line *line, t_env *env)
{
	if (!line)
		return (NULL);
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
				ft_env(env);
			else if (!ft_strncmp(line->value, "export", ft_strlen(line->value)))
				ft_export(env, line->next->value);
			else if (!ft_strncmp(line->value, "unset", ft_strlen(line->value)))
				ft_unset(env, line->next->value);
			else
				perror("minishell: command not found");
		}
		line = line->next;
	}
	return (env);
}
