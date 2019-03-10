/*=============================================================================

test_Grid.cpp
Definitions for unit, integration, and regression tests for class Grid.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 21 November 2014
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
#include "../src/Grid.h"
#include "../src/constants.h"

#include <stdexcept>

void test_Grid(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "Grid";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "add_get_node", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        Node n;
        Vector3d r(1.0, 2.0, 3.0);
        Vector3d v(-0.2, 0.3, -0.4);
        Node expected(1, r, v);
        g.add_node(n);
        g.add_node(expected);
        Node actual = g.get_node(1);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "add_get_node_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        Node n;
        Vector3d r(1.0, 2.0, 3.0);
        Vector3d v(-0.2, 0.3, -0.4);
        g.add_node(n);
        std::string expected = "out of range exception";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            g.get_node(1);
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
    Test t(GROUP, "replace_node", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        Node n;
        Vector3d r(1.0, 2.0, 3.0);
        Vector3d v(-0.2, 0.3, -0.4);
        Node expected(1, r, v);
        g.add_node(n);
        g.add_node(expected);
        r = Vector3d(-1.0, -2.0, -3.0);
        v = Vector3d(0.2, -0.3, 0.4);
        expected = Node(1, r, v);
        g.replace_node(expected);
        Node actual = g.get_node(1);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        size_t expected = 0;
        size_t actual = g.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size1", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        Vector3d r(1.0, 2.0, 3.0);
        Vector3d v(-0.2, 0.3, -0.4);
        Node n(0, r, v);
        g.add_node(n);
        size_t expected = 1;
        size_t actual = g.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "abs_diff", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Grid g, h;
        Vector3d r(12.0, 4.0, -3.0);
        Vector3d v(-4.0, 3.0, 12.0);
        Node x(1, r, v);
        Node y;
        g.add_node(x);
        g.add_node(y);
        h.add_node(y);
        double expected = 28.0;
        double actual = g.abs_diff(h);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        Node y;
        g.add_node(y);
        Vector3d r(12.0, 4.0, -3.0);
        Vector3d v(-0.04, 0.0, 12.0);
        Node x(1, r, v);
        g.add_node(x);
        std::string expected= "   0.000000e+00   0.000000e+00   0.000000e+00";
                    expected+="   0.000000e+00   0.000000e+00   0.000000e+00";
                    expected+="\n";
                    expected+="   1.200000e+01   4.000000e+00  -3.000000e+00";
                    expected+="  -4.000000e-02   0.000000e+00   1.200000e+01";
        std::string actual = g.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "copy_ctor", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        Node y;
        g.add_node(y);
        Vector3d r(12.0, 4.0, -3.0);
        Vector3d v(-0.04, 0.0, 12.0);
        Node x(1, r, v);
        g.add_node(x);
        Grid h(g);
        std::string expected = g.to_string();
        std::string actual = h.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "assignment", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        Node y;
        g.add_node(y);
        Vector3d r(12.0, 4.0, -3.0);
        Vector3d v(-0.04, 0.0, 12.0);
        Node x(1, r, v);
        g.add_node(x);
        Grid h = g;
        std::string expected = g.to_string();
        std::string actual = h.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        Node n;
        Vector3d r(1.0, 2.0, 3.0);
        Vector3d v(-0.2, 0.3, -0.4);
        n = Node(0, r, v);
        g.add_node(n);
        n = Node(1, r, v);
        g.add_node(n);
        g.clear();
        size_t expected = 0;
        size_t actual = g.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_Node", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        Node n;
        Vector3d r(1.0, 2.0, 3.0);
        Vector3d v(-0.2, 0.3, -0.4);
        n = Node(0, r, v);
        g.add_node(n);
        n = Node(1, r, v);
        g.add_node(n);
        g.clear();
        std::string expected("out of range exception");
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            g.get_node(0);
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
    Test t(GROUP, "load_Hydro1_Grid0_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        Grid g(path, tlabel);
        size_t expected = 8;
        size_t actual = g.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Grid0_Node5", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        Grid g(path, tlabel);
        Vector3d v(1.0, 0.0, 1.0);
        Node expected(5, v, v);
        Node actual = g.get_node(5);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

}

// end test_Grid.cpp
