/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:05:45 by ypages            #+#    #+#             */
/*   Updated: 2023/03/22 20:22:17 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_str(char **env, char *str)
{
	(void)env;
	(void)str;
	return (NULL);
}

char	*change_val(char *src, char *val)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = NULL;
	while (src[i] != '=')
		i++;
	new_str = ft_calloc(i + ft_strlen(val) + 2, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (src[i] != '=')
	{
		new_str[i] = src[i];
		i++;
	}
	new_str[i++] = '=';
	while (val[j])
		new_str[i++] = val[j++];
	return (new_str);
}

int	search_var(char **env, char *var)
{
	int	line_nbr;

	line_nbr = 0;
	while (env[line_nbr])
	{
		if (!(ft_strncmp(var, env[line_nbr], ft_strlen(var))) \
				&& env[line_nbr][ft_strlen(var)] == '=')
			return (line_nbr);
		line_nbr++;
	}
	return (-1);
}

char	**ft_export(char **env, char *var, char *val)
{
	int	var_line;

	var_line = 0;
	printf("-- SIZE = %zu\n", ft_strlen(var));
	var_line = search_var(env, var);
	if (var_line >= 0)
		env[var_line] = change_val(env[var_line], val);
	return (env);
}
