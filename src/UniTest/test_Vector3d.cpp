/*=============================================================================

test_Vector3d.cpp
Definitions for unit, integration, and regression tests for class Vector3d.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 23 October 2014
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

#include <test_Vector3d.h>
#include <Test.h>

#include <constants.h>

void test_Vector3d(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Vector3d";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_x", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v;
        double expected = 1.0;
        v.setx(expected);
        double actual = v.getx();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_y", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v;
        double expected = 2.0;
        v.sety(expected);
        double actual = v.gety();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_z", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v;
        double expected = 3.0;
        v.setz(expected);
        double actual = v.getz();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_big", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double expected = 1.0e100;
        double actual = Vector3d::get_big();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_small", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double expected = 1.0e-100;
        double actual = Vector3d::get_small();
        double eqt = 1.0e-115;

        failed_test_count += t.check_equal_real_num(expected, actual, eqt);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_x", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(1.0, 2.0, 3.0);
        double expected = 1.0;
        double actual = v.getx();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_y", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(1.0, -2.0, 3.0);
        double expected = -2.0;
        double actual = v.gety();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_z", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(1.0, 2.0, 3.0);
        double expected = 3.0;
        double actual = v.getz();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor0_x", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v;
        double expected = 0.0;
        double actual = v.getx();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor0_y", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v;
        double expected = 0.0;
        double actual = v.gety();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor0_z", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v;
        double expected = 0.0;
        double actual = v.getz();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_spherical", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d actual(cnst::PI * cnst::THIRD, 5.0 * cnst::PI * cnst::THIRD);
        Vector3d expected(0.43301270189221874, -0.75, 0.5);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "norm", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(-3.0, 4.0, -12.0);
        double expected = 13.0;
        double actual = v.norm();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "abs_diff", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d x(7.0, 2.0, -5.0);
        Vector3d y(4.0, -2.0, -17.0);
        double expected = 13.0;
        double actual = x.abs_diff(y);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(7.0e-11, 0.0, -500.0);
        std::string expected = "   7.000000e-11   0.000000e+00  -5.000000e+02";
        std::string actual = v.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_big", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        double big = Vector3d::get_big();
        Vector3d v(big, -big, big);
        std::string expected = "  1.000000e+100 -1.000000e+100  1.000000e+100";
        std::string actual = v.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "copy_ctor", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        Vector3d expected(0.0, 4.0, -12.0);
        Vector3d actual(v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "assignment", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        Vector3d expected(0.0, 4.0, -12.0);
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "unary_plus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        Vector3d expected(0.0, 4.0, -12.0);
        Vector3d actual = +v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "unary_minus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        Vector3d expected(0.0, -4.0, 12.0);
        Vector3d actual = -v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_equal", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d x(0.0, 4.0, -12.0);
        Vector3d y(1.0, -2.0, 0.0);
        x += y;
        Vector3d expected(1.0, 2.0, -12.0);
        Vector3d actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "plus_equal_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d x(0.0, 4.0, -12.0);
        Vector3d y(1.0, -2.0, 0.0);
        Vector3d expected(1.0, 2.0, -12.0);
        Vector3d actual = (x += y);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_equal", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d x(0.0, 4.0, -12.0);
        Vector3d y(1.0, -2.0, 0.0);
        x -= y;
        Vector3d expected(-1.0, 6.0, -12.0);
        Vector3d actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "minus_equal_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d x(0.0, 4.0, -12.0);
        Vector3d y(1.0, -2.0, 0.0);
        Vector3d expected(-1.0, 6.0, -12.0);
        Vector3d actual = (x -= y);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "binary_plus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d x(0.0, 4.0, -12.0);
        Vector3d y(1.0, -2.0, 0.0);
        Vector3d expected(1.0, 2.0, -12.0);
        Vector3d actual = x + y;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "binary_minus", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d x(0.0, 4.0, -12.0);
        Vector3d y(1.0, -2.0, 0.0);
        Vector3d expected(-1.0, 6.0, -12.0);
        Vector3d actual = x - y;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        double f = 2.0;
        v *= f;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_double_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        double f = 2.0;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = (v *= f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        float f = 2.0;
        v *= f;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        int f = 2;
        v *= f;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_equal_size_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        size_t f = 2;
        v *= f;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        double f = 2.0;
        v /= f;
        Vector3d expected(0.0, 2.0, -6.0);
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_double0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        double f = 0.0;
        v /= f;
        double big = Vector3d::get_big();
        Vector3d expected(big, big, big);
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_double_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        double f = 2.0;
        Vector3d expected(0.0, 2.0, -6.0);
        Vector3d actual = (v /= f);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        float f = 2.0;
        v /= f;
        Vector3d expected(0.0, 2.0, -6.0);
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        int f = 2;
        v /= f;
        Vector3d expected(0.0, 2.0, -6.0);
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_equal_size_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        size_t f = 2;
        v /= f;
        Vector3d expected(0.0, 2.0, -6.0);
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        double f = 2.0;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = v * f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        float f = 2.0;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = v * f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        int f = 2;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = v * f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "times_size_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        size_t f = 2;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = v * f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "double_times", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        double f = 2.0;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = f * v;
    
        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "float_times", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        float f = 2.0;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = f * v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "int_times", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        int f = 2;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = f * v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size_t_times", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        size_t f = 2;
        Vector3d expected(0.0, 8.0, -24.0);
        Vector3d actual = f * v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        double f = 2.0;
        Vector3d expected(0.0, 2.0, -6.0);
        Vector3d actual = v / f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_double0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        double f = 0.0;
        double big = Vector3d::get_big();
        Vector3d expected(big, big, big);
        Vector3d actual = v / f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        float f = 2.0;
        Vector3d expected(0.0, 2.0, -6.0);
        Vector3d actual = v / f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        int f = 2;
        Vector3d expected(0.0, 2.0, -6.0);
        Vector3d actual = v / f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "divide_size_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 4.0, -12.0);
        size_t f = 2;
        Vector3d expected(0.0, 2.0, -6.0);
        Vector3d actual = v / f;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normalize", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(3.0, -4.0, -12.0);
        double f = 13.0;
        Vector3d expected(v.getx()/f, v.gety()/f, v.getz()/f);
        v.normalize();
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normalize_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(3.0, -4.0, -12.0);
        double f = 13.0;
        Vector3d expected(v.getx()/f, v.gety()/f, v.getz()/f);
        Vector3d actual = v.normalize();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normalize0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 0.0, 0.0);
        Vector3d expected = v;
        v.normalize();
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "reverse", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(3.0, -4.0, -12.0);
        Vector3d expected(-3.0, 4.0, 12.0);
        v.reverse();
        Vector3d actual = v;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "reverse_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(3.0, -4.0, -12.0);
        Vector3d expected(-3.0, 4.0, 12.0);
        Vector3d actual = v.reverse();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "unit", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(3.0, -4.0, -12.0);
        double f = 13.0;
        Vector3d expected(v.getx()/f, v.gety()/f, v.getz()/f);
        Vector3d actual = v.unit();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "unit0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(0.0, 0.0, 0.0);
        Vector3d expected = v;
        Vector3d actual = v.unit();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "scalar_product", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d x(2.0, -2.0, 1.0);
        Vector3d y(2.0, -3.0, -7.0);
        double expected = 3.0;
        double actual = x * y;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_equal", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d x(-2.0, 1.0, -1.0);
        Vector3d y(1.0, 3.0, -1.0);
        x %= y;
        Vector3d expected(2.0, -3.0, -7.0);
        Vector3d actual = x;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_equal_trans", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d x(-2.0, 1.0, -1.0);
        Vector3d y(1.0, 3.0, -1.0);
        Vector3d expected(2.0, -3.0, -7.0);
        Vector3d actual = (x %= y);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_product", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d x(-2.0, 1.0, -1.0);
        Vector3d y(1.0, 3.0, -1.0);
        Vector3d expected(2.0, -3.0, -7.0);
        Vector3d actual = x % y;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "mixed_product", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d w(2.0, -2.0, 1.0);
        Vector3d x(-2.0, 1.0, -1.0);
        Vector3d y(1.0, 3.0, -1.0);
        double expected = 3.0;
        double actual = w * (x % y);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "double_cross_product", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d a(2.0, -2.0, 1.0);
        Vector3d b(-2.0, 1.0, -1.0);
        Vector3d c(1.0, 3.0, -1.0);
        Vector3d expected = b * (a * c)  -  (a * b) * c;
        Vector3d actual = a % (b % c);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cos_angle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d a(2.0, -2.0, 1.0);
        Vector3d b(2.0, -3.0, -7.0);
        double expected = 1.0 / sqrt(62.0); // 0.12700012700019;
        double actual = a.cos_angle(b);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "angle_rad", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d a(2.0, -2.0, 1.0);
        Vector3d b(2.0, -3.0, -7.0);
        double expected = acos(1.0 / sqrt(62.0)); // 1.443452299660215;
        double actual = a.angle_rad(b);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cos_angle0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d a(0.0, 0.0, 0.0);
        Vector3d b(2.0, -3.0, -7.0);
        double expected = -4.0;
        double actual = a.cos_angle(b);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cos_angle00", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d a(0.0, 0.0, 0.0);
        Vector3d b(2.0, -3.0, -7.0);
        double expected = -4.0;
        double actual = b.cos_angle(a);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "angle_rad0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d a(0.0, 0.0, 0.0);
        Vector3d b(2.0, -3.0, -7.0);
        double expected = 1.0e100;
        double actual = a.angle_rad(b);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "parallel_to_unit_vector", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d a(2.0, -2.0, 1.0);
        Vector3d n(3.0/13.0, 4.0/13.0, 12.0/13.0); // |n| = 1
        double expected = 0.7692307692307693;
        double actual = a * n;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "distance", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d a(2.0, -2.0, 1.0);
        Vector3d b(5.0, 2.0, -11.0);
        double expected = 13.0;
        double actual = a.distance(b);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "right_normal", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(-3.0, -4.0, 0.0);
        Vector3d expected = Vector3d(-0.8, 0.6, 0.0);
        Vector3d actual = v.right_normal();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_turn_clockwise", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d head(-3.0, -4.0, 0.0);
        Vector3d tail(1.0, 2.0, 0.0);
        Vector3d v = Vector3d(-5.0, 1.0, 0.0);
        int expected = -1;
        int actual = v.get_turn(tail, head);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_turn_counterclockwise", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d tail(-3.0, -4.0, 0.0);
        Vector3d head(1.0, 2.0, 0.0);
        Vector3d v = Vector3d(-5.0, 1.0, 0.0);
        int expected = 1;
        int actual = v.get_turn(tail, head);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_turn_none", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d tail(-3.0, 4.0, 0.0);
        Vector3d head(1.0, 2.0, 0.0);
        Vector3d v = Vector3d(-1.0, 3.0, 0.0);
        int expected = 0;
        int actual = v.get_turn(tail, head);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "check0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d expected(0.0, 0.0, 0.0);
        Vector3d actual = Vector3d(-1.0, 3.0, 5.0);
        actual.set0();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "parallel", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d e(3.0, 4.0, 12.0);
        Vector3d v(-1.0, 2.0, -3.0);
        Vector3d expected(-0.5502958579881656,
                          -0.73372781065088755,
                          -2.2011834319526624);
        Vector3d actual = v.parallel_to(e);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "perpendicular", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d e(3.0, 4.0, 12.0);
        Vector3d v(-1.0, 2.0, -3.0);
        Vector3d expected(-0.4497041420118344,
                          2.73372781065088755,
                          -0.7988165680473376);
        Vector3d actual = v.perpendicular_to(e);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_between_negative", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d tail(2.0, -2.0, 2.0);
        Vector3d head(4.0, -4.0, 4.0);
        Vector3d w = Vector3d(3.0, -3.0, 3.0);
        bool expected = true;
        bool actual = w.is_between(tail, head);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_between_zero", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d tail(2.0, -2.0, 2.0);
        Vector3d head(4.0, -4.0, 4.0);
        Vector3d w = Vector3d(2.0, -2.0, 2.0);
        bool expected = true;
        bool actual = w.is_between(tail, head);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_between_positive", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d tail(2.0, -2.0, 2.0);
        Vector3d head(4.0, -4.0, 4.0);
        Vector3d w = Vector3d(1.0, -1.0, 1.0);
        bool expected = false;
        bool actual = w.is_between(tail, head);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_rz", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d w(0.5, sqrt(3.0)/2.0, 2.0); // phi = 60 degrees
        Vector3d expected(1.0, 2.0, 0.0);
        Vector3d actual = w.get_rz();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "linear_Vector3d_fit", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {   // pmh_2019_1031; phi = 60 degrees
        Vector3d a(0.5, sqrt(3.0)/2.0, 4.0);
        Vector3d b(1.0, sqrt(3.0), 0.0);
        double f = (a-b).norm() / 4.0;
        Vector3d expected(0.625, 0.625*sqrt(3.0), 3.0);
        Vector3d actual = linear_Vector3d_fit(f, a, b);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Vector3d.cpp
