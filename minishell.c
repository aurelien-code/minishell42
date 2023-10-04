/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:11 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/04 08:59:56 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;


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
	if (!(result = malloc(s1_len + len + 1)))
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

char	*expand_prompt_line(char *str, char **env)
{
	char	*new_str;
	int		i;
	int		is_quoted;
	int		is_db_quote;
	int		j;
	char	*key;
	char	*tmp;
	char	*tmp2;

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
			if (j != 1)
			{
				key = ft_substr(str, i, j);
				if (ft_strlen(key) > 1)
					key++;
				tmp2 = ft_getenv(env, key);
				if (key[0] == '?' && ft_strlen(key) == 1)
				{
					tmp2 = ft_itoa(g_exit_code);
					tmp = ft_strjoin(new_str, tmp2);
				}
				else if (tmp2)
					tmp = ft_strjoin(new_str, tmp2);
				else
					tmp = ft_strjoin(new_str, "\b");
				if (tmp)
				{
					free(new_str);
					new_str = tmp;
				}
				if (tmp2)
					free(tmp2);
				--key;
				free(key);
				i += j;
			}
			else
			{
				tmp = new_str;
				new_str = ft_strnjoin(tmp, &str[i], 1);
				free(tmp);
				i++;
			}
		}
		else
		{
			tmp = new_str;
			new_str = ft_strnjoin(tmp, &str[i], 1);
			free(tmp);
			i++;
		}
	}
	if (!*env)
		return (NULL);
	return (new_str);
}

char	**copy_env_in_heap(char **env)
{
	char	**env_cpy;
	int		env_size;
	int		i;

	i = 0;
	env_size = 0;
	while (env[env_size])
		env_size++;
	env_cpy = ft_calloc(env_size + 1, sizeof(char *));
	if (!env_cpy)
		return (NULL);
	while (i < env_size)
	{
		env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
	return (env_cpy);
}

void	init(int argc, char **envp, char ***cpy_env, char **prompt_line)
{
	if (!envp || argc > 1)
		exit(1);
	sig_setup(1);
	*cpy_env = copy_env_in_heap(envp);
	*prompt_line = ft_prompt();
}

void	lexer_and_parse(char *prompt_line, t_lexer **lexer_line,
							t_tokens **tokens, char **cpy_env)
{
	char	*line_after_expand;

	line_after_expand = expand_prompt_line(prompt_line, cpy_env);
	printf("->%s\n", line_after_expand);
	*lexer_line = lexer(line_after_expand);
	if (!*lexer_line)
		return ;
	*tokens = get_tokens(line_after_expand, *lexer_line, cpy_env);
	free(line_after_expand);
}

void	execute_commands(t_tokens *tokens, t_lexer *lexer_line, \
						char ***cpy_env)
{
	t_cmd	*commands;

	commands = parser(tokens);
	free_tokens(tokens);
	free(lexer_line);
	if (commands)
	{
		sig_setup(0);
		g_exit_code = executer(commands, cpy_env);
		sig_setup(1);
		free_commands(commands);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*prompt_line;
	t_lexer		*lexer_line;
	t_tokens	*tokens;
	char		**cpy_env;

	(void)argv;
	init(argc, envp, &cpy_env, &prompt_line);
	while (prompt_line)
	{
		history_size(1);
		lexer_and_parse(prompt_line, &lexer_line, &tokens, cpy_env);
		if (lexer_line && tokens)
			execute_commands(tokens, lexer_line, &cpy_env);
		else if (!tokens)
		{
			free(lexer_line);
		}
		prompt_line = ft_prompt();
	}
	rl_clear_history();
	ft_putstr_fd("exit\n", 2);
	ft_free_cpy_env(cpy_env);
	return (0);
}
