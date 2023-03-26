/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:05:28 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/26 19:29:10 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "../munit/munit.h"
# include "minishell.h"
# include <string.h>

t_line	*new_line(void);
t_line	*last_line_item(t_line *lst);
t_line	*new_line_item(t_line **head, t_operators type, char *value);

MunitResult test_lexer(const MunitParameter params[], void* user_data_or_fixture);
MunitResult test_parser(const MunitParameter params[], void* df);
MunitResult test_line(const MunitParameter params[], void* df);

MunitResult test_new_line_basic(const MunitParameter params[], void* fixture);
MunitResult test_last_line_item_basic(const MunitParameter params[], void* fixture);
MunitResult test_new_line_item_basic(const MunitParameter params[], void* fixture);

#endif