/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:22:47 by aumarin           #+#    #+#             */
/*   Updated: 2023/02/21 18:24:20 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_operator(t_operators op)
{
	if (op == SINGLE_L_REDIRECT)
		printf("SINGLE_L_REDIRECT");
	else if (op == SINGLE_R_REDIRECT)
		printf("SINGLE_R_REDIRECT");
	else if (op == DOUBLE_L_REDIRECT)
		printf("DOUBLE_L_REDIRECT");
	else if (op == DOUBLE_R_REDIRECT)
		printf("DOUBLE_R_REDIRECT");
	else if (op == PIPE)
		printf("PIPE");
	else if (op == ENV_VAR)
		printf("ENV_VAR");
	else if (op == OTHER)
		printf("OTHER");
	else
		printf("ERROR");
}
