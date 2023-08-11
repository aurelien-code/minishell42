/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:55:52 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/11 15:32:02 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_lexer_enum
{
	NORMAL = 1,
	QUOTE = 2,
	PIPE = 3,
	REDIRECT = 4,
	EXPAND = 5
}	t_lexer_enum;

typedef enum e_builtins
{
	ECHO = 1,
	CD = 2,
	PWD = 3,
	EXPORT = 4,
	UNSET = 5,
	ENV = 6,
	EXIT = 7
}	t_builtins;

#endif
