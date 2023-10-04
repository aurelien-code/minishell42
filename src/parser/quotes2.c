/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 22:47:43 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/04 01:50:16 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	size_t	i;
	size_t	len;

	len = ft_strlen(s1);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len && i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new_str);
}

void	handle_dollar(char **env, char *str, int *i, char **new_str)
{
	int		j;
	char	*key;
	char	*env_value;

	j = 1;
	if (str[*i + j] && str[*i + j] == '?')
	{
		if (*new_str)
			*new_str = join_and_free(*new_str, ft_itoa(g_exit_code));
		else
			*new_str = ft_itoa(g_exit_code);
		(*i)++;
		return ;
	}
	else if (str[*i + j] == ' ' || !str[*i + j] || str[*i + j] == '\t')
	{
		if (*new_str)
			*new_str = join_and_free(*new_str, ft_strdup("$"));
		else
			*new_str = ft_strdup("$");
		(*i)++;
		return ;
	}
	while (str[*i + j] && str[*i + j] != ' ' && str[*i + j] != '\t' && \
			str[*i + j] != '$')
		j++;
	key = ft_substr(str, *i, j);
	key++;
	env_value = ft_getenv(env, key);
	if (*new_str)
		*new_str = join_and_free(*new_str, env_value);
	else
		*new_str = env_value;
	free(--key);
	*i += j - 1;
}

void	handle_other_char(char *str, int i, char **new_str)
{
	char	*char_dup;

	char_dup = ft_strndup(&str[i], 1);
	if (*new_str)
		*new_str = join_and_free(*new_str, char_dup);
	else
		*new_str = char_dup;
}
