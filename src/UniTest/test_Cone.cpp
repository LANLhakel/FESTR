/*=============================================================================

test_Cone.cpp
Definitions for unit, integration, and regression tests for class Cone.

pmh_2015_0521

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 14 May 2015
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
#include "../src/Cone.h"
#include "../src/constants.h"
#include "../src/utilities.h"

#include <stdexcept>
#include <fstream>

void test_Cone(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "Cone";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_my_zone", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Face *f = new Cone;
        size_t expected = 7;
        f->set_my_zone(expected);
        size_t actual = f->get_my_zone();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_my_id", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Face *f = new Cone;
        short int expected = 7;
        f->set_my_id(expected);
        short int actual = f->get_my_id();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_check_my_zone", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        size_t mz = 6;
        short int mi = 9;
        Face *f = new Cone(mz, mi);
        size_t expected = mz;
        size_t actual = f->get_my_zone();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_check_my_id", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        size_t mz = 6;
        short int mi = 9;
        Face *f = new Cone(mz, mi);
        short int expected = mi;
        short int actual = f->get_my_id();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Face *f = new Cone;
        size_t expected = 0;
        size_t actual = f->size();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(1.0, 2.0, 3.0);
        Node n0(3, v);
        Node n1(5, v, v);
        Face *f = new Cone;
        f->add_node(n0.geti());
        f->add_node(n1.geti());
        size_t expected = 2;
        size_t actual = f->size();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_curved", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        bool expected = true;
        bool actual = f->is_curved(g);

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_flat", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        bool expected = false;
        bool actual = f->is_flat(g);

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_node_id", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(1.0, 2.0, 3.0);
        Node n0(3, v);
        Node n1(5, v, v);
        Face *f = new Cone;
        f->add_node(n0.geti());
        f->add_node(n1.geti());
        size_t expected = 5;
        size_t actual = f->get_node(1);

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_node_id_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d v(1.0, 2.0, 3.0);
        Node n0(3, v);
        Node n1(5, v, v);
        Face *f = new Cone;
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
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "abs_diff", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Face *f = new Cone(3, 1);
        Face *g = new Cone(4, 5);
        f->add_node(6);
        g->add_node(2);
        g->add_node(9);
        g->add_node(4);
        double expected = 37.0;
        double actual = f->abs_diff(*g);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
        delete g;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Face *f = new Cone(3, 1);
        f->add_node(98765);
        f->add_node(98766);
        std::string expected = "Cone\n          3          1\n";
        expected += "      98765      98766";
        expected += "\n          neighbors          0";
        std::string actual = f->to_string();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Face *expected = new Cone(0, -2);
        Face *actual = new Cone;

        failed_test_count += t.check_equal_real_obj(*expected, *actual, EQT);
        delete expected;
        delete actual;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "assignment", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Face *expected = new Cone(4, 5);
        expected->add_node(2);
        expected->add_node(9);
        Face *actual = new Cone;
        *actual = *expected;

        failed_test_count += t.check_equal_real_obj(*expected, *actual, EQT);
        delete expected;
        delete actual;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "add_get_neighboring_zone", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Face *f = new Cone(3, 1);
        f->add_neighbor(2, 4);
        f->add_neighbor(9, 5);
        size_t expected = 9;
        size_t actual = f->get_neighbor(1).my_zone;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "add_get_neighboring_Cone", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Face *f = new Cone(3, 1);
        f->add_neighbor(2, 4);
        f->add_neighbor(9, 5);
        short int expected = 5;
        short int actual = f->get_neighbor(1).my_id;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "neighbor_count", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Face *f = new Cone(3, 1);
        f->add_neighbor(2, 4);
        f->add_neighbor(9, 5);
        size_t expected = 2;
        size_t actual = f->num_nbr();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "add_get_neighbor_out_of_range", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Face *f = new Cone(3, 1);
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
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "area2_normal", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double area2 = cnst::TWO_PI * 35.0;
        Vector3d expected(0.8 * area2, -0.6 * area2, 0.0);
        Vector3d actual = f->area2_normal_center(g, c);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "center", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        Vector3d expected(3.5, 6.0, 0.0);
        Vector3d actual;
        f->area2_normal_center(g, actual);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normal", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        Vector3d expected(0.8, -0.6, 0.0);
        Vector3d actual = f->normal(g);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "area", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double expected = cnst::PI * 35.0;
        double actual = f->area(g);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "subpoint_positive", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(9.0, 5.0, 0.0);
        // Vector3d expected(b);

        // after rotation into 3-D by angle phi
        Vector3d w(9.0*cos(phi), 9.0*sin(phi), 5.0);
        Vector3d expected(b.getx()*cos(phi), b.getx()*sin(phi), b.gety());
        Vector3d actual = f->subpoint(g, w);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "subpoint_negative", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(1.0, 11.0, 0.0);
        // Vector3d expected(b);

        // after rotation into 3-D by angle phi
        Vector3d w(1.0*cos(phi), 1.0*sin(phi), 11.0);
        Vector3d expected(b.getx()*cos(phi), b.getx()*sin(phi), b.gety());
        Vector3d actual = f->subpoint(g, w);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "subpoint_zero", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(b);
        // Vector3d expected(b);

        // after rotation into 3-D by angle phi
        Vector3d expected(b.getx()*cos(phi), b.getx()*sin(phi), b.gety());
        Vector3d w(expected);
        Vector3d actual = f->subpoint(g, w);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "signed_distance_positive", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(9.0, 5.0, 0.0);
        // Vector3d expected(b);

        // after rotation into 3-D by angle phi
        Vector3d w(9.0*cos(phi), 9.0*sin(phi), 5.0);
        double expected = 5.0;
        double actual = f->distance(g, w);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "signed_distance_negative", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(1.0, 11.0, 0.0);
        // Vector3d expected(b);

        // after rotation into 3-D by angle phi
        Vector3d w(1.0*cos(phi), 1.0*sin(phi), 11.0);
        double expected = -5.0;
        double actual = f->distance(g, w);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "signed_distance_zero", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(b);
        // Vector3d expected(b);

        // after rotation into 3-D by angle phi
        Vector3d w(b.getx()*cos(phi), b.getx()*sin(phi), b.gety());
        double expected = 0.0;
        double actual = f->distance(g, w);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "positive_has_point_above", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(9.0, 5.0, 0.0);
        // Vector3d expected(b);

        // after rotation into 3-D by angle phi
        Vector3d w(9.0*cos(phi), 9.0*sin(phi), 5.0);
        bool expected = true;
        bool actual = f->has_above(g, w);

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "negative_has_point_above", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(1.0, 11.0, 0.0);
        // Vector3d expected(b);

        // after rotation into 3-D by angle phi
        Vector3d w(1.0*cos(phi), 1.0*sin(phi), 11.0);
        bool expected = false;
        bool actual = f->has_above(g, w);

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "positive_has_point_below", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(9.0, 5.0, 0.0);
        // Vector3d expected(b);

        // after rotation into 3-D by angle phi
        Vector3d w(9.0*cos(phi), 9.0*sin(phi), 5.0);
        bool expected = false;
        bool actual = f->has_below(g, w);

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "negative_has_point_below", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(1.0, 11.0, 0.0);
        // Vector3d expected(b);

        // after rotation into 3-D by angle phi
        Vector3d w(1.0*cos(phi), 1.0*sin(phi), 11.0);
        bool expected = true;
        bool actual = f->has_below(g, w);

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "contains_point", "fast");
    
    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(3.5, 6.0, 0.0);

        // after rotation into 3-D by angle phi
        Vector3d w(3.5*cos(phi), 3.5*sin(phi), 6.0);
        bool expected = true;
        bool actual = f->contains(g, w);
        
        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "misses_point", "fast");
    
    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(0.5, 2.0, 0.0);

        // after rotation into 3-D by angle phi
        Vector3d w(0.5*cos(phi), 0.5*sin(phi), 2.0);
        bool expected = false;
        bool actual = f->contains(g, w);
        
        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "edge_contains_point", "fast");
    
    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone.inc"
        double phi = 30.0 * (cnst::PI / 180.0); // 30 degrees in radians

        // in RZ plane
        // Vector3d w(2.0, 4.0, 0.0);

        // after rotation into 3-D by angle phi
        Vector3d w(2.0*cos(phi), 2.0*sin(phi), 4.0);
        bool expected = true;
        bool actual = f->contains(g, w);
        
        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_none_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone.inc"
        Vector3d p = Vector3d(0.0, 6.0, 9.0); // current Ray location
        Vector3d u = Vector3d(1.0, 0.0, 0.0); // current Ray direction
        double expected = -1.0e100;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_none_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone.inc"
        Vector3d p = Vector3d(0.0, 6.0, 9.0); // current Ray location
        Vector3d u = Vector3d(1.0, 0.0, 0.0); // current Ray direction
        Vector3d expected = Vector3d(-1.0e100, -1.0e100, -1.0e100);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_none_face", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone.inc"
        Vector3d p = Vector3d(0.0, 6.0, 9.0); // current Ray location
        Vector3d u = Vector3d(1.0, 0.0, 0.0); // current Ray direction
        FaceID expected(4, 3);
        FaceID actual = f->intercept(g, p, u, EQT, fid).fid;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_none_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone.inc"
        Vector3d p = Vector3d(0.0, 6.0, 9.0); // current Ray location
        Vector3d u = Vector3d(1.0, 0.0, 0.0); // current Ray direction
        bool expected = false;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone.inc"
        Vector3d p = Vector3d(3.5, 8.0, 6.0); // current Ray location
        Vector3d u = Vector3d(0.0, 8.0, 0.0); // current Ray direction
        double expected = -1.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone.inc"
        Vector3d p = Vector3d(3.5, 8.0, 6.0); // current Ray location
        Vector3d u = Vector3d(0.0, 8.0, 0.0); // current Ray direction
        Vector3d expected = Vector3d(3.5, 0.0, 6.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone.inc"
        Vector3d p = Vector3d(3.5, 8.0, 6.0); // current Ray location
        Vector3d u = Vector3d(0.0, 8.0, 0.0); // current Ray direction
        bool expected = false;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_positive_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone_intercepts.inc"
        Vector3d p = (h1 + h2) / 2.0; // current Ray location
        double expected = 0.5;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_positive_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone_intercepts.inc"
        Vector3d p = (h1 + h2) / 2.0; // current Ray location
        Vector3d expected(h2);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 100*EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_one_positive_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone_intercepts.inc"
        Vector3d p = (h1 + h2) / 2.0; // current Ray location
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone_intercepts.inc"
        Vector3d p = h1 - u; // current Ray location
        double expected = 1.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone_intercepts.inc"
        Vector3d p = h1 - u; // current Ray location
        Vector3d expected = Vector3d(h1);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 10*EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone_intercepts.inc"
        Vector3d p = h1 - u; // current Ray location
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_1st_root_outside_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_1st_root_outside.inc"
        double expected = 2.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_1st_root_outside_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_1st_root_outside.inc"
        Vector3d expected = Vector3d(h2);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 10*EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_1st_root_outside_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_1st_root_outside.inc"
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_same_face_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(4, 3); // forcing to pick the larger positive root
        #include "cone_intercepts.inc"
        Vector3d p = h1 - u; // current Ray location
        double expected = 2.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_same_face_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(4, 3); // forcing to pick the larger positive root
        #include "cone_intercepts.inc"
        Vector3d p = h1 - u; // current Ray location
        Vector3d expected = Vector3d(h2);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 100*EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_positive_same_face_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(4, 3); // forcing to pick the larger positive root
        #include "cone_intercepts.inc"
        Vector3d p = h1 - u; // current Ray location
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_negative_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone_intercepts.inc"
        Vector3d p = h2 + u; // current Ray location
        double expected = -1.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_negative_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone_intercepts.inc"
        Vector3d p = h2 + u; // current Ray location
        Vector3d expected = Vector3d(h2);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 10*EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_two_negative_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        FaceID fid(9, 8);
        #include "cone_intercepts.inc"
        Vector3d p = h2 + u; // current Ray location
        bool expected = false;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        Vector3d p = Vector3d(-21.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);   // current Ray direction
        double expected = 6.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        Vector3d p = Vector3d(-21.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);   // current Ray direction
        Vector3d expected = Vector3d(-3.0, 4.0, 0.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        Vector3d p = Vector3d(-21.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);   // current Ray direction
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_skip_root0_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);  // current Ray direction
        double expected = 2.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_skip_root0_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);  // current Ray direction
        Vector3d expected = Vector3d(3.0, 4.0, 0.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_skip_root0_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(3.0, 0.0, 0.0);  // current Ray direction
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_keep_root0_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(0.0, 3.0, 0.0);  // current Ray direction
        double expected = 0.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_keep_root0_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(0.0, 3.0, 0.0);  // current Ray direction
        Vector3d expected = Vector3d(-3.0, 4.0, 0.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_pythagorean_keep_root0_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        Vector3d p = Vector3d(-3.0, 4.0, 0.0); // current Ray location
        Vector3d u = Vector3d(0.0, 3.0, 0.0);  // current Ray direction
        bool expected = false;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk.inc"
        Vector3d p = Vector3d(1.0, 2.0, 6.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        double expected = 2.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk.inc"
        Vector3d p = Vector3d(1.0, 2.0, 6.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        Vector3d expected = Vector3d(3.0, 4.0, 8.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk.inc"
        Vector3d p = Vector3d(1.0, 2.0, 6.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk_t_miss", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk.inc"
        Vector3d p = Vector3d(3.0, 2.0, 6.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        double expected = 2.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk_w_miss", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk.inc"
        Vector3d p = Vector3d(3.0, 2.0, 6.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        Vector3d expected = Vector3d(5.0, 4.0, 8.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk_is_found_miss", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk.inc"
        Vector3d p = Vector3d(3.0, 2.0, 6.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        bool expected = false;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk0_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk0.inc"
        Vector3d p = Vector3d(1.0, 2.0, 6.0); // current Ray location
        Vector3d u = -p; // current Ray direction
        double expected = 1.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk0_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk0.inc"
        Vector3d p = Vector3d(1.0, 2.0, 6.0); // current Ray location
        Vector3d u = -p; // current Ray direction
        Vector3d expected = Vector3d(0.0, 0.0, 0.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk0_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk0.inc"
        Vector3d p = Vector3d(1.0, 2.0, 6.0); // current Ray location
        Vector3d u = -p; // current Ray direction
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk0_Ray_on_axis_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk0.inc"
        Vector3d p = Vector3d(0.0, 0.0, 2.0);       // current Ray location
        Vector3d u = Vector3d(0.0, 0.0, -cnst::CV); // current Ray direction
        double expected = 2.0 / cnst::CV;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk0_Ray_on_axis_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk0.inc"
        Vector3d p = Vector3d(0.0, 0.0, 2.0);       // current Ray location
        Vector3d u = Vector3d(0.0, 0.0, -cnst::CV); // current Ray direction
        Vector3d expected = Vector3d(0.0, 0.0, 0.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_disk0_Ray_on_axis_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_disk0.inc"
        Vector3d p = Vector3d(0.0, 0.0, 2.0);       // current Ray location
        Vector3d u = Vector3d(0.0, 0.0, -cnst::CV); // current Ray direction
        bool expected = true; // avoid rejecting this solution due to numerics
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_cylinder_t", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_cylinder.inc"
        Vector3d p = Vector3d(2.0, 3.0, 5.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        double expected = 1.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_cylinder_w", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_cylinder.inc"
        Vector3d p = Vector3d(2.0, 3.0, 5.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        Vector3d expected = Vector3d(3.0, 4.0, 6.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_cylinder_is_found", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_cylinder.inc"
        Vector3d p = Vector3d(2.0, 3.0, 5.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        bool expected = true;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_cylinder_t_miss", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_cylinder.inc"
        Vector3d p = Vector3d(2.0, 3.0, 7.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        double expected = 1.0;
        double actual = f->intercept(g, p, u, EQT, fid).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_cylinder_w_miss", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_cylinder.inc"
        Vector3d p = Vector3d(2.0, 3.0, 7.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        Vector3d expected = Vector3d(3.0, 4.0, 8.0);
        Vector3d actual = f->intercept(g, p, u, EQT, fid).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "intercept_cylinder_is_found_miss", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_cylinder.inc"
        Vector3d p = Vector3d(2.0, 3.0, 7.0); // current Ray location
        Vector3d u = Vector3d(1.0, 1.0, 1.0); // current Ray direction
        bool expected = false;
        bool actual = f->intercept(g, p, u, EQT, fid).is_found;

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "velocity", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone_intercepts.inc"
        Vector3d v(h1); // test point
        Vector3d expected = Vector3d(4.5*sqrt(3.0), 4.5, 16.0);
        Vector3d actual = f->velocity(g, v);

        failed_test_count += t.check_equal_real_obj(expected, actual, 10*EQT);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        f->clear();
        size_t expected = 0;
        size_t actual = f->size();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_Node", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
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
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_num_nbr", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        f->clear();
        size_t expected = 0;
        size_t actual = f->num_nbr();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_Neighbor", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
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
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_my_zone", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        f->clear();
        size_t expected = 0;
        size_t actual = f->get_my_zone();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_my_id", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "cone0.inc"
        f->clear();
        short int expected = -2;
        short int actual = f->get_my_id();

        failed_test_count += t.check_equal(expected, actual);
        delete f;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro4_Mesh0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Hydro4/");
        std::string tlabel("0");
        std::string fname = path + "mesh_" + tlabel + ".txt";
        std::ifstream infile(fname.c_str());
        utils::find_line(infile, "Cone");
        Cone f(infile);
        infile.close();
        infile.clear();
        std::string expected("Cone\n          0         -1\n");
        expected += "          3          0\n";
        expected += "          neighbors          1\n";
        expected += "          1          0";
        std::string actual = f.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

// end test_Cone.cpp
