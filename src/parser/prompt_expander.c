/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:59:51 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/04 10:05:14 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	assign_tmps(char **tmp, char **tmp2, char *key, char **new_str)
{
	if (key[0] == '?' && ft_strlen(key) == 1)
	{
		*tmp2 = ft_itoa(g_exit_code);
		*tmp = ft_strjoin(*new_str, *tmp2);
	}
	else if (tmp2)
		*tmp = ft_strjoin(*new_str, *tmp2);
	else
		*tmp = ft_strjoin(*new_str, "\b");
}

void	handle_fking_dollar(char *str, char **env, char **new_str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*key;

	j = calculate_j(*i, str);
	if (j != 1)
	{
		key = ft_substr(str, *i, j);
		if (ft_strlen(key) > 1)
			key++;
		tmp2 = ft_getenv(env, key);
		assign_tmps(&tmp, &tmp2, key, new_str);
		apply_changes(new_str, tmp, tmp2, key);
		*i += j;
	}
	else
		join_one(new_str, i, str);
}

char	*expand_prompt_line(char *str, char **env)
{
	char	*new_str;
	int		i;
	int		is_quoted;
	int		is_db_quote;

	i = 0;
	is_quoted = 0;
	is_db_quote = 0;
	new_str = ft_strdup("");
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '"')
			is_db_quote = !is_db_quote;
		if (str[i] == '\'' && !is_db_quote)
			is_quoted = !is_quoted;
		if (str[i] == '$' && !is_quoted)
		{
			handle_fking_dollar(str, env, &new_str, &i);
		}
		else
			join_one(&new_str, &i, str);
	}
	return (new_str);
}
