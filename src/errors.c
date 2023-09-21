/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:46:21 by aumarin           #+#    #+#             */
/*   Updated: 2023/09/21 18:51:05 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*throw_parsing_error(t_lexer *lex, t_tokens *tok, t_cmd *cmd, char *err)
{
	if (lex)
		free(lex);
	if (tok)
		free(tok);
	if (cmd)
		free(cmd);
	ft_putstr_fd(err, 2);
	return (NULL);
}
