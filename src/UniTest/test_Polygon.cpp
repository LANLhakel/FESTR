/*=============================================================================

test_Polygon.cpp
Definitions for unit, integration, and regression tests for class Polygon.

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

#include <test_Polygon.h>
#include <Test.h>

#include <constants.h>
#include <Grid.h>
#include <utils.h>

#include <stdexcept>
#include <fstream>

void test_Polygon(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Polygon";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_my_zone", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Polygon>();
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
        FacePtr f = std::make_shared<Polygon>();
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
        FacePtr f = std::make_shared<Polygon>(mz, mi);
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
        FacePtr f = std::make_shared<Polygon>(mz, mi);
        short int expected = mi;
        short int actual = f->get_my_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Polygon>();
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
        FacePtr f = std::make_shared<Polygon>();
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
        FacePtr f = std::make_shared<Polygon>();
        Vector3d v(1.0, 2.0, 3.0);
        Node n0(3, v);
        f->add_node(n0.geti());
        f->add_node(n0.geti());
        f->add_node(n0.geti());
        bool expected = false;
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
        FacePtr f = std::make_shared<Polygon>();
        Vector3d v(1.0, 2.0, 3.0);
        Node n0(3, v);
        f->add_node(n0.geti());
        f->add_node(n0.geti());
        f->add_node(n0.geti());
        bool expected = true;
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
        FacePtr f = std::make_shared<Polygon>();
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
        FacePtr f = std::make_shared<Polygon>();
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
        FacePtr f = std::make_shared<Polygon>(3, 1);
        FacePtr g = std::make_shared<Polygon>(4, 5);
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
    Test t(GROUP, "to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Polygon>(3, 1);
        f->add_node(98765);
        f->add_node(98766);
        f->add_node(98767);
        f->add_node(98768);
        f->add_node(98769);
        std::string expected = "Polygon\n          5\n";
        expected += "          3          1\n";
        expected += "      98765      98766      98767      98768      98769";
        expected += "\n          neighbors          0";
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
        FacePtr expected = std::make_shared<Polygon>(0, -2);
        FacePtr actual = std::make_shared<Polygon>();

        failed_test_count += t.check_equal_real_obj(*expected, *actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "assignment", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr expected = std::make_shared<Polygon>(4, 5);
        expected->add_node(2);
        expected->add_node(9);
        expected->add_node(4);
        FacePtr actual = std::make_shared<Polygon>();
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
        FacePtr f = std::make_shared<Polygon>(3, 1);
        f->add_neighbor(2, 4);
        f->add_neighbor(9, 5);
        size_t expected = 9;
        size_t actual = f->get_neighbor(1).my_zone;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "add_get_neighboring_Polygon", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Polygon>(3, 1);
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
        FacePtr f = std::make_shared<Polygon>(3, 1);
        f->add_neighbor(2, 4);
        f->add_neighbor(9, 5);
        size_t expected = 2;
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
        FacePtr f = std::make_shared<Polygon>(3, 1);
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
    Test t(GROUP, "area2_normal_triangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <triangle.inc>
        Vector3d expected(4.0, 3.0, 12.0);
        Vector3d actual = f->area2_normal_center(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "area2_normal_rectangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        Vector3d expected(0.0, 0.0, 12.0);
        Vector3d actual = f->area2_normal_center(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "area2_normal_trapezoid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <trapezoid.inc>
        Vector3d expected(0.0, 0.0, 8.0);
        Vector3d actual = f->area2_normal_center(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "area2_normal_hexagon", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hexagon.inc>
        Vector3d expected = Vector3d(0.0, 0.0, -6.0*r*s);
        Vector3d actual = f->area2_normal_center(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "center_triangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <triangle.inc>
        Vector3d expected(1.0, 4.0/3.0, 1.0/3.0);
        Vector3d actual;
        f->area2_normal_center(g, actual);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "center_rectangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        Vector3d expected(2.0, 2.5, 5.0);
        Vector3d actual;
        f->area2_normal_center(g, actual);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "center_trapezoid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <trapezoid.inc>
        Vector3d expected(13.0/12.0, 5.0/6.0, 0.0);
        Vector3d actual;
        f->area2_normal_center(g, actual);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "center_hexagon", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hexagon.inc>
        Vector3d expected = center;
        Vector3d actual;
        f->area2_normal_center(g, actual);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normal_triangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <triangle.inc>
        Vector3d expected(4.0/13.0, 3.0/13.0, 12.0/13.0);
        Vector3d actual = f->normal(g);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normal_rectangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        Vector3d expected(0.0, 0.0, 1.0);
        Vector3d actual = f->normal(g);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "area_triangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <triangle.inc>
        double expected = 6.5;
        double actual = f->area(g);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);

    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "area_rectangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        double expected = 6.0;
        double actual = f->area(g);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "signed_distance_triangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <triangle.inc>
        Vector3d c;
        v = Vector3d(1.0, 4.0/3.0, 1.0/3.0) + f->area2_normal_center(g, c)/5;
        double expected = 2.6;
        double actual = f->distance(g, v);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "signed_distance_rectangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        v = Vector3d(7.0, 6.0, -4.0);
        double expected = -9.0;
        double actual = f->distance(g, v);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "subpoint_triangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <triangle.inc>
        Vector3d expected = Vector3d(1.0, 4.0/3.0, 1.0/3.0);
        Vector3d c;
        v = expected + f->area2_normal_center(g, c)/5;
        Vector3d actual = f->subpoint(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "subpoint_rectangle", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        v = Vector3d(7.0, 6.0, -4.0);
        Vector3d expected = Vector3d(7.0, 6.0, 5.0);
        Vector3d actual = f->subpoint(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "face_point_triangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <triangle.inc>
        Vector3d expected = Vector3d(1.0, 4.0/3.0, 1.0/3.0);
        Vector3d c;
        v = expected + f->area2_normal_center(g, c)/5;
        Vector3d actual = f->face_point(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "face_point_rectangle", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        v = Vector3d(7.0, 6.0, -4.0);
        Vector3d expected = Vector3d(2.0, 2.5, 5.0);
        Vector3d actual = f->face_point(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_has_point_above", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <triangle.inc>
        Vector3d c;
        v = Vector3d(1.0, 4.0/3.0, 1.0/3.0) + f->area2_normal_center(g, c)/5;
        bool expected = true;
        bool actual = f->has_above(g, v);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rectangle_has_point_above", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        v = Vector3d(7.0, 6.0, -4.0);
        bool expected = false;
        bool actual = f->has_above(g, v);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_has_point_below", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <triangle.inc>
        Vector3d c;
        v = Vector3d(1.0, 4.0/3.0, 1.0/3.0) + f->area2_normal_center(g, c)/5;
        bool expected = false;
        bool actual = f->has_below(g, v);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rectangle_has_point_below", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        v = Vector3d(7.0, 6.0, -4.0);
        bool expected = true;
        bool actual = f->has_below(g, v);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_contains_point", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <triangle.inc>
        v = Vector3d(1.0, 4.0/3.0, 1.0/3.0);
        bool expected = true;
        bool actual = f->contains(g, v);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rectangle_contains_point", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        v = Vector3d(2.0, 3.0, 5.0);
        bool expected = true;
        bool actual = f->contains(g, v);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rectangle_misses_point", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        v = Vector3d(7.0, 6.0, 5.0);
        bool expected = false;
        bool actual = f->contains(g, v);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rectangle_first_edge_contains_point", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        v = Vector3d(2.0, 1.0, 5.0);
        bool expected = true;
        bool actual = f->contains(g, v);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rectangle_first_edge_misses_point", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        v = Vector3d(4.0, 1.0, 5.0);
        bool expected = false;
        bool actual = f->contains(g, v);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rectangle_another_edge_contains_point", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        v = Vector3d(2.0, 4.0, 5.0);
        bool expected = true;
        bool actual = f->contains(g, v);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rectangle_another_edge_misses_point", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <rectangle.inc>
        v = Vector3d(4.0, 4.0, 5.0);
        bool expected = false;
        bool actual = f->contains(g, v);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_distance", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(0.0, 0.0, 0.0);
        v = Vector3d(1.0, 4.0/3.0, 1.0/3.0);
        Vector3d w;
        double expected = 1.0;
        double actual = f->intercept(g, r, v, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_point", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(0.0, 0.0, 0.0);
        v = Vector3d(1.0, 4.0/3.0, 1.0/3.0);
        Vector3d expected = v;
        Vector3d actual = f->intercept(g, r, v, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(0.0, 0.0, 0.0);
        v = Vector3d(1.0, 4.0/3.0, 1.0/3.0);
        FaceID expected = FaceID(2, 1);
        FaceID actual = f->intercept(g, r, v, EQT, fid).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(0.0, 0.0, 0.0);
        v = Vector3d(1.0, 4.0/3.0, 1.0/3.0);
        bool expected = true;
        bool actual = f->intercept(g, r, v, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_found_same_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(2, 1); // difference from triangle_intercept_found
        #include <triangle.inc>
        Vector3d r(0.0, 0.0, 0.0);
        v = Vector3d(1.0, 4.0/3.0, 1.0/3.0);
        bool expected = false; // difference from triangle_intercept_found
        bool actual = f->intercept(g, r, v, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_distance_negative", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(0.0, 0.0, 0.0);
        v = Vector3d(-1.0, -4.0/3.0, -1.0/3.0);
        Vector3d w;
        double expected = -1.0;
        double actual = f->intercept(g, r, v, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_point_negative", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(0.0, 0.0, 0.0);
        v = Vector3d(-1.0, -4.0/3.0, -1.0/3.0);
        Vector3d expected = -v;
        Vector3d actual = f->intercept(g, r, v, EQT, fid).w;
        
        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_found_negative", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(0.0, 0.0, 0.0);
        v = Vector3d(-1.0, -4.0/3.0, -1.0/3.0);
        bool expected = false;
        bool actual = f->intercept(g, r, v, EQT, fid).is_found;
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_distance_0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(1.0, 4.0/3.0, 1.0/3.0);
        v = Vector3d(-1.0, -4.0/3.0, -1.0/3.0);
        Vector3d w;
        double expected = 0.0;
        double actual = f->intercept(g, r, v, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_point_0", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(1.0, 4.0/3.0, 1.0/3.0);
        v = Vector3d(-1.0, -4.0/3.0, -1.0/3.0);
        Vector3d expected = -v;
        Vector3d actual = f->intercept(g, r, v, EQT, fid).w;
        
        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_found_0", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(1.0, 4.0/3.0, 1.0/3.0);
        v = Vector3d(-1.0, -4.0/3.0, -1.0/3.0);
        bool expected = false;
        bool actual = f->intercept(g, r, v, EQT, fid).is_found;
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_distance_parallel", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(0.0, 0.0, 0.0);
        v = Vector3d(-3.0, 0.0, 1.0); // parallel to the plane
        Vector3d w;
        double expected = -Vector3d::get_big();
        double actual = f->intercept(g, r, v, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_point_parallel", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(0.0, 0.0, 0.0);
        v = Vector3d(-3.0, 0.0, 1.0); // parallel to the plane
        double big = -Vector3d::get_big();
        Vector3d expected(big, big, big);
        Vector3d actual = f->intercept(g, r, v, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "triangle_intercept_found_parallel", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <triangle.inc>
        Vector3d r(0.0, 0.0, 0.0);
        v = Vector3d(-3.0, 0.0, 1.0); // parallel to the plane
        bool expected = false;
        bool actual = f->intercept(g, r, v, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rectangle_contains_intercept", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <rectangle.inc>
        Vector3d r(2.0, 2.0, 0.0);
        v = Vector3d(0.0, 0.0, 1.0);
        bool expected = true;
        bool actual = f->intercept(g, r, v, EQT, fid).is_found;
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rectangle_does_not_contain_intercept", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include <rectangle.inc>
        Vector3d r(-2.0, -2.0, 0.0);
        v = Vector3d(0.0, 0.0, 1.0);
        bool expected = false;
        bool actual = f->intercept(g, r, v, EQT, fid).is_found;
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "velocity_triangle", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <velocity_triangle.inc>
        Vector3d c(1.0, 4.0/3.0, 1.0/3.0);
        Vector3d expected(4.3677256019137740,
                          1.4401036616521570,
                          0.8384202999809531);
        Vector3d actual = f->velocity(g, c);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "velocity_triangle_at_x", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <velocity_triangle.inc>
        Vector3d c(3.0, 0.0, 0.0);
        Vector3d expected(4.0, -3.0, 2.0);
        Vector3d actual = f->velocity(g, c);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <velocity_triangle.inc>
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
        #include <velocity_triangle.inc>
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
        #include <velocity_triangle.inc>
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
        #include <velocity_triangle.inc>
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
        #include <velocity_triangle.inc>
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
        #include <velocity_triangle.inc>
        f->clear();
        short int expected = -2;
        short int actual = f->get_my_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_1st_Polygon", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        std::string fname = path + "mesh_" + tlabel + ".txt";
        std::ifstream infile(fname.c_str());
        utils::find_line(infile, "Polygon");
        Polygon f(infile);
        infile.close();
        infile.clear();
        std::string expected("Polygon\n          4\n          0         -1\n");
        expected += "          0          1          5          4\n";
        expected += "          neighbors          1\n          1          0";
        std::string actual = f.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Polygon.cpp
