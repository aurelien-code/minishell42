/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:59:51 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/06 11:08:51 by aumarin          ###   ########.fr       */
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

int	check_quotes(int db_quote, int sg_quote, char *new_str)
{
	if (db_quote || sg_quote)
	{
		ft_putstr_fd(UNCLOSE_QUOTE_ERR, 2);
		g_exit_code = 2;
		free(new_str);
		return (0);
	}
	else
		return (1);
}

char	*expand_prompt_line(char *str, char **env)
{
	char	*new_str;
	int		i;
	int		sg_quote;
	int		db_quote;

	i = 0;
	sg_quote = 0;
	db_quote = 0;
	new_str = NULL;
	if (ft_strlen(str) > 0)
		new_str = ft_strdup("");
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '"' && !sg_quote)
			db_quote = !db_quote;
		if (str[i] == '\'' && !db_quote)
			sg_quote = !sg_quote;
		if (str[i] == '$' && !sg_quote)
			handle_fking_dollar(str, env, &new_str, &i);
		else
			join_one(&new_str, &i, str);
	}
	if (!check_quotes(db_quote, sg_quote, new_str))
		return (NULL);
	return (new_str);
}
