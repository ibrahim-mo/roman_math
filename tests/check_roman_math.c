/* 
 * File:   check_roman_math.c
 * Author: Ibrahim Almohandes
 *
 * Created on September 16, 2016, 7:20 PM
 */

//#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "../src/roman_math.h"

void setup(void)
{
}

void teardown(void)
{
}

START_TEST(test_add_roman)
{
    char *result = add_roman("CCCLVI", "MMMCDXXIX");
    ck_assert_str_eq(result, "MMMDCCLXXXV");
    free(result);

    result = add_roman("MCCCLXXV", "DCCLVI");
    ck_assert_str_eq(result, "MMCXXXI");
    free(result);

    result = add_roman("DCCCXI", "DCCLXXIII");
    ck_assert_str_eq(result, "MDLXXXIV");
    free(result);

    result = add_roman("CDXC", "MM");
    ck_assert_str_eq(result, "MMCDXC");
    free(result);

    result = add_roman("", "MMCXI");
    ck_assert_str_eq(result, "MMCXI");
    free(result);

    result=add_roman("XIV", "");
    ck_assert_str_eq(result, "XIV");
    free(result);
}
END_TEST

START_TEST(test_subtract_roman)
{
    char *result = subtract_roman("MMMMMDCCCLXXXIV", "CDXLII");
    ck_assert_str_eq(result, "MMMMMCDXLII");
    free(result);

    result = subtract_roman("CMXXIV", "CCLXXIII");
    ck_assert_str_eq(result, "DCLI");
    free(result);

    result = subtract_roman("MMCLVII", "CCCXVIII");
    ck_assert_str_eq(result, "MDCCCXXXIX");
    free(result);

    result = subtract_roman("MCMXCIX", "CCCXXXIV");
    ck_assert_str_eq(result, "MDCLXV");
    free(result);

    result = subtract_roman("CDIV", "");
    ck_assert_str_eq(result, "CDIV");
    free(result);
}
END_TEST

START_TEST(test_roman_NULL)
{
    ck_assert_msg(add_roman(NULL, NULL)==NULL, "NULL should be returned when at least one input is NULL!");
    ck_assert_msg(add_roman(NULL, "XIV")==NULL, "NULL should be returned when at least one input is NULL!");
    ck_assert_msg(add_roman("XV", NULL)==NULL, "NULL should be returned when at least one input is NULL!");
    ck_assert_msg(subtract_roman(NULL, NULL)==NULL, "NULL should be returned when at least one input is NULL!");
    ck_assert_msg(subtract_roman(NULL, "VII")==NULL, "NULL should be returned when at least one input is NULL!");
    ck_assert_msg(subtract_roman("XX", NULL)==NULL, "NULL should be returned when at least one input is NULL!");
}
END_TEST

START_TEST(test_roman_negative)
{
    ck_assert_msg(subtract_roman("CDXLII", "MMDCCCLXXXIV")==NULL, 
        "Negative subtraction is not supported. first must be >= second!");
    ck_assert_msg(subtract_roman("", "CDXLI")==NULL, 
        "Negative subtraction is not supported. first must be >= second!");
}
END_TEST

START_TEST(test_roman_empty)
{
    char *result = add_roman("", "");
    if (strcmp(result, "") != 0) 
    {
        ck_abort_msg("Empty string should be returned when both inputs are empty strings!");
    }
    free(result);
    result = subtract_roman("", "");
    if (strcmp(result, "") != 0) 
    {
        ck_abort_msg("Empty string should be returned when both inputs are empty strings!");
    }
    free(result);
}
END_TEST

Suite * roman_math_suite(void)
{
    Suite *s;
    TCase *tc_core;
    TCase *tc_limits;

    s = suite_create("roman_math");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_add_roman);
    tcase_add_test(tc_core, test_subtract_roman);
    suite_add_tcase(s, tc_core);

    /* Limits test case */
    tc_limits = tcase_create("Limits");

    tcase_add_test(tc_limits, test_roman_NULL);
    tcase_add_test(tc_limits, test_roman_empty);
    tcase_add_test(tc_limits, test_roman_negative);
    suite_add_tcase(s, tc_limits);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = roman_math_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
