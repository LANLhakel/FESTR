/*=============================================================================

test_Sphere.cpp
Definitions for unit, integration, and regression tests for class Sphere.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 21 November 2014
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

#include <test_Sphere.h>
#include <Test.h>

#include <constants.h>
#include <Grid.h>
#include <utils.h>

#include <fstream>
#include <stdexcept>

void test_Sphere(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Sphere";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_r", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        double expected = 1.0;
        s->setr(expected);
        double actual = s->getr();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_v", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        double expected = 2.0;
        s->setv(expected);
        double actual = s->getv();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_n", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        int expected = -1;
        s->setr(4.0);
        s->setn(expected);
        int actual = s->getn();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_r0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        double expected = 0.0;
        double actual = s->getr();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_v0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        double expected = 0.0;
        double actual = s->getv();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_n0", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        int expected = 0;
        int actual = s->getn();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_n_bad_input", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        s->setn(2);
        int expected = 0;
        int actual = s->getn();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_my_zone", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Sphere>();
        size_t expected = 7;
        f->set_my_zone(expected);
        size_t actual = f->get_my_zone();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_my_id", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Sphere>();
        short int expected = 7;
        f->set_my_id(expected);
        short int actual = f->get_my_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_check_my_zone", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t mz = 6;
        short int mi = 9;
        FacePtr f = std::make_shared<Sphere>(mz, mi);
        size_t expected = mz;
        size_t actual = f->get_my_zone();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_check_my_id", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t mz = 6;
        short int mi = 9;
        FacePtr f = std::make_shared<Sphere>(mz, mi);
        short int expected = mi;
        short int actual = f->get_my_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_check_r0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t mz = 6;
        short int mi = 9;
        FacePtr f = std::make_shared<Sphere>(mz, mi);
        double expected = 0.0;
        double actual = std::dynamic_pointer_cast<Sphere>(f)->getr();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_check_v0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t mz = 6;
        short int mi = 9;
        FacePtr f = std::make_shared<Sphere>(mz, mi);
        double expected = 0.0;
        double actual = std::dynamic_pointer_cast<Sphere>(f)->getv();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_check_n0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t mz = 6;
        short int mi = 9;
        FacePtr f = std::make_shared<Sphere>(mz, mi);
        int expected = 0;
        int actual = std::dynamic_pointer_cast<Sphere>(f)->getn();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Sphere>();
        size_t expected = 0;
        size_t actual = f->size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(1.0, 2.0, 3.0);
        Node n0(3, v);
        Node n1(5, v, v);
        FacePtr f = std::make_shared<Sphere>();
        f->add_node(n0.geti());
        f->add_node(n1.geti());
        size_t expected = 2;
        size_t actual = f->size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_curved", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        FacePtr f = std::make_shared<Sphere>();
        bool expected = true;
        bool actual = f->is_curved(g);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_flat", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Grid g;
        FacePtr f = std::make_shared<Sphere>();
        bool expected = false;
        bool actual = f->is_flat(g);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_node_id", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(1.0, 2.0, 3.0);
        Node n0(3, v);
        Node n1(5, v, v);
        FacePtr f = std::make_shared<Sphere>();
        f->add_node(n0.geti());
        f->add_node(n1.geti());
        size_t expected = 5;
        size_t actual = f->get_node(1);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_node_id_out_of_range", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(1.0, 2.0, 3.0);
        Node n0(3, v);
        Node n1(5, v, v);
        FacePtr f = std::make_shared<Sphere>();
        f->add_node(n0.geti());
        f->add_node(n1.geti());
        std::string expected = "out of range exception";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            size_t n = f->get_node(2);
            std::cout << n;
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
    Test t(GROUP, "abs_diff", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Sphere>(3, 1);
        FacePtr g = std::make_shared<Sphere>(4, 5);
        f->add_node(6);
        g->add_node(2);
        g->add_node(9);
        g->add_node(4);
        double expected = 37.0;
        double actual = f->abs_diff(*g);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_no_neighbors", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>(3, 1);
        FacePtr f = s;
        f->add_node(98765);
        s->setr(6.0);
        s->setv(-0.9);
        std::string expected =  "Sphere\n          3          1\n";
        expected += "      98765\n          neighbors          0\n";
        expected += "   6.000000e+00  -9.000000e-01";
        std::string actual = f->to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_with_neighbor", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>(3, 1);
        FacePtr f = s;
        f->add_node(98765);
        s->setr(6.0);
        s->setv(-0.9);
        s->add_neighbor(4, 7);
        std::string expected =  "Sphere\n          3          1\n";
        expected += "      98765\n          neighbors          1\n";
        expected += "          4          7\n";
        expected += "   6.000000e+00  -9.000000e-01";
        std::string actual = f->to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr expected = std::make_shared<Sphere>(0, -2);
        FacePtr actual = std::make_shared<Sphere>();

        failed_test_count += t.check_equal_real_obj(*expected, *actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "assignment", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr expected = std::make_shared<Sphere>(4, 5);
        expected->add_node(2);
        expected->add_node(9);
        expected->add_node(4);
        FacePtr actual = std::make_shared<Sphere>();
        *actual = *expected;

        failed_test_count += t.check_equal_real_obj(*expected, *actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "add_get_neighboring_zone", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Sphere>(3, 1);
        f->add_neighbor(2, 4);
        f->add_neighbor(9, 5);
        size_t expected = 9;
        size_t actual = f->get_neighbor(1).my_zone;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "add_get_neighboring_Sphere", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Sphere>(3, 1);
        f->add_neighbor(2, 4);
        f->add_neighbor(9, 5);
        short int expected = 5;
        short int actual = f->get_neighbor(1).my_id;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "neighbor_count", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Sphere>(3, 1);
        size_t expected = 0;
        size_t actual = f->num_nbr();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "add_get_neighbor_out_of_range", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Sphere>(3, 1);
        f->add_neighbor(2, 4);
        f->add_neighbor(9, 5);
        std::string expected = "out of range exception";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            FaceID n = f->get_neighbor(5);
            std::cout << n.my_zone << " " << n.my_id;
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
    Test t(GROUP, "center_position", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(3.0, 2.0, 1.0);

        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);

        Vector3d expected(3.0, 2.0, 1.0);
        Vector3d actual = s->center_position(g);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "center_velocity", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d r, v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(-7.0, 1.0, 5.0);

        n = Node(1, r, v);
        g.add_node(n);
        f->add_node(1);

        Vector3d expected(-7.0, 1.0, 5.0);
        Vector3d actual = s->center_velocity(g);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "area2_normal", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g

        v = Vector3d(3.0, 5.0, -7.0);
        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(0.5);
        s->setn(-2);
        Vector3d expected(-2.0*cnst::PI, 0.0, 0.0);
        Vector3d actual = f->area2_normal_center(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "area2_normal0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Sphere>();
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g

        v = Vector3d(0.5, 0.0, 0.0);
        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        Vector3d expected;
        f->area2_normal_center(g, v);
        Vector3d actual(v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normal", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        s->setr(-6.0);
        Grid g;

        Vector3d expected(-1.0, 0.0, 0.0);
        Vector3d actual = s->normal(g);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "area", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(5.0, 2.0, -3.0);

        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(0.5);

        double expected = cnst::PI;
        double actual = s->area(g);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "signed_distance_positive", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(3.0, 2.0, 1.0);

        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(9.0);

        v = Vector3d(6.0, -2.0, -11.0);
        double expected = 4.0;
        double actual = f->distance(g, v);
        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "signed_distance_negative", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(3.0, 2.0, 1.0);

        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(-9.0);

        v = Vector3d(6.0, -2.0, -11.0);
        double expected = -4.0;
        double actual = f->distance(g, v);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "signed_distance_point_inside", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(3.0, 2.0, 1.0);

        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(15.0);

        v = Vector3d(6.0, -2.0, -11.0);
        double expected = -2.0;
        double actual = f->distance(g, v);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "signed_distance_point_at_center", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(3.0, 2.0, 1.0);

        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(15.0);

        v = Vector3d(3.0, 2.0, 1.0);
        double expected = -15.0;
        double actual = f->distance(g, v);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "has_point_above", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(3.0, 2.0, 1.0);
        
        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(9.0);
        s->setn(1);

        v = Vector3d(6.0, -2.0, -11.0);
        bool expected = true;
        bool actual = f->has_above(g, v);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "has_point_below", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(3.0, 2.0, 1.0);

        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(9.0);
        s->setn(-1);

        v = Vector3d(6.0, -2.0, -11.0);
        bool expected = true;
        bool actual = f->has_below(g, v);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "subpoint", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(1.0, 2.0, 3.0); // Sphere center

        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(-10.0);

        v = Vector3d(4.0, 2.0, -1.0); // test point
        Vector3d expected = Vector3d(7.0, 2.0, -5.0);
        Vector3d actual = f->subpoint(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "subpoint_from_center", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(1.0, 2.0, 3.0); // Sphere center

        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(5.0);

        v = Vector3d(1.0, 2.0, 3.0); // test point
        Vector3d expected = Vector3d(-1.0e100, -1.0e100, -1.0e100);
        Vector3d actual = f->subpoint(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "face_point", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        v = Vector3d(1.0, 2.0, 3.0); // Sphere center

        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(-10.0);

        v = Vector3d(4.0, 2.0, -1.0); // test point
        Vector3d expected = Vector3d(7.0, 2.0, -5.0);
        Vector3d actual = f->face_point(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "contains", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g

        n = Node(1, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(5.0);

        v = Vector3d(4.0, 0.0, -3.0);
        bool expected = true; // for any point v relative to any Sphere
        bool actual = f->contains(g, v);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_none_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(7.0, 7.0, 28.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0); // current Ray direction
        double expected = -1.0e100;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_none_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(7.0, 7.0, 28.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0); // current Ray direction
        Vector3d expected = Vector3d(-1.0e100, -1.0e100, -1.0e100);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_none_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(7.0, 7.0, 28.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0); // current Ray direction
        FaceID expected(4, 3);
        FaceID actual = f->intercept(g, p, u, EQT, fid).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_none_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(7.0, 7.0, 28.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0); // current Ray direction
        bool expected = false;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(4.0, 3.0, 16.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0); // current Ray direction
        double expected = -1.0e100;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e0);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(4.0, 3.0, 16.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0); // current Ray direction
        Vector3d expected = Vector3d(-1.0e100, -1.0e100, -1.0e100);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 1.0e0);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(4.0, 3.0, 16.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0); // current Ray direction
        bool expected = false;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_positive_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, 1.0, 10.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0); // current Ray direction
        double expected = 2.56019662378358;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_positive_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, 1.0, 10.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0); // current Ray direction
        Vector3d expected = Vector3d(2.5, -6.6805898713507395,
                                     12.560196623783579);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_positive_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, 1.0, 10.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0); // current Ray direction
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, 34.0, -1.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0);  // current Ray direction
        double expected = 6.439803376216421;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, 34.0, -1.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0);  // current Ray direction
        Vector3d expected = Vector3d(2.5, 14.680589871350737,
                                     5.439803376216421);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, 34.0, -1.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0);  // current Ray direction
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_same_face_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(4, 3); // forcing to pick the larger positive root
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, 34.0, -1.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0);  // current Ray direction
        double expected = 13.5601966237836;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, 100*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_same_face_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(4, 3); // forcing to pick the larger positive root
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, 34.0, -1.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0);  // current Ray direction
        Vector3d expected = Vector3d(2.5, -6.680589871350804,
                                     12.5601966237836);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 100*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_same_face_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(4, 3); // forcing to pick the larger positive root
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, 34.0, -1.0); // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0);  // current Ray direction
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_negative_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, -26.0, 19.0);  // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0);    // current Ray direction
        double expected = -6.439803376216421;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_negative_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, -26.0, 19.0);  // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0);    // current Ray direction
        Vector3d expected = Vector3d(2.5, -6.680589871350737,
                                     12.560196623783579);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_negative_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <sphere.inc>
        Vector3d p = Vector3d(2.5, -26.0, 19.0);  // current Ray location
        Vector3d u = Vector3d(0.0, -3.0, 1.0);    // current Ray direction
        bool expected = false;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        Vector3d p = Vector3d(-21.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);   // current Ray direction
        double expected = 6.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        Vector3d p = Vector3d(-21.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);   // current Ray direction
        Vector3d expected = Vector3d(-3.0, 4.0, 0.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        Vector3d p = Vector3d(-21.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);   // current Ray direction
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_skip_root0_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);  // current Ray direction
        double expected = 2.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_skip_root0_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);  // current Ray direction
        Vector3d expected = Vector3d(3.0, 4.0, 0.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_skip_root0_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);  // current Ray direction
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_keep_root0_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(0.0, 3.0, 0.0);  // current Ray direction
        double expected = 0.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_keep_root0_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(0.0, 3.0, 0.0);  // current Ray direction
        Vector3d expected = Vector3d(-3.0, 4.0, 0.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_keep_root0_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(0.0, 3.0, 0.0);  // current Ray direction
        bool expected = false;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "velocity", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        SpherePtr s = std::make_shared<Sphere>();
        FacePtr f = s;
        Grid g;
        Vector3d r, v;
        Node n;
        g.add_node(n); // represents all previous Nodes in the Grid g
        r = Vector3d(1.0, 2.0, 3.0);    // Sphere center's location
        v = Vector3d(-3.0, -2.0, -1.0); // Sphere center's velocity

        n = Node(1, r, v);
        g.add_node(n);
        f->add_node(1);
        s->setr(-10.0);
        s->setv(-5.0);

        v = Vector3d(7.0, 2.0, -5.0); // test point
        Vector3d expected = Vector3d(-6.0, -2.0, 3.0);
        Vector3d actual = f->velocity(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        f->clear();
        size_t expected = 0;
        size_t actual = f->size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_Node", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        f->clear();
        std::string expected("out of range exception");
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            f->get_node(0);
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
    Test t(GROUP, "clear_num_nbr", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        f->clear();
        size_t expected = 0;
        size_t actual = f->num_nbr();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_Neighbor", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        f->clear();
        std::string expected("out of range exception");
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            f->get_neighbor(0);
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
    Test t(GROUP, "clear_get_my_zone", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        f->clear();
        size_t expected = 0;
        size_t actual = f->get_my_zone();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_my_id", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere0.inc>
        f->clear();
        short int expected = -2;
        short int actual = f->get_my_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_1st_Sphere", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        std::string fname = path + "mesh_" + tlabel + ".txt";
        std::ifstream infile(fname.c_str());
        utils::find_line(infile, "Sphere");
        Sphere f(infile);
        infile.close();
        infile.clear();
        std::string expected("Sphere\n          0          0\n");
        expected += "          0\n          neighbors          0\n";
        expected += "   1.300000e+01  -5.000000e+00";
        std::string actual = f.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Sphere.cpp
