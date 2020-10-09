/*=============================================================================

test_Table.cpp
Definitions for unit, integration, and regression tests for class Table.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 9 January 2015
Last modified on 6 October 2020

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

#include <test_Table.h>
#include <Test.h>

#include <constants.h>

#include <stdexcept>
#include <vector>

void test_Table(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Table";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        size_t expected = 5;
        size_t actual = tbl.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
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

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 1;
        int actual = tbl.get_Z("d");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "deuterium_A", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        double expected = 2.0141017778;
        double actual = tbl.get_A("d");

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "deuterium_N", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 1;
        int actual = tbl.get_N("d");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "deuterium_F", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected("z01");
        std::string actual = tbl.get_F("d");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "helium3_Z", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 2;
        int actual = tbl.get_Z("he3");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "helium3_A", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        double expected = 3.0160293191;
        double actual = tbl.get_A("he3");

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "helium3_N", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 1;
        int actual = tbl.get_N("he3");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "helium3_F", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected("z02");
        std::string actual = tbl.get_F("he3");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "argon_Z", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 18;
        int actual = tbl.get_Z("ar");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "argon_A", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        double expected = 39.948;
        double actual = tbl.get_A("ar");

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "argon_N", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 22;
        int actual = tbl.get_N("ar");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "argon_F", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected("z18");
        std::string actual = tbl.get_F("ar");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "heavy_water_Z", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 10;
        int actual = tbl.get_Z("heavy_water");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "heavy_water_A", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        double expected = 20.0276035556;
        double actual = tbl.get_A("heavy_water");

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "heavy_water_N", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        int expected = 10;
        int actual = tbl.get_N("heavy_water");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "heavy_water_F", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::string expected("d2o");
        std::string actual = tbl.get_F("heavy_water");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "not_present_Z", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
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

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
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

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
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

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
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

{
    Test t(GROUP, "atom_to_mass_fractions_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::vector<std::string> mat{"d", "ar"};
        std::vector<double> a{0.99, 0.01};
        std::vector<double> m = tbl.atom_to_mass(mat, a);

        int expected = 2;
        int actual = static_cast<int>(m.size());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "atom_to_mass_fractions_0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::vector<std::string> mat{"d", "ar"};
        std::vector<double> a{0.99, 0.01};
        std::vector<double> m = tbl.atom_to_mass(mat, a);

        double expected = 0.8330938426918375;
        double actual = m.at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "atom_to_mass_fractions_1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::vector<std::string> mat{"d", "ar"};
        std::vector<double> a{0.99, 0.01};
        std::vector<double> m = tbl.atom_to_mass(mat, a);

        double expected = 0.16690615730816252;
        double actual = m.at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "mass_to_atom_fractions_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::vector<std::string> mat{"d", "ar"};
        std::vector<double> m{0.8330938426918375, 0.16690615730816252};
        std::vector<double> a = tbl.mass_to_atom(mat, m);

        int expected = 2;
        int actual = static_cast<int>(a.size());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "mass_to_atom_fractions_0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::vector<std::string> mat{"d", "ar"};
        std::vector<double> m{0.8330938426918375, 0.16690615730816252};
        std::vector<double> a = tbl.mass_to_atom(mat, m);

        double expected = 0.99;
        double actual = a.at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "mass_to_atom_fractions_1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");
        std::vector<std::string> mat{"d", "ar"};
        std::vector<double> m{0.8330938426918375, 0.16690615730816252};
        std::vector<double> a = tbl.mass_to_atom(mat, m);

        double expected = 0.01;
        double actual = a.at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "number_of_elements", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");

        size_t expected = 4;
        size_t actual = tbl.get_elements().size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "element0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");

        int expected = 1;
        int actual = tbl.get_elements().at(0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "element1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");

        int expected = 2;
        int actual = tbl.get_elements().at(1);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "element2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");

        int expected = 10;
        int actual = tbl.get_elements().at(2);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "element3", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Data/");
        Table tbl(path, path, "Table.txt");

        int expected = 18;
        int actual = tbl.get_elements().at(3);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Table.cpp
