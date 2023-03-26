/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 07:02:22 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/26 19:38:03 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

MunitTest tests[] = {
	{
		"/lexer", /* name */
		test_lexer, /* test */
		NULL, /* setup */
		NULL, /* tear_down */
		MUNIT_TEST_OPTION_NONE, /* options */
		NULL /* parameters */
	},
	{
		"/parser", /* name */
		test_parser, /* test */
		NULL, /* setup */
		NULL, /* tear_down */
		MUNIT_TEST_OPTION_NONE, /* options */
		NULL /* parameters */
	},
	{ "/test_new_line_basic", test_new_line_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_last_line_item_basic", test_last_line_item_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_new_line_item_basic", test_new_line_item_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};


static const MunitSuite suite = {
	"/tests", /* name */
	tests, /* tests */
	NULL, /* suites */
	1, /* iterations */
	MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char **argv)
{
	munit_suite_main(&suite, NULL, argc, argv);

	return (0);
}
