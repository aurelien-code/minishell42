/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypages <ypages@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:36:50 by ypages            #+#    #+#             */
/*   Updated: 2023/02/27 13:26:25 by ypages           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int env_var_nbr(char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (envp[i] && envp[i][j])
	{
		while (envp[i][j])
			j++;
		i++;
	}
	return(i);	
}

char **name_value_split(char *env_var)
{
	char **var_tab;
	var_tab = ft_split(env_var, '=');
	return (var_tab);
}

int val_nbr(char *var_name)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(var_name && var_name[i])
	{
		if(var_name[i] == ':')
			j++;
	i++;
	}
	return (i);
}

t_env *get_env(char **envp)
{
	t_env *env_tab;
	int varnbr;
	int valnbr;
	int i;
	int j;

	i = 0;
	j = 0;
	varnbr = env_var_nbr(envp);
	valnbr = 0;
	env_tab = malloc(sizeof(t_env) * varnbr + 1);
	while(envp[i] != NULL)
	{
		env_tab[i].name = name_value_split(envp[i])[0];
		valnbr = val_nbr(envp[i]);
		env_tab[i].value = ft_split(name_value_split(envp[i])[1], ':');
		i++;
	}
	i = 0;
// CHECK
	while(env_tab[i].value[j])
	{
		printf("\nPOUR LA VALEUR %s NOUS AVONS\n",env_tab[i].name);
		while(env_tab[i].value[j])
		{
			printf("LA VALEUR: %s", env_tab[i].value[j++]);
		}
		i++;
	}
	return(env_tab);
}

int check_env_path(char **argv, char **envp)
{
	(void)argv;
	t_env *env;
	if (!envp || !envp[0] || !envp[0][0])
			return (printf("[ Error ] - Environment is empty\n"), NOK);
	else if (envp[0] && envp[0][0]
		/* split_env() == ERROR \
		|| find_exec() == ERROR 
		|| exec() == ERROR */)
		{
			env = get_env(envp);
			if(env)
				printf("\nI have a env of %d variables\n\n", env_var_nbr(envp));
			return (print_env(envp), OK);
		}
	return (OK);
}
