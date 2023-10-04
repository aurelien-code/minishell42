/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_expander2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:00:24 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/04 10:00:39 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str, int *idx)
{
	int		start;
	int		end;
	char	*key;

	if (str[*idx] != '$')
		return (NULL);
	(*idx)++;
	start = *idx;
	while (str[*idx] && (ft_isalpha(str[*idx]) || str[*idx] == '_' || \
		(ft_isdigit(str[*idx]) && *idx > start)))
		(*idx)++;
	end = *idx;
	key = (char *)malloc(end - start + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, &str[start], end - start + 1);
	return (key);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	char	*result;
	size_t	s1_len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	result = malloc(s1_len + len + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = 0;
	while (j < len)
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}	

int	calculate_j(int i, char *str)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != ' ' && str[i + j] != '\t' \
				&& str[i + j] != '$' && str[i + j] != '\'' && str[i + j] != '"')
	{
		if (str[i + j] == '?' || str[i + j] == '$')
		{
			j++;
			break ;
		}
		j++;
	}
	return (j);
}

void	join_one(char **new_str, int *i, char *str)
{
	char	*tmp;

	tmp = *new_str;
	*new_str = ft_strnjoin(tmp, &str[*i], 1);
	free(tmp);
	(*i)++;
}

void	apply_changes(char **new_str, char *tmp, char *tmp2, char *key)
{
	if (tmp)
	{
		free(*new_str);
		*new_str = tmp;
	}
	if (tmp2)
		free(tmp2);
	--key;
	free(key);
}
