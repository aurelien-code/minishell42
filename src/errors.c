/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:46:21 by aumarin           #+#    #+#             */
/*   Updated: 2023/09/18 16:06:17 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*throw_parsing_error(t_lexer *lex, t_tokens *tok, t_cmd *cmd, char *err)
{
	if (lex)
		free(lexer);
	if (tok)
		free(tok);
	if (cmd)
		free(cmd);
	printf("%s\n", err);
	return (NULL);
}
