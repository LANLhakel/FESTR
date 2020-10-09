/*=============================================================================

test_utils.cpp
Definitions for tests for standalone utility functions.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 29 November 2014
Last modified on 2 October 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.9 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

//  Note: only use trimmed strings for names

#include <test_utils.h>
#include <Test.h>

#include <ArrDbl.h>
#include <constants.h>

#include <stdexcept>
#include <vector>

void test_utils(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "utils";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "radians", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 30.0;
        double expected = cnst::PI / 6.0;
        double actual = utils::radians(x);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT/10);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "degrees", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = cnst::PI / 6.0;
        double expected = 30.0;
        double actual = utils::degrees(x);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nint_plus7.4", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = 7;
        int actual = utils::nint(7.4);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nint_plus7.5", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = 8;
        int actual = utils::nint(7.5);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nint_plus7.6", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = 8;
        int actual = utils::nint(7.6);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nint_minus7.4", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = -7;
        int actual = utils::nint(-7.4);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nint_minus7.5", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = -7;
        int actual = utils::nint(-7.5);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nint_minus7.6", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = -8;
        int actual = utils::nint(-7.6);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nint_0.0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = 0;
        int actual = utils::nint(0.0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "double_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = -1.0e99;
        std::string expected = "  -1.000000e+99";
        std::string actual = utils::double_to_string(x);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "double_to_string_big", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = -1.0e100;
        std::string expected = " -1.000000e+100";
        std::string actual = utils::double_to_string(x);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size_t_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 7;
        std::string expected = "007";
        std::string actual = utils::int_to_string(i, '0', 3);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "short_int_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        short int i = 7;
        std::string expected = "007";
        std::string actual = utils::int_to_string(i, '0', 3);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "file_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string fname(cnststr::PATH + "UniTest/text_file.txt");
        std::string expected = "This is a\n     text\n          file.";
        std::string actual = utils::file_to_string(fname);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sign_int_positive", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = 1;
        int actual = utils::sign_int(7);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sign_int_negative", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = -1;
        int actual = utils::sign_int(-7);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sign_int_zero", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = 0;
        int actual = utils::sign_int(0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sign_eqt_positive", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int i = 7;
        int expected = 1;
        int actual = utils::sign_eqt(i, 0.01);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sign_eqt_negative", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        float x = -7.0;
        int expected = -1;
        int actual = utils::sign_eqt(x, 0.01);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sign_eqt_zero", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 0.001;
        int expected = 0;
        int actual = utils::sign_eqt(x, 0.01);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_root_count2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 1.0;
        double b = 1.0;
        double c = -6.0;
        int expected = 2;
        int actual = utils::solve_quadratic(a, b, c, EQT).nroots;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_positive_root", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 1.0;
        double b = 1.0;
        double c = -6.0;
        double expected = 2.0;
        double actual = utils::solve_quadratic(a, b, c, EQT).x1;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_negative_root", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 1.0;
        double b = 1.0;
        double c = -6.0;
        double expected = -3.0;
        double actual = utils::solve_quadratic(a, b, c, EQT).x2;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_root_b0_count2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 3.0;
        double b = 0.0;
        double c = -27.0;
        int expected = 2;
        int actual = utils::solve_quadratic(a, b, c, EQT).nroots;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_positive_b0_root", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 3.0;
        double b = 0.0;
        double c = -27.0;
        double expected = 3.0;
        double actual = utils::solve_quadratic(a, b, c, EQT).x1;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_negative_b0_root", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = -3.0;
        double b = 0.0;
        double c = 27.0;
        double expected = -3.0;
        double actual = utils::solve_quadratic(a, b, c, EQT).x2;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_double_root_count1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 1.0;
        double b = 4.0;
        double c = 4.0;
        int expected = 1;
        int actual = utils::solve_quadratic(a, b, c, EQT).nroots;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_double_root1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 1.0;
        double b = 4.0;
        double c = 4.0;
        double expected = -2.0;
        double actual = utils::solve_quadratic(a, b, c, EQT).x1;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_double_root2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 1.0;
        double b = 4.0;
        double c = 4.0;
        double expected = -2.0;
        double actual = utils::solve_quadratic(a, b, c, EQT).x2;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_no_real_root_count0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 1.0;
        double b = 1.0;
        double c = 3.0;
        int expected = 0;
        int actual = utils::solve_quadratic(a, b, c, EQT).nroots;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_no_real_root1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 1.0;
        double b = 1.0;
        double c = 3.0;
        double expected = -1.0e100;
        double actual = utils::solve_quadratic(a, b, c, EQT).x1;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_no_real_root2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 1.0;
        double b = 1.0;
        double c = 3.0;
        double expected = -1.0e100;
        double actual = utils::solve_quadratic(a, b, c, EQT).x2;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_a0_count1", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 0.0;
        double b = 4.0;
        double c = 8.0;
        int expected = 1;
        int actual = utils::solve_quadratic(a, b, c, EQT).nroots;
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_a0_root1", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 0.0;
        double b = 4.0;
        double c = 8.0;
        double expected = -2.0;
        double actual = utils::solve_quadratic(a, b, c, EQT).x1;
        
        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_a0_root2", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 0.0;
        double b = 4.0;
        double c = 8.0;
        double expected = -2.0;
        double actual = utils::solve_quadratic(a, b, c, EQT).x2;
        
        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_no_real_root_count0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 0.0;
        double b = 0.0;
        double c = 3.0;
        int expected = 0;
        int actual = utils::solve_quadratic(a, b, c, EQT).nroots;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_no_real_root1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 0.0;
        double b = 0.0;
        double c = 3.0;
        double expected = -1.0e100;
        double actual = utils::solve_quadratic(a, b, c, EQT).x1;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "solve_quadratic_no_real_root2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double a = 0.0;
        double b = 0.0;
        double c = 3.0;
        double expected = -1.0e100;
        double actual = utils::solve_quadratic(a, b, c, EQT).x2;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bisect_mid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 7.2;
        size_t ilow = 0;
        size_t ihigh = 29;
        size_t expected = 19;
        size_t actual = utils::bisect(x, v, ilow, ihigh);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bisect_mid_on_grid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 7.0;
        size_t ilow = 0;
        size_t ihigh = 29;
        size_t expected = 19;
        size_t actual = utils::bisect(x, v, ilow, ihigh);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bisect_low", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 0.4;
        size_t ilow = 0;
        size_t ihigh = 29;
        size_t expected = 0;
        size_t actual = utils::bisect(x, v, ilow, ihigh);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bisect_low_on_grid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 0.3;
        size_t ilow = 0;
        size_t ihigh = 29;
        size_t expected = 0;
        size_t actual = utils::bisect(x, v, ilow, ihigh);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bisect_high", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 9.8;
        size_t ilow = 0;
        size_t ihigh = 29;
        size_t expected = 28;
        size_t actual = utils::bisect(x, v, ilow, ihigh);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bisect_high_on_grid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 9.9;
        size_t ilow = 0;
        size_t ihigh = 29;
        size_t expected = 28;
        size_t actual = utils::bisect(x, v, ilow, ihigh);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bisect_range_low", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 7.2;
        size_t ilow = 19;
        size_t ihigh = 24;
        size_t expected = 19;
        size_t actual = utils::bisect(x, v, ilow, ihigh);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bisect_range_high", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 7.0;
        size_t ilow = 10;
        size_t ihigh = 19;
        size_t expected = 18;
        size_t actual = utils::bisect(x, v, ilow, ihigh);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bracket_low", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 6.8;
        size_t ilow = 11;
        size_t ihigh = 12;
        utils::bracket(x, v, 29, ilow, ihigh);
        size_t expected = 15;
        size_t actual = ilow;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bracket_high", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 6.8;
        size_t ilow = 11;
        size_t ihigh = 12;
        utils::bracket(x, v, 29, ilow, ihigh);
        size_t expected = 19;
        size_t actual = ihigh;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bracketed_low", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 6.8;
        size_t ilow = 18;
        size_t ihigh = 19;
        utils::bracket(x, v, 29, ilow, ihigh);
        size_t expected = 18;
        size_t actual = ilow;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bracketed_high", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 6.8;
        size_t ilow = 18;
        size_t ihigh = 19;
        utils::bracket(x, v, 29, ilow, ihigh);
        size_t expected = 19;
        size_t actual = ihigh;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "not_bracketed_low", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 0.0;
        size_t ilow = 18;
        size_t ihigh = 19;
        utils::bracket(x, v, 29, ilow, ihigh);
        size_t expected = 0;
        size_t actual = ilow;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "not_bracketed_high", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 0.0;
        size_t ilow = 18;
        size_t ihigh = 19;
        utils::bracket(x, v, 29, ilow, ihigh);
        size_t expected = 3;
        size_t actual = ihigh;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bracket_up_low", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 8.0;
        size_t ilow = 27;
        size_t ihigh = 28;
        utils::bracket(x, v, 29, ilow, ihigh);
        size_t expected = 20;
        size_t actual = ilow;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bracket_up_high", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 8.0;
        size_t ilow = 27;
        size_t ihigh = 28;
        utils::bracket(x, v, 29, ilow, ihigh);
        size_t expected = 24;
        size_t actual = ihigh;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bracket_down_low", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 2.0;
        size_t ilow = 1;
        size_t ihigh = 2;
        utils::bracket(x, v, 29, ilow, ihigh);
        size_t expected = 5;
        size_t actual = ilow;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bracket_down_high", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 2.0;
        size_t ilow = 1;
        size_t ihigh = 2;
        utils::bracket(x, v, 29, ilow, ihigh);
        size_t expected = 9;
        size_t actual = ihigh;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nearest0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> v;
        double x = 6.8;
        size_t expected = 0;
        size_t actual = utils::nearest(x, v, 0, 0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nearest1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 6.8;
        size_t expected = 18;
        size_t actual = utils::nearest(x, v, 30, 0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nearest2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 6.9;
        size_t expected = 19;
        size_t actual = utils::nearest(x, v, 30, 0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nearest_low", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 0.0;
        size_t expected = 0;
        size_t actual = utils::nearest(x, v, 30, 0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nearest_low_edge", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 0.3;
        size_t expected = 0;
        size_t actual = utils::nearest(x, v, 30, 0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nearest_high", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 11.0;
        size_t expected = 29;
        size_t actual = utils::nearest(x, v, 30, 0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nearest_high_edge", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 9.8;
        size_t expected = 29;
        size_t actual = utils::nearest(x, v, 30, 29);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nearest_exh_empty", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> v;
        double x = 6.8;
        size_t expected = 0;
        size_t actual = utils::nearest_exh(x, v, 0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nearest_exh", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 6.8;
        size_t expected = 18;
        size_t actual = utils::nearest_exh(x, v, 30);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nearest_exh_low", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 0.0;
        size_t expected = 0;
        size_t actual = utils::nearest_exh(x, v, 30);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nearest_exh_high", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <table.inc>
        double x = 20.0;
        size_t expected = 29;
        size_t actual = utils::nearest_exh(x, v, 30);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fname_root", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string material = "z18";
        std::string te_str = "06400";
        std::string tr_str = "00000";
        std::string ne_str = "8.0e24";
        std::string expected = "z18_te06400ev_tr00000ev_ne8.0e24pcc_";
        std::string actual = utils::fname_root(material, te_str, tr_str, ne_str);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_em", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string sp = "em.txt";
        std::string material = "z18";
        std::string te_str = "06400";
        std::string tr_str = "00000";
        std::string ne_str = "8.0e24";
        std::string path(cnststr::PATH + "UniTest/Dbase2/spectra/");
        std::string fname = path + material + "/"
                          + utils::fname_root(material, te_str, tr_str, ne_str)
                          + sp;
        std::vector<double> v(3, 0.0);
        utils::load_array(fname, 3, 0, 2, v);
        double expected = 2.0e15;
        double actual = v.at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_ab", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string sp = "ab.txt";
        std::string material = "z18";
        std::string te_str = "06400";
        std::string tr_str = "00000";
        std::string ne_str = "8.0e24";
        std::string path(cnststr::PATH + "UniTest/Dbase2/spectra/");
        std::string fname = path + material + "/"
                          + utils::fname_root(material, te_str, tr_str, ne_str)
                          + sp;
        std::vector<double> v(3, 0.0);
        utils::load_array(fname, 3, 0, 2, v);
        double expected = 4.0e9;
        double actual = v.at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_sc", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string sp = "sc.txt";
        std::string material = "z18";
        std::string te_str = "06400";
        std::string tr_str = "00000";
        std::string ne_str = "8.0e24";
        std::string path(cnststr::PATH + "UniTest/Dbase2/spectra/");
        std::string fname = path + material + "/"
                          + utils::fname_root(material, te_str, tr_str, ne_str)
                          + sp;
        std::vector<double> v(3, 0.0);
        utils::load_array(fname, 3, 0, 2, v);
        double expected = 0.08;
        double actual = v.at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_em1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string sp = "em.txt";
        std::string material = "z18";
        std::string te_str = "06400";
        std::string tr_str = "00000";
        std::string ne_str = "8.0e24";
        std::string path(cnststr::PATH + "UniTest/Dbase2/spectra/");
        std::string fname = path + material + "/"
                          + utils::fname_root(material, te_str, tr_str, ne_str)
                          + sp;
        std::vector<double> v(3, 0.0);
        utils::load_array(fname, 3, 0, 1, v);
        double expected = 2.0e15;
        double actual = v.at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_ab1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string sp = "ab.txt";
        std::string material = "z18";
        std::string te_str = "06400";
        std::string tr_str = "00000";
        std::string ne_str = "8.0e24";
        std::string path(cnststr::PATH + "UniTest/Dbase2/spectra/");
        std::string fname = path + material + "/"
                          + utils::fname_root(material, te_str, tr_str, ne_str)
                          + sp;
        std::vector<double> v(3, 0.0);
        utils::load_array(fname, 3, 1, 1, v);
        double expected = 4.0e9;
        double actual = v.at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_sc1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string sp = "sc.txt";
        std::string material = "z18";
        std::string te_str = "06400";
        std::string tr_str = "00000";
        std::string ne_str = "8.0e24";
        std::string path(cnststr::PATH + "UniTest/Dbase2/spectra/");
        std::string fname = path + material + "/"
                          + utils::fname_root(material, te_str, tr_str, ne_str)
                          + sp;
        std::vector<double> v(3, 0.0);
        utils::load_array(fname, 3, 1, 2, v);
        double expected = 0.08;
        double actual = v.at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_fp", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string sp = "zb.txt";
        std::string material = "z18";
        std::string te_str = "06400";
        std::string tr_str = "00000";
        std::string ne_str = "8.0e24";
        std::string path(cnststr::PATH + "UniTest/Dbase2/eos/");
        std::string fname = path + material + "/"
                          + utils::fname_root(material, te_str, tr_str, ne_str)
                          + sp;
        std::vector<double> v(19, -1.0);
        double zbar;
        utils::load_eos(fname, 19, v, zbar);
        double expected = 0.1;
        double actual = v.at(12);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_fp0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string sp = "zb.txt";
        std::string material = "z18";
        std::string te_str = "06400";
        std::string tr_str = "00000";
        std::string ne_str = "8.0e24";
        std::string path(cnststr::PATH + "UniTest/Dbase2/eos/");
        std::string fname = path + material + "/"
                          + utils::fname_root(material, te_str, tr_str, ne_str)
                          + sp;
        std::vector<double> v(19, -1.0);
        double zbar;
        utils::load_eos(fname, 19, v, zbar);
        double expected = 0.0;
        double actual = v.at(18);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_zbar", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string sp = "zb.txt";
        std::string material = "z18";
        std::string te_str = "06400";
        std::string tr_str = "00000";
        std::string ne_str = "8.0e24";
        std::string path(cnststr::PATH + "UniTest/Dbase2/eos/");
        std::string fname = path + material + "/"
                          + utils::fname_root(material, te_str, tr_str, ne_str)
                          + sp;
        std::vector<double> v(19, -1.0);
        double zbar;
        utils::load_eos(fname, 19, v, zbar);
        double expected = 10.0;
        double actual = zbar;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ne_charge_neut", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double np = 1.0e16; // total particle number density (particles/cm3)
        unsigned short int nmat = 2; // number of materials
        std::vector<double> fp; // fractional population of material
        fp.reserve(nmat);
        fp.push_back(0.6);  // "deuterium"
        fp.push_back(0.4);  // "argon"
        std::vector<double> zb; // average ionization state of material
        zb.reserve(nmat);
        zb.push_back(1.0);  // "deuterium"
        zb.push_back(10.0); // "argon"
        double expected = 4.6e16;
        double actual = utils::ne_charge_neut(np, nmat, fp, zb);

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e5);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ndigits0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 0;
        int expected = 1;
        int actual = utils::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ndigits9", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 9;
        int expected = 1;
        int actual = utils::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ndigits10", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 10;
        int expected = 2;
        int actual = utils::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ndigits360", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 360;
        int expected = 3;
        int actual = utils::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ndigits_over_limit", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 1000000000000;
        int expected = 0;
        int actual = utils::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fitlin_0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 0.0;
        double x1 = 2.0, y1 = -2.0, x2 = 6.0, y2 = 7.0;
        double expected = -6.5;
        double actual = utils::fitlin(x, x1, y1, x2, y2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fitlin_2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 2.0;
        double x1 = 2.0, y1 = -2.0, x2 = 6.0, y2 = 7.0;
        double expected = -2.0;
        double actual = utils::fitlin(x, x1, y1, x2, y2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fitlin_5", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 5.0;
        double x1 = 2.0, y1 = -2.0, x2 = 6.0, y2 = 7.0;
        double expected = 4.75;
        double actual = utils::fitlin(x, x1, y1, x2, y2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fitlin_6", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 6.0;
        double x1 = 2.0, y1 = -2.0, x2 = 6.0, y2 = 7.0;
        double expected = 7.0;
        double actual = utils::fitlin(x, x1, y1, x2, y2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fitlin_8", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 8.0;
        double x1 = 2.0, y1 = -2.0, x2 = 6.0, y2 = 7.0;
        double expected = 11.5;
        double actual = utils::fitlin(x, x1, y1, x2, y2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fitpoint_lin_lin", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 6.0;
        double x1 = 2.0, y1 = 3.0, x2 = 7.0, y2 = 8.0;
        std::string xmode = "lin";
        std::string ymode = "lin";
        double expected = 7.0;
        double actual = utils::fitpoint(x, x1, y1, x2, y2, xmode, ymode);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fitpoint_lin_log", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 6.0;
        double x1 = 2.0, y1 = 3.0, x2 = 7.0, y2 = 8.0;
        std::string xmode = "lin";
        std::string ymode = "log";
        double expected = 6.575007318068902;
        double actual = utils::fitpoint(x, x1, y1, x2, y2, xmode, ymode);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fitpoint_log_lin", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 6.0;
        double x1 = 2.0, y1 = 3.0, x2 = 7.0, y2 = 8.0;
        std::string xmode = "log";
        std::string ymode = "lin";
        double expected = 7.384757197874386;
        double actual = utils::fitpoint(x, x1, y1, x2, y2, xmode, ymode);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fitpoint_log_log", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 6.0;
        double x1 = 2.0, y1 = 3.0, x2 = 7.0, y2 = 8.0;
        std::string xmode = "log";
        std::string ymode = "log";
        double expected = 7.090472022038607;
        double actual = utils::fitpoint(x, x1, y1, x2, y2, xmode, ymode);

        failed_test_count += t.check_equal_real_num(expected, actual, 1e3*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_grid_lin_1_false", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> act = utils::get_grid(2.0, 2.0, 1, "lin", false);
        std::string expected("   2.000000e+00");
        std::string actual = utils::double_to_string(act.at(0));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_grid_lin_3_false", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> act = utils::get_grid(2.0, 8.0, 3, "lin", false);
        std::string expected("   2.000000e+00   5.000000e+00   8.000000e+00");
        std::string actual = utils::double_to_string(act.at(0))
                           + utils::double_to_string(act.at(1))
                           + utils::double_to_string(act.at(2));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_grid_lin_3_true", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> act = utils::get_grid(2.0, 8.0, 2, "lin", true);
        std::string expected("   0.000000e+00   2.000000e+00   8.000000e+00");
        std::string actual = utils::double_to_string(act.at(0))
                           + utils::double_to_string(act.at(1))
                           + utils::double_to_string(act.at(2));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_grid_lin_3_true_no_duplicate", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> act = utils::get_grid(0.0, 8.0, 3, "lin", true);
        std::string expected("   0.000000e+00   4.000000e+00   8.000000e+00");
        std::string actual = utils::double_to_string(act.at(0))
                           + utils::double_to_string(act.at(1))
                           + utils::double_to_string(act.at(2));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_grid_lin_negative_false", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> act = utils::get_grid(-8.0, -2.0, 3, "lin", false);
        std::string expected("  -8.000000e+00  -5.000000e+00  -2.000000e+00");
        std::string actual = utils::double_to_string(act.at(0))
                           + utils::double_to_string(act.at(1))
                           + utils::double_to_string(act.at(2));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_grid_lin_negative_true", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> act = utils::get_grid(-8.0, -2.0, 2, "lin", true);
        std::string expected("  -8.000000e+00  -2.000000e+00   0.000000e+00");
        std::string actual = utils::double_to_string(act.at(0))
                           + utils::double_to_string(act.at(1))
                           + utils::double_to_string(act.at(2));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_grid_lin_negative_true_no_duplicate", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> act = utils::get_grid(-8.0, 0.0, 3, "lin", true);
        std::string expected("  -8.000000e+00  -4.000000e+00   0.000000e+00");
        std::string actual = utils::double_to_string(act.at(0))
                           + utils::double_to_string(act.at(1))
                           + utils::double_to_string(act.at(2));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_grid_log_3_false", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> act = utils::get_grid(10.0, 1000.0, 3, "log", false);
        std::string expected("   1.000000e+01   1.000000e+02   1.000000e+03");
        std::string actual = utils::double_to_string(act.at(0))
                           + utils::double_to_string(act.at(1))
                           + utils::double_to_string(act.at(2));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_grid_log_3_true", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> act = utils::get_grid(1.0, 10.0, 2, "log", true);
        std::string expected("   0.000000e+00   1.000000e+00   1.000000e+01");
        std::string actual = utils::double_to_string(act.at(0))
                           + utils::double_to_string(act.at(1))
                           + utils::double_to_string(act.at(2));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "syngrids_lin_lin", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t NIN = 3;
        double xin[NIN] = {2.0, 7.0, 9.0};

        std::vector<double> yin;
        yin.push_back(3.0);
        yin.push_back(8.0);
        yin.push_back(6.0);

        const size_t NOUT = 8;
        double xout[NOUT] = {1.0, 2.0, 3.0, 7.0, 8.0, 8.9, 9.0, 10.0};

        ArrDbl yout(NOUT);

        std::string xmode = "lin";
        std::string ymode = "lin";

        utils::syngrids(xin, yin, NIN, xmode, ymode, xout, yout, NOUT);

        ArrDbl yexp(NOUT);
        yexp[0] = 3.0;
        yexp[1] = 3.0;
        yexp[2] = 4.0;
        yexp[3] = 8.0;
        yexp[4] = 7.0;
        yexp[5] = 6.1;
        yexp[6] = 6.0;
        yexp[7] = 6.0;
        std::string expected(yexp.to_string());

        std::string actual(yout.to_string());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "syngrids_empty", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t NIN = 0;
        std::vector<double> xin, yin;

        const size_t NOUT = 8;
        double xout[NOUT] = {1.0, 2.0, 3.0, 7.0, 8.0, 8.9, 9.0, 10.0};

        ArrDbl yout(NOUT);

        std::string xmode = "lin";
        std::string ymode = "lin";

        utils::syngrids(xin, yin, NIN, xmode, ymode, xout, yout, NOUT);

        ArrDbl yexp(NOUT);
        yexp[0] = 0.0;
        yexp[1] = 0.0;
        yexp[2] = 0.0;
        yexp[3] = 0.0;
        yexp[4] = 0.0;
        yexp[5] = 0.0;
        yexp[6] = 0.0;
        yexp[7] = 0.0;
        std::string expected(yexp.to_string());

        std::string actual(yout.to_string());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rescale_y3_scale_factors", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rescale_y3.inc>
        std::vector<double> so(m); // interpolated scale factors
        utils::syngrids(hvold, sc, n, "lin", "lin", x, so, m);
        std::string actual, expected;
        std::vector<double> e(m);
        e[0] = 0.5;
        e[1] = 0.5;
        e[2] = 1.25;
        e[3] = 2.0;
        e[4] = 3.5;
        e[5] = 4.0;
        e[6] = 4.0;
        for (size_t i = 0; i < m; ++i)
        {
            expected += utils::double_to_string(e.at(i));
            actual   += utils::double_to_string(so.at(i));
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rescale_y3_scale_y", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rescale_y3.inc>
        utils::scale_y(hvold, sc, n, "lin", "lin", x, y, m);
        std::string actual, expected;
        std::vector<double> e(m);
        e[0] = 0.5 * 8.0;
        e[1] = 0.5 * 9.0;
        e[2] = 1.25 * 5.0;
        e[3] = 2.0 * 2.0;
        e[4] = 3.5 * 5.0;
        e[5] = 4.0 * 1.0;
        e[6] = 4.0 * 6.5;
        for (size_t i = 0; i < m; ++i)
        {
            expected += utils::double_to_string(e.at(i));
            actual   += utils::double_to_string(y.at(i));
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rescale_y3_shift_x", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rescale_y3.inc>
        std::vector<double> xnew(m);
        utils::shift_x(hvold, hvnew, n, x, xnew, m);
        std::string actual, expected;
        std::vector<double> e(m);
        e[0] = 1.5  +  1.5 * (2.0 - 3.0);
        e[1] = 1.5;
        e[2] = 1.5  +  1.5 * (4.0 - 3.0);
        e[3] = 4.5;
        e[4] = 4.5  +  1.25 * (8.0 - 5.0);
        e[5] = 9.5;
        e[6] = 9.5  +  1.25 * (9.5 - 9.0);
        for (size_t i = 0; i < m; ++i)
        {
            expected += utils::double_to_string(e.at(i));
            actual   += utils::double_to_string(xnew.at(i));
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rescale_y3", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rescale_y3.inc>
        std::vector<double> xnew(x);
        std::vector<double> ynew(m);
        utils::rescale(hvold, sc, hvnew, n, x, y, m, "lin", "lin", xnew, ynew, m);
        std::string actual, expected;
        std::vector<double> e(m);
        e[0] = 5.083333333333333;
        e[1] = 6.25;
        e[2] = 4.75;
        e[3] = 5.8;
        e[4] = 16.6;
        e[5] = 9.4;
        e[6] = 4.0;
        for (size_t i = 0; i < m; ++i)
        {
            expected += utils::double_to_string(e.at(i));
            actual   += utils::double_to_string(ynew.at(i));
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "planckian", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double hv = 1000.0; // eV
        double tev = 500.0; // eV
        double expected = 788906361433.20398; // W / (cm2 * sr * eV)
        double actual = utils::planckian(hv, tev);

        failed_test_count += t.check_equal_real_num(expected, actual, 1e-3);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "planckian0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double hv = 1000.0; // eV
        double tev = -1.0;  // eV
        double expected = 0.0; // W / (cm2 * sr * eV)
        double actual = utils::planckian(hv, tev);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bool_to_string_true", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        bool b(true);
        std::string expected("true");
        std::string actual(utils::bool_to_string(b));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bool_to_string_false", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        bool b(false);
        std::string expected("false");
        std::string actual(utils::bool_to_string(b));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "true_string_to_bool", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string b("tRuE");
        bool expected(true);
        bool actual(utils::string_to_bool(b));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "false_string_to_bool", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string b("FalSE");
        bool expected(false);
        bool actual(utils::string_to_bool(b));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "1_string_to_bool", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string b("1");
        bool expected(true);
        bool actual(utils::string_to_bool(b));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "0_string_to_bool", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string b("0");
        bool expected(false);
        bool actual(utils::string_to_bool(b));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "yes_string_to_bool", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string b("yEs");
        bool expected(true);
        bool actual(utils::string_to_bool(b));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "no_string_to_bool", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string b("nO");
        bool expected(false);
        bool actual(utils::string_to_bool(b));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_7_of_9", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<size_t> dim, indx; // dimension, index
        dim.push_back(9); // dimension #0
        indx.push_back(7);
        size_t expected(7);
        size_t actual(utils::many_to_one(dim, indx));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_0000_00", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::vector<size_t> indx;    // the "many" indices
        indx.push_back(0);
        indx.push_back(0);
        indx.push_back(0);
        indx.push_back(0);
        size_t expected(0);
        size_t actual(utils::many_to_one(dim, indx));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_2001_13", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::vector<size_t> indx;    // the "many" indices
        indx.push_back(2);
        indx.push_back(0);
        indx.push_back(0);
        indx.push_back(1);
        size_t expected(13);
        size_t actual(utils::many_to_one(dim, indx));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_3102_23", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::vector<size_t> indx;    // the "many" indices
        indx.push_back(3);
        indx.push_back(1);
        indx.push_back(0);
        indx.push_back(2);
        size_t expected(23);
        size_t actual(utils::many_to_one(dim, indx));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_3112_out_of_range", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::vector<size_t> indx;    // the "many" indices
        indx.push_back(3);
        indx.push_back(1);
        indx.push_back(1);
        indx.push_back(2);
        std::string expected = "out of range exception";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            size_t j = utils::many_to_one(dim, indx);
            std::cout << j << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = "out of range exception";
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_range_error", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::vector<size_t> indx;    // the "many" indices
        indx.push_back(3);
        indx.push_back(1);
        indx.push_back(0);
        std::string expected = "Error: many_to_one ranges do not conform:\n";
        expected += "dimensions =          4\nindices =          3";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            size_t j = utils::many_to_one(dim, indx);
            std::cout << j << std::endl;
        }
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "one_to_many_7_of_9", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<size_t> dim, indx; // dimension, index
        dim.push_back(9); // dimension #0
        size_t expected(7);
        indx = utils::one_to_many(dim, 7);
        size_t actual = indx.at(0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "one_to_many_00_0000", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::string expected(" 0 0 0 0");
        std::vector<size_t> indx = utils::one_to_many(dim, 0);
        std::string actual = utils::int_to_string(indx.at(0), ' ', 2)
                           + utils::int_to_string(indx.at(1), ' ', 2)
                           + utils::int_to_string(indx.at(2), ' ', 2)
                           + utils::int_to_string(indx.at(3), ' ', 2);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "one_to_many_13_2001", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::string expected(" 2 0 0 1");
        std::vector<size_t> indx = utils::one_to_many(dim, 13);
        std::string actual = utils::int_to_string(indx.at(0), ' ', 2)
                           + utils::int_to_string(indx.at(1), ' ', 2)
                           + utils::int_to_string(indx.at(2), ' ', 2)
                           + utils::int_to_string(indx.at(3), ' ', 2);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "one_to_many_23_3102", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::string expected(" 3 1 0 2");
        std::vector<size_t> indx = utils::one_to_many(dim, 23);
        std::string actual = utils::int_to_string(indx.at(0), ' ', 2)
                           + utils::int_to_string(indx.at(1), ' ', 2)
                           + utils::int_to_string(indx.at(2), ' ', 2)
                           + utils::int_to_string(indx.at(3), ' ', 2);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "one_to_many_out_of_range", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::string expected = "out of range exception";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            std::vector<size_t> indx = utils::one_to_many(dim, 24);
            std::cout << indx.size() << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = "out of range exception";
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "two_to_one_7_of_9", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<size_t> dim; // dimension
        dim.push_back(9); // dimension #0
        std::pair<size_t, size_t> p(0, 7); // the "pair" of indices
        size_t expected(7);
        size_t actual(utils::two_to_one(dim, p));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "two_to_one_00_0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::pair<size_t, size_t> p(0, 0); // the "pair" of indices
        size_t expected(0);
        size_t actual(utils::two_to_one(dim, p));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "two_to_one_20_6", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::pair<size_t, size_t> p(2, 0); // the "pair" of indices
        size_t expected(6);
        size_t actual(utils::two_to_one(dim, p));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "two_to_one_32_9", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::pair<size_t, size_t> p(3, 2); // the "pair" of indices
        size_t expected(9);
        size_t actual(utils::two_to_one(dim, p));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "two_to_one_range_error", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::string expected = "Error: two_to_one range error:\n";
        expected += "maximum =          3\nrequested =          4";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            std::pair<size_t, size_t> p(4, 0); // the "pair" of indices
            size_t j = utils::two_to_one(dim, p);
            std::cout << j << std::endl;
        }
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "two_to_one_21_out_of_range", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::pair<size_t, size_t> p(2, 1); // the "pair" of indices
        std::string expected = "out of range exception";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            size_t j = utils::two_to_one(dim, p);
            std::cout << j << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = "out of range exception";
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "one_to_two_7_of_9", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<size_t> dim; // dimension
        dim.push_back(9); // dimension #0
        std::string expected(" 0 7");
        std::pair<size_t, size_t> p = utils::one_to_two(dim, 7);
        std::string actual = utils::int_to_string(p.first, ' ', 2)
                           + utils::int_to_string(p.second, ' ', 2);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "one_to_two_0_00", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::string expected(" 0 0");
        std::pair<size_t, size_t> p = utils::one_to_two(dim, 0);
        std::string actual = utils::int_to_string(p.first, ' ', 2)
                           + utils::int_to_string(p.second, ' ', 2);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "one_to_two_6_20", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::string expected(" 2 0");
        std::pair<size_t, size_t> p = utils::one_to_two(dim, 6);
        std::string actual = utils::int_to_string(p.first, ' ', 2)
                           + utils::int_to_string(p.second, ' ', 2);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "one_to_two_9_32", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::string expected(" 3 2");
        std::pair<size_t, size_t> p = utils::one_to_two(dim, 9);
        std::string actual = utils::int_to_string(p.first, ' ', 2)
                           + utils::int_to_string(p.second, ' ', 2);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "one_to_two_out_of_range", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::string expected = "out of range exception";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            std::pair<size_t, size_t> p = utils::one_to_two(dim, 10);
            std::cout << p.first << " " << p.second << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = "out of range exception";
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "gaussian", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double x = 2.0, x0 = 4.0, sigma = 3.0;
        double expected = 0.10648266850745075;
        double actual = utils::gaussian(x, x0, sigma);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "convolution_range_error_in", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double fwhm = 0.0;
        std::vector<double> xin(6);
        std::vector<double> yin(5);
        ArrDbl xout(8);
        ArrDbl yout(8);
        std::string expected = "Error: convolution ranges do not match:";
        expected += "\nsize(xin):          6\nsize(yin):          5";
        expected += "\nsize(xout):          8\nsize(yout):          8";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            utils::convolution(fwhm, xin, yin, xout, yout);
        }
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "convolution_range_error_out", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double fwhm = 0.0;
        std::vector<double> xin(5);
        std::vector<double> yin(5);
        ArrDbl xout(7);
        ArrDbl yout(8);
        std::string expected = "Error: convolution ranges do not match:";
        expected += "\nsize(xin):          5\nsize(yin):          5";
        expected += "\nsize(xout):          7\nsize(yout):          8";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            utils::convolution(fwhm, xin, yin, xout, yout);
        }
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "convolution_syngrids_branch", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> xin;
        xin.push_back(2.0);
        xin.push_back(7.0);
        xin.push_back(9.0);

        std::vector<double> yin;
        yin.push_back(3.0);
        yin.push_back(8.0);
        yin.push_back(6.0);

        const size_t NOUT = 8;
        ArrDbl xout(NOUT);
        xout.at(0) = 1.0;
        xout.at(1) = 2.0;
        xout.at(2) = 3.0;
        xout.at(3) = 7.0;
        xout.at(4) = 8.0;
        xout.at(5) = 8.9;
        xout.at(6) = 9.0;
        xout.at(7) = 10.0;

        ArrDbl yout(NOUT);

        double fwhm = 0.0;
        utils::convolution(fwhm, xin, yin, xout, yout);

        ArrDbl yexp(NOUT);
        yexp[0] = 3.0;
        yexp[1] = 3.0;
        yexp[2] = 3.650186;
        yexp[3] = 8.0;
        yexp[4] = 6.928203;
        yexp[5] = 6.086928;
        yexp[6] = 6.0;
        yexp[7] = 6.0;
        std::string expected(yexp.to_string());

        std::string actual(yout.to_string());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "integrate_trapezoid_5_5", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <integ_trap.inc>
        double a = 5.0;
        double b = 5.0;
        double expected = 0.0;
        double actual = utils::integrate_trapezoid(a, b, x, y, n);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "integrate_trapezoid_1_7", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <integ_trap.inc>
        double a = 1.0;
        double b = 7.0;
        double expected = 34.0;
        double actual = utils::integrate_trapezoid(a, b, x, y, n);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "integrate_trapezoid_0_9", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <integ_trap.inc>
        double a = 0.0;
        double b = 9.0;
        double expected = 34.0;
        double actual = utils::integrate_trapezoid(a, b, x, y, n);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "integrate_trapezoid_1_3", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <integ_trap.inc>
        double a = 1.0;
        double b = 3.0;
        double expected = 10.0;
        double actual = utils::integrate_trapezoid(a, b, x, y, n);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "integrate_trapezoid_1.5_2.5", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <integ_trap.inc>
        double a = 1.5;
        double b = 2.5;
        double expected = 5.0;
        double actual = utils::integrate_trapezoid(a, b, x, y, n);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "integrate_trapezoid_2.5_1.5", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <integ_trap.inc>
        double a = 2.5;
        double b = 1.5;
        double expected = -5.0;
        double actual = utils::integrate_trapezoid(a, b, x, y, n);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "integrate_trapezoid_2_4.5", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <integ_trap.inc>
        double a = 2.0;
        double b = 4.5;
        double expected = 17.75;
        double actual = utils::integrate_trapezoid(a, b, x, y, n);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "integrate_trapezoid_7_3", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <integ_trap.inc>
        double a = 7.0;
        double b = 3.0;
        double expected = -24.0;
        double actual = utils::integrate_trapezoid(a, b, x, y, n);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "unit1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 51;
        std::string fname(cnststr::PATH + "UniTest/sp_unit.dat");
        std::ifstream infile(fname.c_str());
        std::vector<double> x(n), y(n), e(n), a(n);
        for (size_t i = 0; i < n; ++i) infile >> x.at(i) >> y.at(i);
        e = y;
        double fwhm = 1.0;
        utils::convolution(fwhm, x, y, x, a);
        std::string actual, expected;
        for (size_t i = 0; i < n; ++i)
        {
            expected += utils::double_to_string(e.at(i));
            actual   += utils::double_to_string(a.at(i));
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "unit10", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 51;
        std::string fname(cnststr::PATH + "UniTest/sp_unit.dat");
        std::ifstream infile(fname.c_str());
        fname = cnststr::PATH + "UniTest/sp_unit10.dat";
        std::ifstream expfile(fname.c_str());
        std::vector<double> x(n), y(n), e(n), a(n);
        for (size_t i = 0; i < n; ++i)
        {
            infile >> x.at(i) >> y.at(i);
            expfile >> x.at(i) >> e.at(i);
        }
        double fwhm = 10.0;
        utils::convolution(fwhm, x, y, x, a);
        std::string actual, expected;
        for (size_t i = 0; i < n; ++i)
        {
            expected += utils::double_to_string(e.at(i));
            actual   += utils::double_to_string(a.at(i));
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "convolved1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 2801;
        std::string fname(cnststr::PATH + "UniTest/sp_full.dat");
        std::ifstream infile(fname.c_str());
        std::vector<double> x(n), y(n), e(n), a(n);
        for (size_t i = 0; i < n; ++i) infile >> x.at(i) >> y.at(i);
        e = y;
        double fwhm = 1.0;
        utils::convolution(fwhm, x, y, x, a);
        std::string actual, expected;
        for (size_t i = 0; i < n; ++i)
        {
            expected += utils::double_to_string(e.at(i));
            actual   += utils::double_to_string(a.at(i));
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "convolved50", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 2801;
        std::string fname(cnststr::PATH + "UniTest/sp_full.dat");
        std::ifstream infile(fname.c_str());
        fname = cnststr::PATH + "UniTest/sp_full50.dat";
        std::ifstream expfile(fname.c_str());
        std::vector<double> x(n), y(n), e(n), a(n);
        for (size_t i = 0; i < n; ++i)
        {
            infile >> x.at(i) >> y.at(i);
            expfile >> x.at(i) >> e.at(i);
        }
        double fwhm = 50.0;
        utils::convolution(fwhm, x, y, x, a);
        std::string actual, expected;
        for (size_t i = 0; i < n; ++i)
        {
            expected += utils::double_to_string(e.at(i));
            actual   += utils::double_to_string(a.at(i));
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_contained_in_true", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <is_contained_in.inc>
        bool expected(true);
        bool actual(utils::is_contained_in(4.0, intervals));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_contained_in_false", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <is_contained_in.inc>
        bool expected(false);
        bool actual(utils::is_contained_in(7.0, intervals));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "replace_in_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected("BeginMidEnd");
        std::string actual("BeginMiddleEnd");
        utils::replace_in_string(actual, "Middle", "Mid");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "replace_in_string_containing_end_of_line", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected("BeginMidEnd");
        std::string actual("Begin\nEnd");
        utils::replace_in_string(actual, "\n", "Mid");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "replace_in_string_not_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected("replace_in_string: old substring not found");
        std::string actual = UNCAUGHT_EXCEPTION;
        std::string s("Test string");
        try
        {
            utils::replace_in_string(s, "substring not present", "replacement");
        }
        catch (const std::invalid_argument &invarg)
        {
            actual = invarg.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normalize_default_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> f{99.0, 1.0};
        std::vector<double> fn = utils::normalize(f);
        size_t expected = 2;
        size_t actual = fn.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normalize_default_0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> f{99.0, 1.0};
        std::vector<double> fn = utils::normalize(f);
        double expected = 0.99;
        double actual = fn.at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normalize_default_1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> f{99.0, 1.0};
        std::vector<double> fn = utils::normalize(f);
        double expected = 0.01;
        double actual = fn.at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normalize_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> f{99.0, 1.0};
        std::vector<double> fn = utils::normalize(f, 2.0);
        size_t expected = 2;
        size_t actual = fn.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normalize_0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> f{99.0, 1.0};
        std::vector<double> fn = utils::normalize(f, 2.0);
        double expected = 1.98;
        double actual = fn.at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normalize_1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::vector<double> f{99.0, 1.0};
        std::vector<double> fn = utils::normalize(f, 2.0);
        double expected = 0.02;
        double actual = fn.at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_utils.cpp
