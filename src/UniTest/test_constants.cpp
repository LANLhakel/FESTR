/*=============================================================================

test_constants.cpp
Definitions for tests for global numeric constants

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 28 January 2020
Last modified on 2 October 2020

Copyright (c) 2018, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

=============================================================================*/

//  Note: only use trimmed strings for names

#include <test_constants.h>
#include <Test.h>

//-----------------------------------------------------------------------------

void test_constants(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "constants";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "U", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double expected = 1.660539e-24;
        double actual = cnst::U;

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e-34);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "CV", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double expected = 2.99792458e10;
        double actual = cnst::CV;

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e2);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "INT_WIDTH", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = 11;
        int actual = cnst::INT_WIDTH;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "SCALE_EQT", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double expected = 1.0e-5;
        double actual = cnst::SCALE_EQT;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "THIRD", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double expected = 1.0 / 3.0;
        double actual = cnst::THIRD;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "PI", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double expected = 3.141592653589793;
        double actual = cnst::PI;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "TWO_PI", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double expected = 2.0 * 3.141592653589793;
        double actual = cnst::TWO_PI;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "FOUR_PI", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double expected = 4.0 * 3.141592653589793;
        double actual = cnst::FOUR_PI;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "FOUR_THIRDS_PI", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double expected = 4.0 * 3.141592653589793 / 3.0;
        double actual = cnst::FOUR_THIRDS_PI;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "PATH", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected = "./";
        std::string actual = cnststr::PATH;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "DASHES", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected = "---------------------------------------------";
        std::string actual = cnststr::DASHES;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ZONE_SEPARATOR", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected =
            "\n---------------------------------------------\n";
        std::string actual = cnststr::ZONE_SEPARATOR;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_constants.cpp
