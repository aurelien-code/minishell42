/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:04:15 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/26 18:42:02 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

MunitResult test_lexer(const MunitParameter params[], void* user_data_or_fixture)
{
	(void)params;
	(void)user_data_or_fixture;
	
	char        *str1 = "<>|'\"$ c";
	t_tokens	*obt = lexer(str1);
	t_tokens    exp[] = {1, 2, 3, 4, 5, 6, 7, 8};

	munit_assert_false(memcmp(obt, exp, sizeof(exp)));
	munit_assert_memory_equal(sizeof(exp), exp, obt);
	return MUNIT_OK;
}

MunitResult test_line(const MunitParameter params[], void* df)
{
	(void)params;
	(void)df;

	t_tokens *tks = malloc(sizeof(t_tokens));
	t_line	*null_ret_test = parse("", tks);
	munit_assert_ptr_null(null_ret_test);

	return MUNIT_OK;
}


MunitResult test_parser(const MunitParameter params[], void* df)
{
	(void)params;
	(void)df;
	
	t_tokens *tks = malloc(sizeof(t_tokens));
	t_line	*null_ret_test = parse("", tks);
	munit_assert_ptr_null(null_ret_test);
	
		
	return MUNIT_OK;
}