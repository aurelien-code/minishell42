/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:46:44 by aumarin           #+#    #+#             */
/*   Updated: 2023/05/22 14:02:19 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

# ifndef PROMPT_NAME
#  define PROMPT_NAME "minishell> "
# endif

# ifndef NOK
#  define NOK 0
# endif

# ifndef OK
#  define OK 1
# endif

# ifndef REDIR_NEWLINE_ERR
#  define REDIR_NEWLINE_ERR "Syntax error: newline unexpected"
# endif

# ifndef REDIR_SYNTAX_ERR
#  define REDIR_SYNTAX_ERR "Syntax error: redirection unexpected"
# endif

# ifndef UNCLOSE_QUOTE_ERR
#  define UNCLOSE_QUOTE_ERR "Error: quote unclosed"
# endif

#endif