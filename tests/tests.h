/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:05:28 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/25 17:03:41 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "../munit/munit.h"
# include "minishell.h"

MunitResult test_lexer(const MunitParameter params[], void* user_data_or_fixture);
MunitResult test_parser(const MunitParameter params[], void* df);
MunitResult test_line(const MunitParameter params[], void* df);

#endif