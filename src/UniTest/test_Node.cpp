/*=============================================================================

test_Node.cpp
Definitions for unit, integration, and regression tests for class Node.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 19 November 2014
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
#include "../src/Node.h"

void test_Node(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "Node";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_i", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Node n;
        size_t expected = 7;
        n.seti(expected);
        size_t actual = n.geti();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Node n;
        Vector3d expected(1.0, -1.0, 0.0);
        n.setr(expected);
        Vector3d actual = n.getr();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_v", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Node n;
        Vector3d expected(-1.0, 0.0, 1.0);
        n.setv(expected);
        Vector3d actual = n.getv();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "abs_diff", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d r(12.0, 4.0, -3.0);
        Vector3d v(-4.0, 3.0, 12.0);
        Node x(1, r, v);
        Node y;
        double expected = 27.0;
        double actual = x.abs_diff(y);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(7.0e-11, 0.0, -500.0);
        Node n(1, v, v);
        std::string expected = "   7.000000e-11   0.000000e+00  -5.000000e+02";
                    expected+= "   7.000000e-11   0.000000e+00  -5.000000e+02";
        std::string actual = n.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_i0_r0_v0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d zero;
        Node expected(0, zero, zero);
        Node actual;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_v0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d r(12.0, 4.0, -3.0);
        Vector3d zero;
        Node expected(0, r, zero);
        Node actual(0, r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "copy_ctor", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d r(12.0, 4.0, -3.0);
        Vector3d v(-4.0, 3.0, 12.0);
        Node n(0, r, v);
        Node expected(0, r, v);
        Node actual(n);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "assignment", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d r(12.0, 4.0, -3.0);
        Vector3d v(-4.0, 3.0, 12.0);
        Node n(0, r, v);
        Node expected(0, r, v);
        Node actual = n;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

}

// end test_Node.cpp
