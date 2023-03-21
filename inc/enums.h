/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:55:52 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/21 14:07:06 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUM

typedef enum e_tokens
{
	LESS = 1,
	GREAT = 2,
	PIPE = 3,
	QUOTE = 4,
	DOUBLE_QUOTE = 5,
	DOLLAR = 6,
	SPC = 7,
	CHAR = 8
}	t_tokens;

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

typedef enum e_operators
{
	SINGLE_L_REDIRECT = 1,
	SINGLE_R_REDIRECT = 2,
	DOUBLE_L_REDIRECT = 3,
	DOUBLE_R_REDIRECT = 4,
	ENV_VAR = 5,
	PIPE_ = 6,
	STR = 7,
	FILE_ = 8,
	BUILTIN = 9
}	t_operators;

#endif
