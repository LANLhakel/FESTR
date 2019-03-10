/*=============================================================================

test_ArrSection.cpp
Definitions for unit, integration, and regression tests for class ArrSection.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 25 July 2016
Last modified on 3 March 2019

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.8 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

//  Note: only use trimmed strings for names

#include "../../common/UniTest/Test.h"
#include "../src/utilities.h"

#include "ArrSection.h"
#include <string>
#include <cstdlib>

void test_ArrSection(int &failed_test_count, int &disabled_test_count)
{

const std::string PATH = "./";
const std::string GROUP = "ArrSection";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_lower_limit", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(-3, 5, false);
        int expected = -3;
        int actual = a.get_lower_limit();
 
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_upper_limit", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(-3, 5, false);
        int expected = 5;
        int actual = a.get_upper_limit();
 
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_upper_limit_with_swap", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(5, -3, false);
        int expected = 5;
        int actual = a.get_upper_limit();
 
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_lower_limit_with_swap", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(5, -3, false);
        int expected = -3;
        int actual = a.get_lower_limit();
 
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(-3, 5, false);
        int expected = 9;
        int actual = a.size();
 
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_value", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(-3, 5, false);
        double expected = 0.0;
        double actual = a[0];

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------
           
{
    Test t(GROUP, "set_get_at_p4", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(-3, 5, false);
        double expected = -1.0;
        a[4] = expected;
        double actual = a[4];

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------
           
{
    Test t(GROUP, "set_get_at_m2", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(-3, 5, false);
        double expected = -7.0;
        a[-2] = expected;
        double actual = a(-2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "beyond_lower_with_false", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(2, 3, false);
        a[2] = 7.0;
        a[3] = -2.0;
        double expected = 7.0;
        double actual = a(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "beyond_upper_with_false", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(2, 3, false);
        a[2] = 7.0;
        a[3] = -2.0;
        double expected = -2.0;
        double actual = a(4);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "beyond_lower_with_true", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(2, 3, true);
        a[2] = 7.0;
        a[3] = -2.0;
        double expected = 0.0;
        double actual = a(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "beyond_upper_with_true", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(2, 3, true);
        a[2] = 7.0;
        a[3] = -2.0;
        double expected = 0.0;
        double actual = a(4);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "abs_diff", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(2, 3, false);
        a[2] = 7.0;
        a[3] = -2.0;
        ArrSection b(-1, -1, false);
        b[-1] = -5.0;
        double expected = 13.0;
        double actual = b.abs_diff(a);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(2, 3, false);
        a[2] = 7.0e-11;
        a[3] = -1.0e8;
        std::string expected = "   7.000000e-11\n  -1.000000e+08";
        std::string actual = a.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_file", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(0, 2, false);
        a[0] = 2.0;
        a[1] = 0.0;
        a[2] = -1.0;

        std::string fname(PATH + "ArrSection_to_file.txt");

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test "
                      << "ArrSection_to_file" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::string header("# ArrSection_to_file.txt");
        a.to_file(fname, header);
        std::string expected(header);
        expected += "\n   2.000000e+00\n   0.000000e+00\n  -1.000000e+00";
        std::string actual(utils::file_to_string(fname));

        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test "
                      << "ArrSection_to_file" << std::endl;
            exit(EXIT_FAILURE);
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "copy_ctor", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(-3, -2, false);
        a[-3] = 7.0e-11;
        ArrSection b(a);
        std::string expected = "   7.000000e-11\n   0.000000e+00";
        std::string actual = b.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
            
{
    Test t(GROUP, "assignment", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(-3, -2, false);
        a[-3] = 7.0e-11;
        ArrSection b = a;
        std::string expected = "   7.000000e-11\n   0.000000e+00";
        std::string actual = b.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fill", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        ArrSection a(-3, -2, false);
        a.fill(7.0e-11);
        std::string expected = "   7.000000e-11\n   7.000000e-11";
        std::string actual = a.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}
