/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:26:27 by aumarin           #+#    #+#             */
/*   Updated: 2023/03/26 19:30:04 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

MunitResult test_new_line_basic(const MunitParameter params[], void* fixture)
{
	(void)params;
	(void)fixture;
    // Call the function and check the output
    t_line* actual_output = new_line();
    munit_assert_not_null(actual_output);
    munit_assert_null(actual_output->value);
    munit_assert_null(actual_output->next);

    // Cleanup
    free(actual_output);
    return MUNIT_OK;
}

MunitResult test_last_line_item_basic(const MunitParameter params[], void* fixture)
{
	(void)params;
	(void)fixture;
    // Initialize inputs
    t_line* head = new_line();
    head->type = STR;
    head->value = "+";
    t_line* second_item = new_line();
    second_item->type = STR;
    second_item->value = "2";
    head->next = second_item;

    // Call the function and check the output
    t_line* actual_output = last_line_item(head);
    munit_assert_not_null(actual_output);
    munit_assert_string_equal(actual_output->value, "2");
    munit_assert_null(actual_output->next);

    // Cleanup
    free(head->next);
    free(head);
    return MUNIT_OK;
}

MunitResult test_new_line_item_basic(const MunitParameter params[], void* fixture)
{
	(void)params;
	(void)fixture;
    // Initialize inputs
    t_line* head = new_line();
    head->type = STR;
    head->value = "+";

    // Call the function and check the output
    t_line* actual_output = new_line_item(&head, STR, "2");
    munit_assert_not_null(actual_output);
    munit_assert_string_equal(head->next->value, "2");
    munit_assert_null(head->next->next);

    // Cleanup
    free(head->next);
    free(head);
    return MUNIT_OK;
}