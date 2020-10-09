/*=============================================================================

test_Zone.cpp
Definitions for unit, integration, and regression tests for class Zone.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 8 December 2014
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

#include <test_Zone.h>
#include <Test.h>

#include <Cone.h>
#include <Face.h>
#include <Grid.h>
#include <Node.h>
#include <Polygon.h>
#include <Sphere.h>
#include <Surface.h>
#include <Vector3d.h>

#include <stdexcept>

void test_Zone(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Zone";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_id", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Zone z;
        z.set_id(5);
        size_t expected = 5;
        size_t actual = z.get_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_id", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Zone z(5);
        size_t expected = 5;
        size_t actual = z.get_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Zone z(5);
        size_t expected = 0;
        size_t actual = z.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor0_id", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Zone z;
        size_t expected = 0;
        size_t actual = z.get_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor0_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Zone z;
        size_t expected = 0;
        size_t actual = z.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  The cube is treated as a collection of six square-shaped Polygons
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "outer_Sphere_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        size_t expected = 7;
        size_t actual = z.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        size_t expected = 6;
        size_t actual = z.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_zone_point", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        Vector3d w{-1.0, -2.0, -3.0};
        Vector3d expected{0.5, 0.5, 0.5};
        Vector3d actual = z.zone_point(g, w);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sphere_zone_point", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere_zone_point.inc>
        Vector3d w{0.0, 0.0, 9.0};
        Vector3d expected{0.0, 0.0, 4.0};
        Vector3d actual = z.zone_point(g, w);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cone_on_axis_zone_point", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cone_on_axis.inc>
        Vector3d w{0.1, 0.0, -0.2};
        Vector3d expected{2.0/3.0, 0.0, 0.5};
        Vector3d actual = z.zone_point(g, w);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cone_off_axis_zone_point", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cone_off_axis.inc>
        Vector3d w{1.1, 0.0, 1.2};
        Vector3d expected{1.5, 0.0, 0.5};
        Vector3d actual = z.zone_point(g, w);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_zone_point_hit_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        Vector3d r{-1.0, -2.0, -3.0};
        Vector3d v{-1.0, 0.0, 0.0};
        FaceID fid{4, 0}; // as if r belongs to this Face
        RetIntercept intrcpt = z.hit(g, r, v, fid);;

        Vector3d expected{0.0, 0.5, 0.5}; // point hit starting from zone_point
        Vector3d actual = intrcpt.w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_zone_point_hit_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        Vector3d r{-1.0, -2.0, -3.0};
        Vector3d v{-1.0, 0.0, 0.0};
        FaceID fid{9, 0}; // as if r belongs to this Face
        RetIntercept intrcpt = z.hit(g, r, v, fid);;

        FaceID expected{9, 2}; // Face hit starting from zone_point
        FaceID actual = intrcpt.fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sphere_zone_point_hit_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere_zone_point.inc>
        Vector3d r{0.0, 0.0, 9.0};
        Vector3d v{-1.0, 0.0, 0.0};
        FaceID fid{4, 0}; // as if r belongs to this Face
        RetIntercept intrcpt = z.hit(g, r, v, fid);;

        Vector3d expected{-3.0, 0.0, 4.0}; // point hit starting from zone_point
        Vector3d actual = intrcpt.w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sphere_zone_point_hit_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <sphere_zone_point.inc>
        Vector3d r{0.0, 0.0, 9.0};
        Vector3d v{-1.0, 0.0, 0.0};
        FaceID fid{4, 0}; // as if r belongs to this Face
        RetIntercept intrcpt = z.hit(g, r, v, fid);;

        FaceID expected{4, 1}; // Face hit starting from zone_point
        FaceID actual = intrcpt.fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cone_on_axis_zone_point_hit_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cone_on_axis.inc>
        Vector3d r{1.0, 0.0, -3.0};
        Vector3d v{-1.0, 0.0, 0.0};
        FaceID fid{4, 0}; // as if r belongs to this Face
        RetIntercept intrcpt = z.hit(g, r, v, fid);;

        Vector3d expected{-1.0, 0.0, 0.5}; // point hit starting from zone_point
        Vector3d actual = intrcpt.w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cone_on_axis_zone_point_hit_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cone_on_axis.inc>
        Vector3d r{1.0, 0.0, -3.0};
        Vector3d v{-1.0, 0.0, 0.0};
        FaceID fid{4, 0}; // as if r belongs to this Face
        RetIntercept intrcpt = z.hit(g, r, v, fid);;

        FaceID expected{4, 1}; // Face hit starting from zone_point
        FaceID actual = intrcpt.fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cone_off_axis_zone_point_hit_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cone_off_axis.inc>
        Vector3d r{1.0, 0.0, -3.0};
        Vector3d v{-1.0, 0.0, 0.0};
        FaceID fid{4, 0}; // as if r belongs to this Face
        RetIntercept intrcpt = z.hit(g, r, v, fid);;

        Vector3d expected{1.0, 0.0, 0.5}; // point hit starting from zone_point
        Vector3d actual = intrcpt.w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cone_off_axis_zone_point_hit_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cone_off_axis.inc>
        Vector3d r{1.0, 0.0, -3.0};
        Vector3d v{-1.0, 0.0, 0.0};
        FaceID fid{4, 0}; // as if r belongs to this Face
        RetIntercept intrcpt = z.hit(g, r, v, fid);;

        FaceID expected{4, 3}; // Face hit starting from zone_point
        FaceID actual = intrcpt.fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "outer_Sphere_get_face_my_zone", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        size_t expected = 8;
        size_t actual = z.get_face(3)->get_my_zone();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "outer_Sphere_get_face_my_id", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        short int expected = 3;
        short int actual = z.get_face(3)->get_my_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "outer_Sphere_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        std::string expected = "Zone          0\n          7\nSphere\n";
        expected += "          8          0\n          8\n";
        expected += "          neighbors          0\n";
        expected += "   1.300000e+01  -5.000000e+00\n";
        expected += "Polygon\n          4\n          8          1\n";
        expected += "          0          1          5          4\n";
        expected += "          neighbors          1\n";
        expected += "          9          0\n";
        expected += "Polygon\n          4\n          8          2\n";
        expected += "          2          6          7          3\n";
        expected += "          neighbors          1\n";
        expected += "          9          1\n";
        expected += "Polygon\n          4\n          8          3\n";
        expected += "          0          2          3          1\n";
        expected += "          neighbors          1\n";
        expected += "          9          2\n";
        expected += "Polygon\n          4\n          8          4\n";
        expected += "          4          5          7          6\n";
        expected += "          neighbors          1\n";
        expected += "          9          3\n";
        expected += "Polygon\n          4\n          8          5\n";
        expected += "          0          4          6          2\n";
        expected += "          neighbors          1\n";
        expected += "          9          4\n";
        expected += "Polygon\n          4\n          8          6\n";
        expected += "          1          3          7          5\n";
        expected += "          neighbors          1\n";
        expected += "          9          5";
        std::string actual = z.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        std::string expected = "Zone          0\n          6\n";
        expected += "Polygon\n          4\n          9          0\n";
        expected += "          0          4          5          1\n";
        expected += "          neighbors          1\n";
        expected += "          8          1\n";
        expected += "Polygon\n          4\n          9          1\n";
        expected += "          2          3          7          6\n";
        expected += "          neighbors          1\n";
        expected += "          8          2\n";
        expected += "Polygon\n          4\n          9          2\n";
        expected += "          0          1          3          2\n";
        expected += "          neighbors          1\n";
        expected += "          8          3\n";
        expected += "Polygon\n          4\n          9          3\n";
        expected += "          4          6          7          5\n";
        expected += "          neighbors          1\n";
        expected += "          8          4\n";
        expected += "Polygon\n          4\n          9          4\n";
        expected += "          0          2          6          4\n";
        expected += "          neighbors          1\n";
        expected += "          8          5\n";
        expected += "Polygon\n          4\n          9          5\n";
        expected += "          1          5          7          3\n";
        expected += "          neighbors          1\n";
        expected += "          8          6";
        std::string actual = z.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cone_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <conic_zones.inc>
        std::string expected = "Zone          2\n          3\n";
        expected += "Cone\n          2          0\n";
        expected += "          3          4\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Cone\n          2          1\n";
        expected += "          4          2\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Cone\n          2          2\n";
        expected += "          2          3\n";
        expected += "          neighbors          1\n";
        expected += "          1          1";
        std::string actual = z->to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "outer_Sphere_to_cube_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 0);
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        FaceID expected(8, 3);
        FaceID actual = z.hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "outer_Sphere_to_cube_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 0);
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        double expected = 1.0;
        double actual = z.hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "outer_Sphere_to_cube_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 0);
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        Vector3d expected(0.0, 0.5, 0.5); // exit point
        Vector3d actual = z.hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "outer_Sphere_to_cube_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 0);
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        bool expected = true;
        bool actual = z.hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "through_cube_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 2);
        Vector3d w(0.0, 0.5, 0.5);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        FaceID expected(9, 5);
        FaceID actual = z.hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "through_cube_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 2);
        Vector3d w(0.0, 0.5, 0.5);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        double expected = 0.5 / 15.5;  // 0.03225806451612903
        double actual = z.hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "through_cube_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 2);
        Vector3d w(0.0, 0.5, 0.5);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        double tint = 0.5 / 15.5;      // 0.03225806451612903
        double xint = 0.0  +   4.0 * tint;
        double yint = 0.5  +   6.5 * tint;
        double zint = 0.5  +  15.5 * tint;
        Vector3d expected(xint, yint, zint); // exit point
        Vector3d actual = z.hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "through_cube_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 2);
        Vector3d w(0.0, 0.5, 0.5);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        bool expected = true;
        bool actual = z.hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_outer_Sphere_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 6);
        double tint = 0.5 / 15.5;      // 0.03225806451612903
        double xint = 0.0  +   4.0 * tint;
        double yint = 0.5  +   6.5 * tint;
        double zint = 0.5  +  15.5 * tint;
        Vector3d w(xint, yint, zint);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);       // Ray direction
        FaceID expected(8, 0);
        FaceID actual = z.hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_outer_Sphere_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 6);
        double tint = 0.5 / 15.5;      // 0.03225806451612903
        double xint = 0.0  +   4.0 * tint;
        double yint = 0.5  +   6.5 * tint;
        double zint = 0.5  +  15.5 * tint;
        Vector3d w(xint, yint, zint);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);       // Ray direction
        double expected = 0.4685794564218944;
        double actual = z.hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_outer_Sphere_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 6);
        double tint = 0.5 / 15.5;      // 0.03225806451612903
        double xint = 0.0  +   4.0 * tint;
        double yint = 0.5  +   6.5 * tint;
        double zint = 0.5  +  15.5 * tint;
        Vector3d w(xint, yint, zint);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);       // Ray direction

        tint = 0.4685794564218944;
        xint +=  4.0 * tint;
        yint +=  6.5 * tint;
        zint += 15.5 * tint;
        Vector3d expected(xint, yint, zint); // exit point
        Vector3d actual = z.hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_outer_Sphere_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 6);
        double tint = 0.5 / 15.5;      // 0.03225806451612903
        double xint = 0.0  +   4.0 * tint;
        double yint = 0.5  +   6.5 * tint;
        double zint = 0.5  +  15.5 * tint;
        Vector3d w(xint, yint, zint);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);       // Ray direction
        bool expected = true;
        bool actual = z.hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must slide along cube's left Face and hit the edge of top Face
    Test t(GROUP, "grazing_cube_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 2);
        Vector3d w(0.0, 0.5, 0.5);    // Ray starting point (left Face)
        Vector3d u(0.0, 0.0, 1.0);    // Ray direction (straight up left Face)
        FaceID expected(9, 5);
        FaceID actual = z.hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must slide along cube's left Face and hit the edge of top Face
    Test t(GROUP, "grazing_cube_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 2);
        Vector3d w(0.0, 0.5, 0.5);    // Ray starting point (left Face)
        Vector3d u(0.0, 0.0, 1.0);    // Ray direction (straight up left Face)
        double expected = 0.5;
        double actual = z.hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must slide along cube's left Face and hit the edge of top Face
    Test t(GROUP, "grazing_cube_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 2);
        Vector3d w(0.0, 0.5, 0.5);    // Ray starting point (left Face)
        Vector3d u(0.0, 0.0, 1.0);    // Ray direction (straight up left Face)
        Vector3d expected(0.0, 0.5, 1.0); // exit point
        Vector3d actual = z.hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must slide along cube's left Face and hit the edge of top Face
    Test t(GROUP, "grazing_cube_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 2);
        Vector3d w(0.0, 0.5, 0.5);    // Ray starting point (left Face)
        Vector3d u(0.0, 0.0, 1.0);    // Ray direction (straight up left Face)
        bool expected = true;
        bool actual = z.hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must slide along cone's slanted side and hit the edge of bottom Face
    Test t(GROUP, "grazing_cone_side_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <conic_zones.inc>
        FaceID this_face(2, 1);
        Vector3d w(sqrt(74.0), 0.0, 10.0); // Ray starting point (outer side)
        Vector3d u(9.0-sqrt(74.0), 0.0, -9.0); // Ray direction (along side)
        FaceID expected(2, 0);
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must slide along cone's slanted side and hit the edge of bottom Face
    Test t(GROUP, "grazing_cone_side_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <conic_zones.inc>
        FaceID this_face(2, 1);
        Vector3d w(sqrt(74.0), 0.0, 10.0); // Ray starting point (outer side)
        Vector3d u(9.0-sqrt(74.0), 0.0, -9.0); // Ray direction (along side)
        double expected = 1.0;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must slide along cone's slanted side and hit the edge of bottom Face
    Test t(GROUP, "grazing_cone_side_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <conic_zones.inc>
        FaceID this_face(2, 1);
        Vector3d w(sqrt(74.0), 0.0, 10.0); // Ray starting point (outer side)
        Vector3d u(9.0-sqrt(74.0), 0.0, -9.0); // Ray direction (along side)
        Vector3d expected(8.999999, 0.0, 1.0); // exit point
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must slide along cone's slanted side and hit the edge of bottom Face
    Test t(GROUP, "grazing_cone_side_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <conic_zones.inc>
        FaceID this_face(2, 1);
        Vector3d w(sqrt(74.0), 0.0, 10.0); // Ray starting point (outer side)
        Vector3d u(9.0-sqrt(74.0), 0.0, -9.0); // Ray direction (along side)
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must not get stuck at one of the cube's Faces
    Test t(GROUP, "up_to_outer_Sphere_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 6);
        Vector3d w(0.0, 0.0, 1.0); // Ray starting point (upper left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up)
        FaceID expected(8, 0);
        FaceID actual = z.hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must not get stuck at one of the cube's Faces
    Test t(GROUP, "up_to_outer_Sphere_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 6);
        Vector3d w(0.0, 0.0, 1.0); // Ray starting point (upper left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up)
        double expected = 8.806248474865697;
        double actual = z.hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must not get stuck at one of the cube's Faces
    Test t(GROUP, "up_to_outer_Sphere_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 6);
        Vector3d w(0.0, 0.0, 1.0); // Ray starting point (upper left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up)

        double tint = 8.806248474865697;
        double zint = 1.0 + tint;
        Vector3d expected(0.0, 0.0, zint); // exit point
        Vector3d actual = z.hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must not get stuck at one of the cube's Faces
    Test t(GROUP, "up_to_outer_Sphere_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <outer_Sphere.inc>
        z.set_id(8);
        FaceID this_face(8, 6);
        Vector3d w(0.0, 0.0, 1.0); // Ray starting point (upper left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up)
        bool expected = true;
        bool actual = z.hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must not get stuck at one of the cone's Faces
    Test t(GROUP, "cone_to_cylinder_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <conic_zones.inc>
        FaceID this_face(2, 0);
        Vector3d w(9.0, 0.0, 1.0);  // Ray starting point (Node #4)
        Vector3d u(-1.0, 0.0, 0.0); // Ray direction
        FaceID expected(2, 2);
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must not get stuck at one of the cone's Faces
    Test t(GROUP, "cone_to_cylinder_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <conic_zones.inc>
        FaceID this_face(2, 0);
        Vector3d w(9.0, 0.0, 1.0);  // Ray starting point (Node #4)
        Vector3d u(-1.0, 0.0, 0.0); // Ray direction
        double expected = 4.0;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must not get stuck at one of the cone's Faces
    Test t(GROUP, "cone_to_cylinder_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <conic_zones.inc>
        FaceID this_face(2, 0);
        Vector3d w(9.0, 0.0, 1.0);  // Ray starting point (Node #4)
        Vector3d u(-1.0, 0.0, 0.0); // Ray direction
        Vector3d expected(5.0, 0.0, 1.000001); // exit point (Node #3)
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must not get stuck at one of the cone's Faces
    Test t(GROUP, "cone_to_cylinder_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <conic_zones.inc>
        FaceID this_face(2, 0);
        Vector3d w(9.0, 0.0, 1.0);  // Ray starting point (Node #4)
        Vector3d u(-1.0, 0.0, 0.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must follow cube's left front edge and hit the upper left front Node
    Test t(GROUP, "from_bottom_along_edge_cube_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 4);    // bottom Face labeled as initial
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up the edge)
        FaceID expected(9, 5);
        FaceID actual = z.hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must follow cube's left front edge and hit the upper left front Node
    Test t(GROUP, "from_bottom_along_edge_cube_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 4);    // bottom Face labeled as initial
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up the edge)
        double expected = 1.0;
        double actual = z.hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must follow cube's left front edge and hit the upper left front Node
    Test t(GROUP, "from_bottom_along_edge_cube_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 4);    // bottom Face labeled as initial
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up the edge)
        Vector3d expected(0.0, 0.0, 1.0); // exit point
        Vector3d actual = z.hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must follow cube's left front edge and hit the upper left front Node
    Test t(GROUP, "from_bottom_along_edge_cube_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 4);    // bottom Face labeled as initial
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up the edge)
        bool expected = true;
        bool actual = z.hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must follow cube's left front edge and hit the upper left front Node
    Test t(GROUP, "from_front_along_edge_cube_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 0);    // front Face labeled as initial
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up the edge)
        FaceID expected(9, 5);
        FaceID actual = z.hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must follow cube's left front edge and hit the upper left front Node
    Test t(GROUP, "from_front_along_edge_cube_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 0);    // front Face labeled as initial
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up the edge)
        double expected = 1.0;
        double actual = z.hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must follow cube's left front edge and hit the upper left front Node
    Test t(GROUP, "from_front_along_edge_cube_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 0);    // front Face labeled as initial
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up the edge)
        Vector3d expected(0.0, 0.0, 1.0); // exit point
        Vector3d actual = z.hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must follow cube's left front edge and hit the upper left front Node
    Test t(GROUP, "from_front_along_edge_cube_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube.inc>
        z.set_id(9);
        FaceID this_face(9, 0);    // front Face labeled as initial
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up the edge)
        bool expected = true;
        bool actual = z.hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  The cube is treated as a single Surface made of six square-shaped Polygons
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bounding_sphere_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        size_t expected = 2;
        size_t actual = z.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bounding_sphere_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        std::string expected = "Zone          0\n          2\n";
        expected += "Sphere\n          0          0\n          8\n";
        expected += "          neighbors          0\n";
        expected += "   1.300000e+01  -5.000000e+00\n";
        expected += "Surface\n          6\n          0          1\n";
        expected += "          neighbors          6\n";
        expected += "          1          0\n";
        expected += "          1          1\n";
        expected += "          1          2\n";
        expected += "          1          3\n";
        expected += "          1          4\n";
        expected += "          1          5\n";
        expected += "Polygon\n          4\n          0         -1\n";
        expected += "          0          1          5          4\n";
        expected += "          neighbors          1\n";
        expected += "          1          0\n";
        expected += "Polygon\n          4\n          1         -1\n";
        expected += "          2          6          7          3\n";
        expected += "          neighbors          1\n";
        expected += "          1          1\n";
        expected += "Polygon\n          4\n          2         -1\n";
        expected += "          0          2          3          1\n";
        expected += "          neighbors          1\n";
        expected += "          1          2\n";
        expected += "Polygon\n          4\n          3         -1\n";
        expected += "          4          5          7          6\n";
        expected += "          neighbors          1\n";
        expected += "          1          3\n";
        expected += "Polygon\n          4\n          4         -1\n";
        expected += "          0          4          6          2\n";
        expected += "          neighbors          1\n";
        expected += "          1          4\n";
        expected += "Polygon\n          4\n          5         -1\n";
        expected += "          1          3          7          5\n";
        expected += "          neighbors          1\n";
        expected += "          1          5";
        std::string actual = z.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bounding_Sphere_to_cube_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 0); // Ray starts on the Sphere
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        FaceID expected(2, -1);
        FaceID actual = z.hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bounding_Sphere_to_cube_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 0); // Ray starts on the Sphere
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        double expected = 1.0;
        double actual = z.hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bounding_Sphere_to_cube_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 0); // Ray starts on the Sphere
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        Vector3d expected(0.0, 0.5, 0.5); // exit point
        Vector3d actual = z.hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "bounding_Sphere_to_cube_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 0); // Ray starts on the Sphere
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        bool expected = true;
        bool actual = z.hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_bounding_Sphere_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 1); // Ray starts on the cubic Surface
        double tint = 0.5 / 15.5;      // 0.03225806451612903
        double xint = 0.0  +   4.0 * tint;
        double yint = 0.5  +   6.5 * tint;
        double zint = 0.5  +  15.5 * tint;
        Vector3d w(xint, yint, zint);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);       // Ray direction
        FaceID expected(0, 0);
        FaceID actual = z.hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_bounding_Sphere_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 1); // Ray starts on the cubic Surface
        double tint = 0.5 / 15.5;      // 0.03225806451612903
        double xint = 0.0  +   4.0 * tint;
        double yint = 0.5  +   6.5 * tint;
        double zint = 0.5  +  15.5 * tint;
        Vector3d w(xint, yint, zint);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);       // Ray direction
        double expected = 0.4685794564218944;
        double actual = z.hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_bounding_Sphere_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 1); // Ray starts on the cubic Surface
        double tint = 0.5 / 15.5;      // 0.03225806451612903
        double xint = 0.0  +   4.0 * tint;
        double yint = 0.5  +   6.5 * tint;
        double zint = 0.5  +  15.5 * tint;
        Vector3d w(xint, yint, zint);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);       // Ray direction

        tint = 0.4685794564218944;
        xint +=  4.0 * tint;
        yint +=  6.5 * tint;
        zint += 15.5 * tint;
        Vector3d expected(xint, yint, zint); // exit point
        Vector3d actual = z.hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_bounding_Sphere_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 1); // Ray starts on the cubic Surface
        double tint = 0.5 / 15.5;      // 0.03225806451612903
        double xint = 0.0  +   4.0 * tint;
        double yint = 0.5  +   6.5 * tint;
        double zint = 0.5  +  15.5 * tint;
        Vector3d w(xint, yint, zint);     // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);       // Ray direction
        bool expected = true;
        bool actual = z.hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must advance along one of the cube's Faces
    Test t(GROUP, "up_to_bounding_Sphere_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 1); // Ray starts on the cubic Surface
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up)
        FaceID expected(5, -1);
        FaceID actual = z.hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must advance along one of the cube's Faces
    Test t(GROUP, "up_to_bounding_Sphere_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 1); // Ray starts on the cubic Surface
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up)
        double expected = 1.0;
        double actual = z.hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must advance along one of the cube's Faces
    Test t(GROUP, "up_to_bounding_Sphere_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 1); // Ray starts on the cubic Surface
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up)
        Vector3d expected(0.0, 0.0, 1.0); // exit point
        Vector3d actual = z.hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{   // Ray must advance along one of the cube's Faces
    Test t(GROUP, "up_to_bounding_Sphere_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        FaceID this_face(0, 1); // Ray starts on the cubic Surface
        Vector3d w(0.0, 0.0, 0.0); // Ray starting point (lower left front Node)
        Vector3d u(0.0, 0.0, 1.0); // Ray direction (straight up)
        bool expected = true;
        bool actual = z.hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        z.clear();
        size_t expected = 0;
        size_t actual = z.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_Face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        #include <bounding_Sphere.inc>
        z.add_face(f); // add the bounding Sphere to this Zone
        z.add_face(q); // add the cube-shaped Surface to this Zone
        z.clear();
        std::string expected("out of range exception");
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            z.get_face(0);
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
    Test t(GROUP, "load_Hydro1_Mesh0_Zone0_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        std::string fname(path + "mesh_" + tlabel + ".txt");
        std::ifstream geometry(fname.c_str());
        utils::find_word(geometry, "Zone");
        fname = path + "time_" + tlabel + ".txt";
        std::ifstream material(fname.c_str());
        utils::find_word(material, "Zone");
        Zone z(geometry, material);
        geometry.close();
        geometry.clear();
        material.close();
        material.clear();
        std::string expected("Zone          0\n          2\nSphere\n");
        expected += "          0          0\n          0\n";
        expected += "          neighbors          0\n";
        expected += "   1.300000e+01  -5.000000e+00\nSurface\n          6\n";
        expected += "          0          1\n          neighbors          6\n";
        expected += "          1          0\n";
        expected += "          1          1\n";
        expected += "          1          2\n";
        expected += "          1          3\n";
        expected += "          1          4\n";
        expected += "          1          5\n";
        expected += "Polygon\n          4\n          0         -1\n";
        expected += "          0          1          5          4\n";
        expected += "          neighbors          1\n          1          0\n";
        expected += "Polygon\n          4\n          1         -1\n";
        expected += "          2          6          7          3\n";
        expected += "          neighbors          1\n          1          1\n";
        expected += "Polygon\n          4\n          2         -1\n";
        expected += "          0          2          3          1\n";
        expected += "          neighbors          1\n          1          2\n";
        expected += "Polygon\n          4\n          3         -1\n";
        expected += "          4          5          7          6\n";
        expected += "          neighbors          1\n          1          3\n";
        expected += "Polygon\n          4\n          4         -1\n";
        expected += "          0          4          6          2\n";
        expected += "          neighbors          1\n          1          4\n";
        expected += "Polygon\n          4\n          5         -1\n";
        expected += "          1          3          7          5\n";
        expected += "          neighbors          1\n          1          5";
        std::string actual = z.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone0_to_string_full", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        std::string fname = path + "time_" + tlabel + ".txt";
        std::ifstream material(fname.c_str());
        utils::find_word(material, "Zone");
        Zone z(0); // z.my_id will have been set on load from the "mesh" file
        z.load_mat(material);
        material.close();
        material.clear();
        std::string expected("Zone          0\n");
        expected += "ne   0.000000e+00 electrons/cm3\n";
        expected += "te   0.000000e+00 eV\n";
        expected += "tr   0.000000e+00 eV\n";
        expected += "np   0.000000e+00 particles/cm3\n";
        expected += "nmat          0\n";
        expected += "material fraction";
        std::string actual = z.mat_to_string_full();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone0_to_string_plot", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        std::string fname = path + "time_" + tlabel + ".txt";
        std::ifstream material(fname.c_str());
        utils::find_word(material, "Zone");
        Zone z(0); // z.my_id will have been set on load from the "mesh" file
        z.load_mat(material);
        material.close();
        material.clear();
        std::string expected("");
        expected += "   0.000000e+00"; // ne
        expected += "   0.000000e+00"; // te
        expected += "   0.000000e+00"; // tr
        expected += "   0.000000e+00"; // np
        std::string actual = z.mat_to_string_plot();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_to_string_full", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        std::string expected("Zone          1\n");
        expected += "ne   0.000000e+00 electrons/cm3\n";
        expected += "te   6.400000e+03 eV\n";
        expected += "tr   2.000000e+02 eV\n";
        expected += "np   1.000000e+16 particles/cm3\n";
        expected += "nmat          3\n";
        expected += "material fraction\n";
        expected += "h   5.000000e-01\n";
        expected += "d   1.000000e-01\n";
        expected += "ar   4.000000e-01";
        std::string actual = z.mat_to_string_full();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_to_string_plot", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        std::string expected("");
        expected += "   0.000000e+00"; // ne
        expected += "   6.400000e+03"; // te
        expected += "   2.000000e+02"; // tr
        expected += "   1.000000e+16"; // np
        expected += "   5.000000e-01"; // h
        expected += "   1.000000e-01"; // d
        expected += "   4.000000e-01"; // ar
        std::string actual = z.mat_to_string_plot();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_set_ne", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        double expected = 2000.0;
        z.set_ne(expected);
        double actual = z.get_ne();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_te", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        double expected = 6400.0;
        double actual = z.get_te();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_set_te", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        double expected = 7000.0;
        z.set_te(expected);
        double actual = z.get_te();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_tr", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        double expected = 200.0;
        double actual = z.get_tr();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_set_tr", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        double expected = 300.0;
        z.set_tr(expected);
        double actual = z.get_tr();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_np", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        double expected = 1.0e16;
        double actual = z.get_np();

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_set_np", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        double expected = 3.0e16;
        z.set_np(expected);
        double actual = z.get_np();

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_nmat", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        unsigned short int expected = 3;
        unsigned short int actual = z.get_nmat();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_set_nmat", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        unsigned short int expected = 3;
        z.set_nmat(expected);
        unsigned short int actual = z.get_nmat();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_mat", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        std::string expected("ar");
        std::string actual = z.mat_at(2);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_set_mat", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        std::vector<std::string> mt;
        mt.push_back("ne");
        mt.push_back("al");
        mt.push_back("co");
        mt.push_back("k");
        z.set_mat(mt);
        std::string expected("k");
        std::string actual = z.mat_at(3);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_fp", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        double expected = 0.4;
        double actual = z.fp_at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_set_fp", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        std::vector<double> f;
        f.push_back(0.3);
        f.push_back(0.2);
        f.push_back(0.1);
        f.push_back(0.4);
        z.set_fp(f);
        double expected = 0.1;
        double actual = z.fp_at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_clear_string_full", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        z.clear();
        std::string expected("Zone          0\n");
        expected += "ne   0.000000e+00 electrons/cm3\n";
        expected += "te  -1.000000e+00 eV\n";
        expected += "tr  -1.000000e+00 eV\n";
        expected += "np  -1.000000e+00 particles/cm3\n";
        expected += "nmat          0\n";
        expected += "material fraction";
        std::string actual = z.mat_to_string_full();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_clear_string_plot", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        z.clear();
        std::string expected("");
        expected += "   0.000000e+00"; // ne
        expected += "  -1.000000e+00"; // te
        expected += "  -1.000000e+00"; // tr
        expected += "  -1.000000e+00"; // np
        std::string actual = z.mat_to_string_plot();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_clear_mat", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        z.clear();
        std::string expected("out of range exception");
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            z.mat_at(0);
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
    Test t(GROUP, "load_Hydro1_Time0_Zone1_clear_fp", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <hydro1_time0_Zone1.inc>
        z.clear();
        std::string expected("out of range exception");
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            z.fp_at(0);
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
    Test t(GROUP, "load_Hydro1_Time0_Zone1_ite", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        size_t expected = 0;
        size_t actual = ite;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_itr", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        size_t expected = 0;
        size_t actual = itr;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_ine", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        size_t expected = 5;
        size_t actual = ine;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_em0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        double expected = 4.06e30;
        double actual = em.at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e15);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_em1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        double expected = 8.12e30;
        double actual = em.at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e15);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_em2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        double expected = 2.03e31;
        double actual = em.at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e15);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_ab0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        double expected = 6.04e-5;
        double actual = ab.at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e12);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_ab1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        double expected = 6.04e-1;
        double actual = ab.at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e10);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_ab2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        double expected = 6.04e0;
        double actual = ab.at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e8);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_sc0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        double expected = 6.04e-6;
        double actual = sc.at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, 0.01);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_sc1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        double expected = 6.04e-2;
        double actual = sc.at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, 0.1);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Time0_Zone1_sc2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mix.inc>
        double expected = 6.04e-1;
        double actual = sc.at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, 0.01);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Zone.cpp
