/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:43:39 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/02 22:40:01 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char	*ft_getenv(char **env, char *var)
{
	int		i;
	int		env_size;
	char	**env_kv;
	char	*result;

	result = NULL;
	env_size = get_env_size(env);
	i = 0;
	while (i < env_size)
	{
		env_kv = ft_split(env[i], '=');
		if (!strncmp(env_kv[0], var, ft_strlen(env_kv[0])))
		{
			result = ft_strdup(env_kv[1]);
			ft_free_split(env_kv);
			return (result);
		}
		i++;
		ft_free_split(env_kv);
	}
	return (result);
}

t_tokens	*expand(t_lexer	*lexer_arr, int	*i, char **env)
{
	int		j;
	char	*new_str;
	char	*tmp_sublxr;

	new_str = "";
	j = (*i) + 1;
	if (lexer_arr[j].value == '?')
	{
		(*i)++;
		return (new_token_item(ft_itoa(g_exit_code), TOKEN));
	}
	if (lexer_arr[*i].value == '$')
	{
		while (lexer_arr[j].value && lexer_arr[j].value != ' ' && \
			lexer_arr[j].value != '$' && lexer_arr[j].type == NORMAL)
				j++;
		tmp_sublxr = substr_lexer(lexer_arr, *i, j);
		new_str = ft_getenv(env, tmp_sublxr);
		free(tmp_sublxr);
		*i = j;
	}
	return (new_token_item(new_str, TOKEN));
}
