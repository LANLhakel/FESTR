/*=============================================================================

test_Objective.cpp
Definitions for unit, integration, and regression tests for class Objective.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 24 June 2015
Last modified on 13 March 2019

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
#include "../src/Objective.h"
#include "../src/constants.h"
#include "../src/ArrDbl.h"

#include <stdexcept>

void test_Objective(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "Objective";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj;
        std::string expected("no_name");
        std::string actual = obj.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "oname_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj;
        std::string expected("no_name");
        std::string actual = obj.get_oname();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "path_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj;
        std::string expected("no_path");
        std::string actual = obj.get_path();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "my_id_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj;
        int expected(-1);
        int actual = obj.get_my_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "weight_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj;
        double expected(0.0);
        double actual = obj.get_weight();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj;
        size_t expected(0);
        size_t actual = obj.get_size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_x_present_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj;
        std::string expected("false");
        std::string actual(obj.is_x_present());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_w_present_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj;
        std::string expected("false");
        std::string actual(obj.is_w_present());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_rescale", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj;
        bool expected(false);
        bool actual = obj.get_rescale();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_best_scale", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj;
        double expected(1.0);
        double actual = obj.get_best_scale();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_XYW", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        std::string s("ObjectiveNameXYW\nweight   2.000000e+00\ndata");
        s += "\n   3.000000e+02   3.000000e+00   1.000000e-01";
        s += "\n   6.000000e+02   7.000000e+00   4.000000e-01";
        std::string expected(s);
        std::string actual = obj.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_x_present_XYW", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        std::string expected("true");
        std::string actual(obj.is_x_present());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_w_present_XYW", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        std::string expected("true");
        std::string actual(obj.is_w_present());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_YW", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameYW", cnst::PATH + "UniTest/Goal1/", 1, 3.0,
                      false, true, false);
        std::string s("ObjectiveNameYW\nweight   3.000000e+00\ndata");
        s += "\n   3.000000e+00   1.000000e-01";
        s += "\n   7.000000e+00   4.000000e-01";
        std::string expected(s);
        std::string actual = obj.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_x_present_YW", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameYW", cnst::PATH + "UniTest/Goal1/", 1, 3.0,
                      false, true, false);
        std::string expected("false");
        std::string actual(obj.is_x_present());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_w_present_YW", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameYW", cnst::PATH + "UniTest/Goal1/", 1, 3.0,
                      false, true, false);
        std::string expected("true");
        std::string actual(obj.is_w_present());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_XY", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXY", cnst::PATH + "UniTest/Goal1/", 1, 4.0,
                      true, false, false);
        std::string s("ObjectiveNameXY\nweight   4.000000e+00\ndata");
        s += "\n   3.000000e+02   6.000000e+00   1.000000e+00";
        s += "\n   6.000000e+02   1.100000e+01   1.000000e+00";
        std::string expected(s);
        std::string actual = obj.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_x_present_XY", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXY", cnst::PATH + "UniTest/Goal1/", 1, 4.0,
                      true, false, false);
        std::string expected("true");
        std::string actual(obj.is_x_present());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_w_present_XY", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXY", cnst::PATH + "UniTest/Goal1/", 1, 4.0,
                      true, false, false);
        std::string expected("false");
        std::string actual(obj.is_w_present());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_Y", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameY", cnst::PATH + "UniTest/Goal1/", 1, 5.0,
                      false, false, false);
        std::string s("ObjectiveNameY\nweight   5.000000e+00\ndata");
        s += "\n   3.000000e+00   1.000000e+00";
        s += "\n   7.000000e+00   1.000000e+00";
        std::string expected(s);
        std::string actual = obj.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_x_present_Y", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameY", cnst::PATH + "UniTest/Goal1/", 1, 5.0,
                      false, false, false);
        std::string expected("false");
        std::string actual(obj.is_x_present());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_w_present_Y", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameY", cnst::PATH + "UniTest/Goal1/", 1, 5.0,
                      false, false, false);
        std::string expected("false");
        std::string actual(obj.is_w_present());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "abs_diff", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj1("ObjectiveNameYW", cnst::PATH + "UniTest/Goal1/", 1, 3.0,
                       false, true, false);
        Objective obj2("ObjectiveNameXY", cnst::PATH + "UniTest/Goal1/", 1, 4.0,
                       true, false, false);
        double expected(7.0);
        double actual = obj1.abs_diff(obj2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "oname", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameY", cnst::PATH + "UniTest/Goal1/", 1, 5.0,
                      false, false, false);
        std::string expected("ObjectiveNameY");
        std::string actual = obj.get_oname();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "path", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameY", cnst::PATH + "UniTest/Goal1/", 1, 5.0,
                      false, false, false);
        std::string expected(cnst::PATH + "UniTest/Goal1/");
        std::string actual = obj.get_path();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "my_id", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameY", cnst::PATH + "UniTest/Goal1/", 1, 5.0,
                      false, false, false);
        int expected(1);
        int actual = obj.get_my_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "weight", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameY", cnst::PATH + "UniTest/Goal1/", 1, 5.0,
                      false, false, false);
        double expected(5.0);
        double actual = obj.get_weight();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameY", cnst::PATH + "UniTest/Goal1/", 1, 5.0,
                      false, false, false);
        size_t expected(2);
        size_t actual = obj.get_size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_x_at", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        double expected(300.0);
        double actual = obj.get_x_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_y_at", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        double expected(3.0);
        double actual = obj.get_y_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_w_at", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        double expected(0.1);
        double actual = obj.get_w_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_fabs_array", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 2;
        double a[n] = {2.0, 1.0};
        double expected(5.0);
        double actual = obj.get_fabs(a, n);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_fabs_array_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 3;
        double a[n] = {2.0, 1.0, 0.0};
        std::string expected = "Error: Objective ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          2";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = obj.get_fabs(a, n);
            std::cout << x;
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
    Test t(GROUP, "get_fabs_vector", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        std::vector<double> a;
        a.push_back(2.0);
        a.push_back(1.0);
        size_t n = a.size();
        double expected(5.0);
        double actual = obj.get_fabs(a, n);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_fabs_vector_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        std::vector<double> a;
        a.push_back(2.0);
        a.push_back(1.0);
        a.push_back(0.0);
        size_t n = a.size();
        std::string expected = "Error: Objective ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          2";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = obj.get_fabs(a, n);
            std::cout << x;
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
    Test t(GROUP, "get_fabs_ArrDbl", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 2;
        ArrDbl a(n);
        a.at(0) = 2.0;
        a.at(1) = 1.0;
        double expected(5.0);
        double actual = obj.get_fabs(a, n);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_fabs_ArrDbl_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 3;
        ArrDbl a(n);
        a[0] = 2.0;
        a[1] = 1.0;
        a[0] = 0.0;
        std::string expected = "Error: Objective ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          2";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = obj.get_fabs(a, n);
            std::cout << x;
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
    Test t(GROUP, "get_chi2_array", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 2;
        double a[n] = {2.0, 1.0};
        double expected(29.0);
        double actual = obj.get_chi2(a, n);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_chi2_array_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 3;
        double a[n] = {2.0, 1.0, 0.0};
        std::string expected = "Error: Objective ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          2";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = obj.get_chi2(a, n);
            std::cout << x;
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
    Test t(GROUP, "get_fitness_array", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 2;
        double a[n] = {2.0, 1.0};
        double expected(-29.0);
        double actual = obj.get_fitness(a, n);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_fitness_array_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 3;
        double a[n] = {2.0, 1.0, 0.0};
        std::string expected = "Error: Objective ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          2";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = obj.get_fitness(a, n);
            std::cout << x;
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
    Test t(GROUP, "get_chi2_vector", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        std::vector<double> a;
        a.push_back(2.0);
        a.push_back(1.0);
        size_t n = a.size();
        double expected(29.0);
        double actual = obj.get_chi2(a, n);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_chi2_vector_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        std::vector<double> a;
        a.push_back(2.0);
        a.push_back(1.0);
        a.push_back(0.0);
        size_t n = a.size();
        std::string expected = "Error: Objective ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          2";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = obj.get_chi2(a, n);
            std::cout << x;
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
    Test t(GROUP, "get_fitness_vector", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        std::vector<double> a;
        a.push_back(2.0);
        a.push_back(1.0);
        size_t n = a.size();
        double expected(-29.0);
        double actual = obj.get_fitness(a, n);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_fitness_vector_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        std::vector<double> a;
        a.push_back(2.0);
        a.push_back(1.0);
        a.push_back(0.0);
        size_t n = a.size();
        std::string expected = "Error: Objective ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          2";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = obj.get_fitness(a, n);
            std::cout << x;
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
    Test t(GROUP, "get_chi2_ArrDbl", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 2;
        ArrDbl a(n);
        a.at(0) = 2.0;
        a.at(1) = 1.0;
        double expected(29.0);
        double actual = obj.get_chi2(a, n);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_chi2_ArrDbl_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 3;
        ArrDbl a(n);
        a[0] = 2.0;
        a[1] = 1.0;
        a[0] = 0.0;
        std::string expected = "Error: Objective ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          2";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = obj.get_chi2(a, n);
            std::cout << x;
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
    Test t(GROUP, "get_fitness_ArrDbl", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 2;
        ArrDbl a(n);
        a.at(0) = 2.0;
        a.at(1) = 1.0;
        double expected(-29.0);
        double actual = obj.get_fitness(a, n);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_fitness_ArrDbl_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Objective obj("ObjectiveNameXYW", cnst::PATH + "UniTest/Goal1/", 1, 2.0,
                      true, true, false);
        const size_t n = 3;
        ArrDbl a(n);
        a[0] = 2.0;
        a[1] = 1.0;
        a[0] = 0.0;
        std::string expected = "Error: Objective ranges do not conform:\n";
        expected += "size1 =          3\nsize2 =          2";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = obj.get_fitness(a, n);
            std::cout << x;
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
    Test t(GROUP, "get_best_fitness_update_yes", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "objective1.inc"
        double expected(-29.0);
        double actual = obj.get_best_fitness();

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_best_case_update_yes", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "objective1.inc"
        size_t expected(5);
        size_t actual = obj.get_best_case();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_best_fitness_update_no", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "objective2.inc"
        double expected(-29.0);
        double actual = obj.get_best_fitness();

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_best_case_update_no", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "objective2.inc"
        size_t expected(5);
        size_t actual = obj.get_best_case();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

// end test_Objective.cpp
