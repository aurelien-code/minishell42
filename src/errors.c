/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:46:21 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/04 13:37:36 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	*throw_parsing_error(t_lexer *lex, t_tokens *tok, t_cmd *cmd, char *err)
{
	if (lex)
		free(lex);
	if (tok)
		free_tokens(tok);
	if (cmd)
		free_commands(cmd);
	g_exit_code = 2;
	ft_putstr_fd(err, 2);
	return (NULL);
}
