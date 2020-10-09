/*=============================================================================

test_ArrDbl.cpp
Definitions for unit, integration, and regression tests for class ArrDbl.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 3 December 2014
Last modified on 9 October 2020

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

#include <test_ArrDbl.h>
#include <Test.h>

#include <constants.h>
#include <utils.h>
#include <Vector3d.h>

#include <cstdlib>
#include <memory>
#include <stdexcept>

void test_ArrDbl(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "ArrDbl";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a(3);
        size_t expected = 3;
        size_t actual = a.size();
 
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_value", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a(999);
        double expected = 0.0;
        double actual = a.at(998);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_out_of_range", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a(3);
        std::string expected = "out of range exception";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = a.at(3);
            std::cout << x << std::endl;
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
    Test t(GROUP, "push_back", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a;
        a.push_back(1.0);
        a.push_back(9.0);
        a.push_back(-7.0);
        a.push_back(4.0);
        double expected = -7.0;
        double actual = a.at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------
    
{
    Test t(GROUP, "emplace_back", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a;
        a.emplace_back(1.0);
        a.emplace_back(9.0);
        a.emplace_back(-7.0);
        a.emplace_back(4.0);
        double expected = -7.0;
        double actual = a.at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------
           
{
    Test t(GROUP, "set_get_at", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a(999);
        double expected = -7.0;
        a.at(998) = -7.0;
        double actual = a.at(998);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------
           
{
    Test t(GROUP, "set_get_index_operator", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a(999);
        double expected = -7.0;
        a[998] = -7.0;
        double actual = a[998];

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "abs_diff", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(2);
        x.at(0) = 7.0;
        x.at(1) = -2.0;
        ArrDbl y(1);
        y.at(0) = -5.0;
        double expected = 13.0;
        double actual = y.abs_diff(x);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a(2);
        a.at(0) = 7.0e-11;
        std::string expected = "   7.000000e-11\n   0.000000e+00";
        std::string actual = a.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_file", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 2.0;
        x.at(1) = 0.0;
        x.at(2) = -1.0;

        std::string fname(cnststr::PATH + "UniTest/Output/ArrDbl-to_file.txt");
        #ifndef WIN
        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test "
                      << "ArrDbl-to_file" << std::endl;
            exit(EXIT_FAILURE);
        }
        #endif
        std::string header("# ArrDbl-to_file.txt");
        x.to_file(fname, header);
        std::string expected(header);
        expected += "\n   2.000000e+00\n   0.000000e+00\n  -1.000000e+00";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "copy_ctor", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a(2);
        a.at(0) = 7.0e-11;
        ArrDbl b(a);
        std::string expected = "   7.000000e-11\n   0.000000e+00";
        std::string actual = b.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
            
{
    Test t(GROUP, "assignment", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        auto a = std::make_shared<ArrDbl>(2);
        a->at(0) = 7.0e-11;
        auto b = *a;
        std::string expected = "   7.000000e-11\n   0.000000e+00";
        std::string actual = b.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "assign_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl actual(5);
        double f = -7.0;
        actual.assign(5, f);
        ArrDbl expected(5);
        expected.at(0) = -7.0;
        expected.at(1) = -7.0;
        expected.at(2) = -7.0;
        expected.at(3) = -7.0;
        expected.at(4) = -7.0;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "assign_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl actual;
        float f = -7.0;
        actual.assign(5, f);
        ArrDbl expected(5);
        expected.at(0) = -7.0;
        expected.at(1) = -7.0;
        expected.at(2) = -7.0;
        expected.at(3) = -7.0;
        expected.at(4) = -7.0;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "assign_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl actual(2);
        int f = -7;
        actual.at(0) = 3.0;
        actual.assign(5, f);
        ArrDbl expected(5);
        expected.at(0) = -7.0;
        expected.at(1) = -7.0;
        expected.at(2) = -7.0;
        expected.at(3) = -7.0;
        expected.at(4) = -7.0;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "assign_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a(2);
        int f = -7;
        a.assign(5, f);
        size_t expected(5);
        size_t actual(a.size());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fill_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl actual(5);
        double f = -4.0;
        actual.assign(5, f);
        f = -7.0;
        actual.fill(f);
        ArrDbl expected(5);
        expected.at(0) = -7.0;
        expected.at(1) = -7.0;
        expected.at(2) = -7.0;
        expected.at(3) = -7.0;
        expected.at(4) = -7.0;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fill_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl actual;
        float f = -4.0;
        actual.assign(5, f);
        f = -7.0;
        actual.fill(f);
        ArrDbl expected(5);
        expected.at(0) = -7.0;
        expected.at(1) = -7.0;
        expected.at(2) = -7.0;
        expected.at(3) = -7.0;
        expected.at(4) = -7.0;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fill_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl actual(2);
        int f = -4;
        actual.at(0) = 3.0;
        actual.assign(5, f);
        f = -7;
        actual.fill(f);
        ArrDbl expected(5);
        expected.at(0) = -7.0;
        expected.at(1) = -7.0;
        expected.at(2) = -7.0;
        expected.at(3) = -7.0;
        expected.at(4) = -7.0;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fill_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a(2);
        int f = -4;
        a.assign(5, f);
        f = -7;
        a.fill(f);
        size_t expected(5);
        size_t actual(a.size());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_out_of_range", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a(2);
        int f = -7;
        a.assign(5, f);
        a.clear();
        std::string expected = "out of range exception";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = a.at(0);
            std::cout << x << std::endl;
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
    Test t(GROUP, "clear_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl a(2);
        int f = -7;
        a.assign(5, f);
        a.clear();
        size_t expected(0);
        size_t actual(a.size());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "unary_plus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(2);
        x.at(0) = 7.0;
        x.at(1) = -2.0;
        ArrDbl expected = x;
        ArrDbl actual = +x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "unary_minus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 7.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl expected(3);
        expected.at(0) = -7.0;
        expected.at(1) = 0.0;
        expected.at(2) = 2.0;

        ArrDbl actual = -x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_equal_ArrDbl", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 7.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = -2.0;
        y.at(1) = 4.0;
        y.at(2) = 1.0;

        x += y;

        ArrDbl expected(3);
        expected.at(0) = 5.0;
        expected.at(1) = 4.0;
        expected.at(2) = -1.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "self_plus_equal_ArrDbl", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 7.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        x += x;

        ArrDbl expected(3);
        expected.at(0) = 14.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_equal_ArrDbl_range_error", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        ArrDbl y;
        std::string expected = "Error: ArrDbl ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          0";
        std::string actual = UNCAUGHT_EXCEPTION;

        try {x += y;}
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_equal_ArrDbl_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 7.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = -2.0;
        y.at(1) = 4.0;
        y.at(2) = 1.0;

        ArrDbl expected(3);
        expected.at(0) = 5.0;
        expected.at(1) = 4.0;
        expected.at(2) = -1.0;

        ArrDbl actual = (x += y);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_equal_ArrDbl", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 7.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = -2.0;
        y.at(1) = 4.0;
        y.at(2) = 1.0;

        x -= y;

        ArrDbl expected(3);
        expected.at(0) = 9.0;
        expected.at(1) = -4.0;
        expected.at(2) = -3.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_equal_ArrDbl_range_error", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        ArrDbl y;
        std::string expected = "Error: ArrDbl ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          0";
        std::string actual = UNCAUGHT_EXCEPTION;

        try {x -= y;}
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_equal_ArrDbl_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 7.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = -2.0;
        y.at(1) = 4.0;
        y.at(2) = 1.0;

        ArrDbl expected(3);
        expected.at(0) = 9.0;
        expected.at(1) = -4.0;
        expected.at(2) = -3.0;

        ArrDbl actual = (x -= y);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_ArrDbl", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = 0.5;
        y.at(1) = 5.0;
        y.at(2) = -2.0;

        x *= y;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = 4.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "self_times_equal_ArrDbl", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        x *= x;

        ArrDbl expected(3);
        expected.at(0) = 16.0;
        expected.at(1) = 0.0;
        expected.at(2) = 4.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_ArrDbl_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = 0.5;
        y.at(1) = 5.0;
        y.at(2) = -2.0;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = 4.0;

        ArrDbl actual = (x *= y);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_ArrDbl_range_error", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        ArrDbl y;
        std::string expected = "Error: ArrDbl ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          0";
        std::string actual = UNCAUGHT_EXCEPTION;

        try {x *= y;}
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_ArrDbl", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = 0.5;
        y.at(1) = 0.0;
        y.at(2) = -2.0;

        x /= y;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = -Vector3d::get_big();
        expected.at(2) = 1.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_ArrDbl_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = 0.5;
        y.at(1) = 0.0;
        y.at(2) = -2.0;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = -Vector3d::get_big();
        expected.at(2) = 1.0;

        ArrDbl actual = (x /= y);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_ArrDbl_range_error", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        ArrDbl y;
        std::string expected = "Error: ArrDbl ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          0";
        std::string actual = UNCAUGHT_EXCEPTION;

        try {x /= y;}
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "binary_plus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 7.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = -2.0;
        y.at(1) = 4.0;
        y.at(2) = 1.0;

        ArrDbl expected(3);
        expected.at(0) = 5.0;
        expected.at(1) = 4.0;
        expected.at(2) = -1.0;

        ArrDbl actual = x + y;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "binary_plus_range_error", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        ArrDbl y;
        std::string expected = "Error: ArrDbl ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          0";
        std::string actual = UNCAUGHT_EXCEPTION;

        try {x = x + y;}
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "binary_minus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 7.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = -2.0;
        y.at(1) = 4.0;
        y.at(2) = 1.0;

        ArrDbl expected(3);
        expected.at(0) = 9.0;
        expected.at(1) = -4.0;
        expected.at(2) = -3.0;

        ArrDbl actual = x - y;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "binary_minus_range_error", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        ArrDbl y;
        std::string expected = "Error: ArrDbl ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          0";
        std::string actual = UNCAUGHT_EXCEPTION;

        try {x = x - y;}
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "binary_times_ArrDbl", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 1.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = 0.5;
        y.at(1) = 0.0;
        y.at(2) = -2.0;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = 4.0;

        ArrDbl actual = x * y;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "binary_times_range_error", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        ArrDbl y;
        std::string expected = "Error: ArrDbl ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          0";
        std::string actual = UNCAUGHT_EXCEPTION;

        try {x = x * y;}
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "binary_divide_ArrDbl", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl y(3);
        y.at(0) = 0.5;
        y.at(1) = 0.0;
        y.at(2) = -2.0;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = -Vector3d::get_big();
        expected.at(2) = 1.0;

        ArrDbl actual = x / y;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "binary_divide_range_error", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        ArrDbl y;
        std::string expected = "Error: ArrDbl ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          0";
        std::string actual = UNCAUGHT_EXCEPTION;

        try {x = x / y;}
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_equal_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        x += f;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_equal_double_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;

        ArrDbl actual = (x += f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_equal_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        x += f;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_equal_float_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;

        ArrDbl actual = (x += f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_equal_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        x += f;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_equal_int_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;

        ArrDbl actual = (x += f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_equal_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        x -= f;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = -2.0;
        expected.at(2) = -4.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_equal_double_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = -2.0;
        expected.at(2) = -4.0;

        ArrDbl actual = (x -= f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_equal_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        x -= f;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = -2.0;
        expected.at(2) = -4.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_equal_float_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = -2.0;
        expected.at(2) = -4.0;

        ArrDbl actual = (x -= f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_equal_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        x -= f;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = -2.0;
        expected.at(2) = -4.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_equal_int_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = -2.0;
        expected.at(2) = -4.0;

        ArrDbl actual = (x -= f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        x *= f;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_double_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;

        ArrDbl actual = (x *= f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        x *= f;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_float_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;

        ArrDbl actual = (x *= f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        x *= f;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_int_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;

        ArrDbl actual = (x *= f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        x /= f;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = -1.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_double0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 0.0;

        x /= f;

        double BIG = -Vector3d::get_big();
        ArrDbl expected(3);
        expected.at(0) = BIG;
        expected.at(1) = BIG;
        expected.at(2) = BIG;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_double_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = -1.0;

        ArrDbl actual = (x /= f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        x /= f;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = -1.0;

        ArrDbl actual = x;
 
        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_float0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 0.0;

        x /= f;

        double BIG = -Vector3d::get_big();
        ArrDbl expected(3);
        expected.at(0) = BIG;
        expected.at(1) = BIG;
        expected.at(2) = BIG;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_float_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = -1.0;

        ArrDbl actual = (x /= f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        x /= f;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = -1.0;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_int0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 0;

        x /= f;

        double BIG = -Vector3d::get_big();
        ArrDbl expected(3);
        expected.at(0) = BIG;
        expected.at(1) = BIG;
        expected.at(2) = BIG;

        ArrDbl actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_int_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = -1.0;

        ArrDbl actual = (x /= f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;
        ArrDbl actual = x + f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;
        ArrDbl actual = x + f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;
        ArrDbl actual = x + f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = -2.0;
        expected.at(2) = -4.0;
        ArrDbl actual = x - f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = -2.0;
        expected.at(2) = -4.0;
        ArrDbl actual = x - f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = -2.0;
        expected.at(2) = -4.0;
        ArrDbl actual = x - f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;
        ArrDbl actual = x * f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;
        ArrDbl actual = x * f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;
        ArrDbl actual = x * f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = -1.0;
        ArrDbl actual = x / f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = -1.0;
        ArrDbl actual = x / f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = 2.0;
        expected.at(1) = 0.0;
        expected.at(2) = -1.0;
        ArrDbl actual = x / f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "double_plus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;
        ArrDbl actual = f + x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "float_plus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;
        ArrDbl actual = f + x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "int_plus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = 6.0;
        expected.at(1) = 2.0;
        expected.at(2) = 0.0;
        ArrDbl actual = f + x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "double_minus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = -2.0;
        expected.at(1) = 2.0;
        expected.at(2) = 4.0;
        ArrDbl actual = f - x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "float_minus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = -2.0;
        expected.at(1) = 2.0;
        expected.at(2) = 4.0;
        ArrDbl actual = f - x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "int_minus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = -2.0;
        expected.at(1) = 2.0;
        expected.at(2) = 4.0;
        ArrDbl actual = f - x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "double_times", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;
        ArrDbl actual = f * x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "float_times", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;
        ArrDbl actual = f * x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "int_times", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = 8.0;
        expected.at(1) = 0.0;
        expected.at(2) = -4.0;
        ArrDbl actual = f * x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "double_divide", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        double f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 0.5;
        expected.at(1) = -Vector3d::get_big();
        expected.at(2) = -1.0;
        ArrDbl actual = f / x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "float_divide", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        float f = 2.0;

        ArrDbl expected(3);
        expected.at(0) = 0.5;
        expected.at(1) = -Vector3d::get_big();
        expected.at(2) = -1.0;
        ArrDbl actual = f / x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "int_divide", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;
        int f = 2;

        ArrDbl expected(3);
        expected.at(0) = 0.5;
        expected.at(1) = -Vector3d::get_big();
        expected.at(2) = -1.0;
        ArrDbl actual = f / x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "log", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 4.0;
        x.at(1) = 0.0;
        x.at(2) = -2.0;

        ArrDbl expected(3);
        expected.at(0) = 1.3862943611198906;
        expected.at(1) = -Vector3d::get_big();
        expected.at(2) = -Vector3d::get_big();
        ArrDbl actual(3);
        actual = log(x);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "exp", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        ArrDbl x(3);
        x.at(0) = 2.0;
        x.at(1) = 0.0;
        x.at(2) = -1.0;

        ArrDbl expected(3);
        expected.at(0) = 7.38905609893065;
        expected.at(1) = 1.0;
        expected.at(2) = 0.36787944117144233;
        ArrDbl actual(3);
        actual = exp(x);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_ArrDbl.cpp
