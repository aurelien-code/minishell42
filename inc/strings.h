/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:46:44 by aumarin           #+#    #+#             */
/*   Updated: 2023/10/02 14:46:50 by aumarin          ###   ########.fr       */
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
#  define REDIR_NEWLINE_ERR "Syntax error: newline unexpected.\n"
# endif

# ifndef REDIR_SYNTAX_ERR
#  define REDIR_SYNTAX_ERR "Syntax error: redirection unexpected.\n"
# endif

# ifndef UNCLOSE_QUOTE_ERR
#  define UNCLOSE_QUOTE_ERR "Error: quote unclosed.\n"
# endif

# ifndef TOO_MANY_REDIRS
#  define TOO_MANY_REDIRS "Syntax error: too many redirection symbols.\n"
# endif

# ifndef NO_PIPE_ENTRY
#  define NO_PIPE_ENTRY "Syntax error: missing command before '|'.\n"
# endif

# ifndef NO_FILE_TO_REDR
#  define NO_FILE_TO_REDR "Syntax error: missing command after redirection.\n"
# endif

# ifndef TEMP_FILE_ERR
#  define TEMP_FILE_ERR "minishell: cannot create temp file for here-document"
# endif

#endif
