/*=============================================================================

test_Table.cpp
Definitions for unit, integration, and regression tests for class Table.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 9 January 2015
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

#include <Test.h>
#include "../src/Table.h"
#include "../src/constants.h"

#include <stdexcept>

void test_Table(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "Table";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        size_t expected = 5;
        size_t actual = tbl.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        size_t expected = 0;
        tbl.clear();
        size_t actual = tbl.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "deuterium_Z", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 1;
        int actual = tbl.get_Z("d");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "deuterium_A", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        double expected = 2.0141017778;
        double actual = tbl.get_A("d");

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "deuterium_N", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 1;
        int actual = tbl.get_N("d");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "deuterium_F", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected("z01");
        std::string actual = tbl.get_F("d");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "helium3_Z", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 2;
        int actual = tbl.get_Z("he3");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "helium3_A", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        double expected = 3.0160293191;
        double actual = tbl.get_A("he3");

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "helium3_N", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 1;
        int actual = tbl.get_N("he3");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "helium3_F", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected("z02");
        std::string actual = tbl.get_F("he3");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "argon_Z", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 18;
        int actual = tbl.get_Z("ar");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "argon_A", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        double expected = 39.948;
        double actual = tbl.get_A("ar");

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "argon_N", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 22;
        int actual = tbl.get_N("ar");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "argon_F", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected("z18");
        std::string actual = tbl.get_F("ar");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "heavy_water_Z", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 10;
        int actual = tbl.get_Z("heavy_water");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "heavy_water_A", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        double expected = 20.0276035556;
        double actual = tbl.get_A("heavy_water");

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "heavy_water_N", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 10;
        int actual = tbl.get_N("heavy_water");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "heavy_water_F", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected("d2o");
        std::string actual = tbl.get_F("heavy_water");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "not_present_Z", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected = "air is not present in Table";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            int i = tbl.get_Z("air");
            std::cout << i << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "not_present_A", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected = "air is not present in Table";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = tbl.get_A("air");
            std::cout << x << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "not_present_N", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected = "air is not present in Table";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            int i = tbl.get_N("air");
            std::cout << i << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "not_present_F", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected = "air is not present in Table";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            std::string s = tbl.get_F("air");
            std::cout << s << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

// end test_Table.cpp
