/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:04:15 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/25 00:04:29 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

MunitResult test_parser(const MunitParameter params[], void* df)
{
	(void)params;
	(void)df;
	
	t_tokens *tks = malloc(sizeof(t_tokens));
	t_line	*null_ret_test = parse("", tks);
	munit_assert_ptr_null(null_ret_test);
	
	return MUNIT_OK;
}