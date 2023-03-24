/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:05:05 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/24 19:06:20 by aumarin          ###   ########.fr       */
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
	int	i = -1;
	while (obt[++i])
		munit_assert_int(obt[i], ==, exp[i]);
	munit_assert_memory_equal(sizeof(exp), exp, obt);
	return MUNIT_OK;
}