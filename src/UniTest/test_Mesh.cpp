/*=============================================================================

test_Mesh.cpp
Definitions for unit, integration, and regression tests for class Mesh.

pmh_2014_1219
pmh_2015_0522
pmh_2019_1031

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 18 December 2014
Last modified 2 October 2020

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

#include <test_Mesh.h>
#include <Test.h>

#include <Cone.h>
#include <Face.h>
#include <Grid.h>
#include <Node.h>
#include <Polygon.h>
#include <Sphere.h>
#include <Surface.h>
#include <Vector3d.h>
#include <Zone.h>

#include <stdexcept>

void test_Mesh(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Mesh";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor_reserve_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Mesh m(5);
        size_t expected = 0;
        size_t actual = m.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        size_t expected = 4;
        size_t actual = m.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

/******************************** mesh.inc ***********************************/
// pmh_2014_1219

//-----------------------------------------------------------------------------
//  First Ray handover
//-----------------------------------------------------------------------------
{
    Test t(GROUP, "to_Surface_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(-5.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);   // Ray direction
        double expected = 2.5;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_Surface_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(-5.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);   // Ray direction
        Vector3d expected(0.0, 0.75, 0.5);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_Surface_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(-5.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);   // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_Surface_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(-5.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);   // Ray direction
        FaceID expected(2, -1);      // cube's left Face as part of Surface
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_Surface_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(-5.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);   // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(1, 2);       // cube's left Face
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Second Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_back_box_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(1); // cube Zone = 1
        FaceID this_face(1, 2);     // cube's left Face
        Vector3d w(0.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        double expected = 0.5;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_back_box_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(1); // cube Zone = 1
        FaceID this_face(1, 2);     // cube's left Face
        Vector3d w(0.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        Vector3d expected(1.0, 0.75, 0.5);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_back_box_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(1); // cube Zone = 1
        FaceID this_face(1, 2);     // cube's left Face
        Vector3d w(0.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        FaceID expected(1, 3);      // cube's right Face
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_to_back_box_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(1); // cube Zone = 1
        FaceID this_face(1, 2);     // cube's left Face
        Vector3d w(0.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(3, 2);       // back box's left Face
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);    }
}

//-----------------------------------------------------------------------------
//  Third Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "back_box_to_Surface_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(3); // back box Zone = 3
        FaceID this_face(3, 2);     // back box's left Face
        Vector3d w(1.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        double expected = 0.5;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "back_box_to_Surface_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(3); // back box Zone = 3
        FaceID this_face(3, 2);     // back box's left Face
        Vector3d w(1.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        Vector3d expected(2.0, 0.75, 0.5);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "back_box_to_Surface_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(3); // back box Zone = 3
        FaceID this_face(3, 2);     // back box's left Face
        Vector3d w(1.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        FaceID expected(3, 3);      // back box's right Face
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "back_box_to_Surface_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(3); // back box Zone = 3
        FaceID this_face(3, 2);     // back box's left Face
        Vector3d w(1.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(0, 1); // back box's right Face as part of Surface
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Fourth Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Surface_to_bounding_Sphere_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1);     // bounding Sphere's inner Face (Surface)
        Vector3d w(2.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        double expected = 5.484356174671468;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Surface_to_bounding_Sphere_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1);     // bounding Sphere's inner Face (Surface)
        Vector3d w(2.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        Vector3d expected(12.968712349342937, 0.75, 0.5);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Surface_to_bounding_Sphere_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1);     // bounding Sphere's inner Face (Surface)
        Vector3d w(2.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        FaceID expected(0, 0);      // bounding Sphere's outer Face (Sphere)
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Surface_to_bounding_Sphere_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1);     // bounding Sphere's inner Face (Surface)
        Vector3d w(2.0, 0.75, 0.5); // Ray starting point
        Vector3d u(2.0, 0.0, 0.0);  // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(0, -2); // no neighbor for bounding Sphere's outer Face
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

/***************************** mesh_cones.inc ********************************/
// pmh_2015_0522

//-----------------------------------------------------------------------------
//  First Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_Surface_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(25.0, 37.0, 90.0); // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        double expected = 10.0;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_Surface_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(25.0, 37.0, 90.0); // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        Vector3d expected(5.0, 7.0, 10.0);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 100*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_Surface_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(25.0, 37.0, 90.0); // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_Surface_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(25.0, 37.0, 90.0); // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        FaceID expected(3, -1);       // cone outer side as part of Surface
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_Surface_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(25.0, 37.0, 90.0); // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(2, 1);        // cone outer, slanted side
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Second Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_cylinder_side_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 1); // as if Ray started on outer, slanted side
        Vector3d w(5.0, 7.0, 10.0);   // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        double expected = 1.0;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_cylinder_side_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 1); // as if Ray started on outer, slanted side
        Vector3d w(5.0, 7.0, 10.0);   // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        Vector3d expected(3.0, 4.0, 2.0);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_cylinder_side_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 1); // as if Ray started on outer, slanted side
        Vector3d w(5.0, 7.0, 10.0);   // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_cylinder_side_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 1); // as if Ray started on outer, slanted side
        Vector3d w(5.0, 7.0, 10.0);   // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        FaceID expected(2, 2);        // cone inner, vertical side
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_cylinder_side_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 1); // as if Ray started on outer, slanted side
        Vector3d w(5.0, 7.0, 10.0);   // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(1, 1);        // cylinder side
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Third Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_cylinder_bottom_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer side
        Vector3d w(3.0, 4.0, 2.0);    // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        double expected = 0.125;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_cylinder_bottom_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer side
        Vector3d w(3.0, 4.0, 2.0);    // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        Vector3d expected(2.75, 3.625, 1.0);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_cylinder_bottom_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer side
        Vector3d w(3.0, 4.0, 2.0);    // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_cylinder_bottom_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer side
        Vector3d w(3.0, 4.0, 2.0);    // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        FaceID expected(1, 0);        // cylinder bottom
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_to_cylinder_bottom_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer side
        Vector3d w(3.0, 4.0, 2.0);    // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(0, 1);        // bounding Sphere's inner Face (Surface)
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Fourth Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_Surface_to_bounding_Sphere_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1);     // bounding Sphere's inner Face (Surface)
        Vector3d w(2.75, 3.625, 1.0); // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        double expected = 11.7046434584003;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_Surface_to_bounding_Sphere_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1);     // bounding Sphere's inner Face (Surface)
        Vector3d w(2.75, 3.625, 1.0); // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        Vector3d expected(-20.6592869168006,
                          -31.488930375200901, -92.637147667202399);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_Surface_to_bounding_Sphere_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1);     // bounding Sphere's inner Face (Surface)
        Vector3d w(2.75, 3.625, 1.0); // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        FaceID expected(0, 0);       // bounding Sphere's outer Face (Sphere)
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_Surface_to_bounding_Sphere_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1);     // bounding Sphere's inner Face (Surface)
        Vector3d w(2.75, 3.625, 1.0); // Ray starting point
        Vector3d u(-2.0, -3.0, -8.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(0, -2); // no neighbor for bounding Sphere's outer Face
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

/************************ mesh_cones_tiebreaks.inc ***************************/
// pmh_2019_1031

//-----------------------------------------------------------------------------
//  First Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_Surface_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(0.0, 100.0, 0.0); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        double expected = sqrt(pow(98.0,2) + pow(1.0e-6,2)) / cnst::CV;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_Surface_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(0.0, 100.0, 0.0); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        Vector3d expected(0.0, 2.0, -1.0e-6);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_Surface_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(0.0, 100.0, 0.0); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_Surface_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(0.0, 100.0, 0.0); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        FaceID expected(2, -1); // outer cylinder of outer Zone as part of Surface
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_Surface_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 0); // as if Ray started on the bounding Sphere
        Vector3d w(0.0, 100.0, 0.0); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(2, 1); // outer cylinder of outer Zone
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Second Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_cylinder_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 2.0, 0.0);   // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        double expected = sqrt(1.000000000001) / cnst::CV;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_cylinder_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 2.0, 0.0);   // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        Vector3d expected(0.0, 1.0, -1.0e-6);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_cylinder_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 2.0, 0.0);   // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_cylinder_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 2.0, 0.0);   // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        FaceID expected(2, 3); // outer Zone's inner cylinder
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_cylinder_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 2.0, 0.0);   // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(1, 1); // inner Zone's outer cylinder
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Third Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_top_Zone_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 1.0, -1.0e-6);    // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        double expected = 1.0 / cnst::CV;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_top_Zone_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 1.0, -1.0e-6);    // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        Vector3d expected(0.0, 1.0e-6, -9.99999e-7);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_top_Zone_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 1.0, -1.0e-6);    // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_top_Zone_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 1.0, -1.0e-6);    // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        FaceID expected(1, 2); // inner Zone's top (nearly) disk
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_top_Zone_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 1.0, -1.0e-6);    // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(3, 0); // top Zone's (nearly) disk
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Fourth Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_across_top_Zone_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(3); // top Zone
        FaceID this_face(3, 0); // bottom Face
        Vector3d w(0.0, 1.0e-6, -9.99999e-7); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        double expected = 2.0e-6 / cnst::CV;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_across_top_Zone_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(3); // top Zone
        FaceID this_face(3, 0); // bottom Face
        Vector3d w(0.0, 1.0e-6, -9.99999e-7); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        Vector3d expected(0.0, -1.0e-6, -9.99999e-7);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_across_top_Zone_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(3); // top Zone
        FaceID this_face(3, 0); // bottom Face
        Vector3d w(0.0, 1.0e-6, -9.99999e-7); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        FaceID expected(3, 0); // same (bottom) Face on other side
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_across_top_Zone_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(3); // top Zone
        FaceID this_face(3, 0); // bottom Face
        Vector3d w(0.0, 1.0e-6, -9.99999e-7); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(1, 2); // inner Zone's upper Face (on other side)
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Fifth Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_from_top_Zone_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 2); // as if Ray started on top (nearly) disk
        Vector3d w(0.0, -1.0e-6, -9.99999e-7); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        double expected = 1.0 / cnst::CV;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_from_top_Zone_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 2); // as if Ray started on top (nearly) disk
        Vector3d w(0.0, -1.0e-6, -9.99999e-7); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        Vector3d expected(0.0, -1.0, -1.0e-6);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_from_top_Zone_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 2); // as if Ray started on top (nearly) disk
        Vector3d w(0.0, -1.0e-6, -9.99999e-7); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_from_top_Zone_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 2); // as if Ray started on top (nearly) disk
        Vector3d w(0.0, -1.0e-6, -9.99999e-7); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        FaceID expected(1, 1); // inner Zone's outer cylinder (on other side)
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_from_top_Zone_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 2); // as if Ray started on top (nearly) disk
        Vector3d w(0.0, -1.0e-6, -9.99999e-7); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(2, 3); // outer Zone's inner cylinder (on other side)
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Sixth Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_other_cylinder_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 3); // as if Ray started on inner cylinder
        Vector3d w(0.0, -1.0, -1.0e-6); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        double expected = 1.0 / cnst::CV;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_other_cylinder_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 3); // as if Ray started on inner cylinder
        Vector3d w(0.0, -1.0, -1.0e-6); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        Vector3d expected(0.0, -2.0, -1.0e-6);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_other_cylinder_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 3); // as if Ray started on inner cylinder
        Vector3d w(0.0, -1.0, -1.0e-6); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_other_cylinder_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 3); // as if Ray started on inner cylinder
        Vector3d w(0.0, -1.0, -1.0e-6); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        FaceID expected(2, 1); // outer Zone's outer cylinder
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_to_other_cylinder_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(2); // cone Zone = 2
        FaceID this_face(2, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, -1.0, -1.0e-6); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(0, 1); // bounding Sphere's inner Surface
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Seventh Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_from_Surface_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1); // as if Ray started on the bounding Sphere's Surface
        Vector3d w(0.0, -2.0, 0.0); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        double expected = 98.0 / cnst::CV;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_from_Surface_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1); // as if Ray started on the bounding Sphere's Surface
        Vector3d w(0.0, -2.0, 0.0); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        Vector3d expected(0.0, -100.0, 0.0);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_from_Surface_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1); // as if Ray started on the bounding Sphere's Surface
        Vector3d w(0.0, -2.0, 0.0); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_from_Surface_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1); // as if Ray started on the bounding Sphere's Surface
        Vector3d w(0.0, -2.0, 0.0); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        FaceID expected(0, 0); // bounding Sphere
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_tiebreaks_from_Surface_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(0); // bounding Sphere Zone = 0
        FaceID this_face(0, 1); // as if Ray started on the bounding Sphere's Surface
        Vector3d w(0.0, -2.0, 0.0); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(0, -2); // bounding Sphere has no neighbors
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Cut across the inner Zone (should miss hitting Node 1)
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "across_inner_Zone_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 1.0, -2.0e-6);    // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        double expected = 2.0 / cnst::CV;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "across_inner_Zone_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 1.0, -2.0e-6);    // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        Vector3d expected(0.0, -1.0, -2.0e-6);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "across_inner_Zone_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 1.0, -2.0e-6);    // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "across_inner_Zone_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 1.0, -2.0e-6);    // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        FaceID expected(1, 1); // inner Zone's outer cylinder's other side
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "across_inner_Zone_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_tiebreaks.inc>
        z = m.get_zone(1); // cylinder Zone = 1
        FaceID this_face(1, 1); // as if Ray started on outer cylinder
        Vector3d w(0.0, 1.0, -2.0e-6);    // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(2, 3); // outer Zone's inner cylinder (on the other side)
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

/************************ mesh_cones_vertex.inc ***************************/

//-----------------------------------------------------------------------------
//  First Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_to_disk_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(0);
        FaceID this_face(0, 1); // as if Ray started on the outer cylinder
        Vector3d w(0.0, 0.00346442, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        double expected = 0.00346442 / cnst::CV;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_to_disk_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(0);
        FaceID this_face(0, 1); // as if Ray started on the outer cylinder
        Vector3d w(0.0, 0.00346442, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        Vector3d expected(0.0, 9.99988e-7, -0.1399999999);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 5.0e-8);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_to_disk_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(0);
        FaceID this_face(0, 1); // as if Ray started on the outer cylinder
        Vector3d w(0.0, 0.00346442, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_to_disk_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(0);
        FaceID this_face(0, 1); // as if Ray started on the outer cylinder
        Vector3d w(0.0, 0.00346442, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        FaceID expected(0, 2); // top disk of bottom Zone
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_to_disk_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(0);
        FaceID this_face(0, 1); // as if Ray started on the outer cylinder
        Vector3d w(0.0, 0.00346442, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(1, 0); // bottom disk of top Zone
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Second Ray handover (manually move the Ray near the Cone's vertex)
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_short_hop_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(1);
        FaceID this_face(1, 0); // as if Ray started on the bottom disk
        Vector3d w(9.9998e-7, 0.0, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        double expected = Vector3d::get_big() / 2.0;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e90);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_short_hop_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(1);
        FaceID this_face(1, 0); // as if Ray started on the bottom disk
        Vector3d w(9.9998e-7, 0.0, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        Vector3d expected(-9.9998e-7, 0.0, -0.1399999999);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_short_hop_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(1);
        FaceID this_face(1, 0); // as if Ray started on the bottom disk
        Vector3d w(9.9998e-7, 0.0, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_short_hop_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(1);
        FaceID this_face(1, 0); // as if Ray started on the bottom disk
        Vector3d w(9.9998e-7, 0.0, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        FaceID expected(1, 0); // bottom disk of top Zone again
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_short_hop_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(1);
        FaceID this_face(1, 0); // as if Ray started on the bottom disk
        Vector3d w(9.9998e-7, 0.0, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(0, 2); // top disk of bottom Zone
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  Third Ray handover
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_to_cylinder_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(0);
        FaceID this_face(0, 2); // as if Ray started on the top disk
        Vector3d w(-9.9998e-7, 0.0, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        double expected = 0.00346442 / cnst::CV;
        double actual = z->hit(g, w, u, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, 5.0e-20);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_to_cylinder_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(0);
        FaceID this_face(0, 2); // as if Ray started on the top disk
        Vector3d w(-9.9998e-7, 0.0, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        Vector3d expected(-9.9998e-7, -0.00346442, -0.1399999999);
        Vector3d actual = z->hit(g, w, u, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, 5.0e-9);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_to_cylinder_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(0);
        FaceID this_face(0, 2); // as if Ray started on the top disk
        Vector3d w(-9.9998e-7, 0.0, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        bool expected = true;
        bool actual = z->hit(g, w, u, this_face).is_found;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_to_cylinder_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(0);
        FaceID this_face(0, 2); // as if Ray started on the top disk
        Vector3d w(-9.9998e-7, 0.0, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        FaceID expected(0, 1); // cylinder of bottom Zone on the other side
        FaceID actual = z->hit(g, w, u, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cones_vertex_to_cylinder_next_face", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones_vertex.inc>
        z = m.get_zone(0);
        FaceID this_face(0, 2); // as if Ray started on the top disk
        Vector3d w(-9.9998e-7, 0.0, -0.1399999999); // Ray starting point
        Vector3d u(0.0, -cnst::CV, 0.0); // Ray direction
        RetIntercept h = z->hit(g, w, u, this_face);
        FaceID expected(0, -2); // uninitialized in this unit test
        FaceID actual = m.next_face(g, h);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
//  end raytracing tests
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        m.clear();
        size_t expected = 0;
        size_t actual = m.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_Zone", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        m.clear();
        std::string expected("out of range exception");
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            m.get_zone(0);
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
    Test t(GROUP, "to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh.inc>
        std::string expected("Number_of_zones          4");
        expected += cnststr::ZONE_SEPARATOR;
        expected += "Zone          0\n";
        expected += "          2\n";
        expected += "Sphere\n";
        expected += "          0          0\n";
        expected += "          0\n";
        expected += "          neighbors          0\n";
        expected += "   1.300000e+01   0.000000e+00\n";
        expected += "Surface\n";
        expected += "         13\n";
        expected += "          0          1\n";
        expected += "          neighbors         13\n";
        expected += "          1          0\n";
        expected += "          1          1\n";
        expected += "          1          2\n";
        expected += "          1          4\n";
        expected += "          1          5\n";
        expected += "          2          0\n";
        expected += "          3          1\n";
        expected += "          2          5\n";
        expected += "          2          3\n";
        expected += "          2          4\n";
        expected += "          3          5\n";
        expected += "          3          3\n";
        expected += "          3          4\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          0         -1\n";
        expected += "          0          1          5          4\n";
        expected += "          neighbors          1\n";
        expected += "          1          0\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1         -1\n";
        expected += "          2          6          7          3\n";
        expected += "          neighbors          1\n";
        expected += "          1          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          2         -1\n";
        expected += "          0          2          3          1\n";
        expected += "          neighbors          1\n";
        expected += "          1          2\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          3         -1\n";
        expected += "          0          4          6          2\n";
        expected += "          neighbors          1\n";
        expected += "          1          4\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          4         -1\n";
        expected += "          1          3          7          5\n";
        expected += "          neighbors          1\n";
        expected += "          1          5\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          5         -1\n";
        expected += "          4          5         13         10\n";
        expected += "          neighbors          1\n";
        expected += "          2          0\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          6         -1\n";
        expected += "          6         12         15          7\n";
        expected += "          neighbors          1\n";
        expected += "          3          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          7         -1\n";
        expected += "          5          9         14         13\n";
        expected += "          neighbors          1\n";
        expected += "          2          5\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          8         -1\n";
        expected += "         10         13         14         11\n";
        expected += "          neighbors          1\n";
        expected += "          2          3\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          9         -1\n";
        expected += "          4         10         11          8\n";
        expected += "          neighbors          1\n";
        expected += "          2          4\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "         10         -1\n";
        expected += "          9          7         15         14\n";
        expected += "          neighbors          1\n";
        expected += "          3          5\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "         11         -1\n";
        expected += "         11         14         15         12\n";
        expected += "          neighbors          1\n";
        expected += "          3          3\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "         12         -1\n";
        expected += "          8         11         12          6\n";
        expected += "          neighbors          1\n";
        expected += "          3          4";
        expected += cnststr::ZONE_SEPARATOR;
        expected += "Zone          1\n";
        expected += "          6\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          0\n";
        expected += "          0          4          5          1\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          1\n";
        expected += "          2          3          7          6\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          2\n";
        expected += "          0          1          3          2\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          3\n";
        expected += "          4          6          7          5\n";
        expected += "          neighbors          2\n";
        expected += "          2          2\n";
        expected += "          3          2\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          4\n";
        expected += "          0          2          6          4\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          5\n";
        expected += "          1          5          7          3\n";
        expected += "          neighbors          1\n";
        expected += "          0          1";
        expected += cnststr::ZONE_SEPARATOR;
        expected += "Zone          2\n";
        expected += "          6\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          2          0\n";
        expected += "          4         10         13          5\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          2          1\n";
        expected += "          8          9         14         11\n";
        expected += "          neighbors          1\n";
        expected += "          3          0\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          2          2\n";
        expected += "          4          5          9          8\n";
        expected += "          neighbors          1\n";
        expected += "          1          3\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          2          3\n";
        expected += "         10         11         14         13\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          2          4\n";
        expected += "          4          8         11         10\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          2          5\n";
        expected += "          5         13         14          9\n";
        expected += "          neighbors          1\n";
        expected += "          0          1";
        expected += cnststr::ZONE_SEPARATOR;
        expected += "Zone          3\n";
        expected += "          6\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          3          0\n";
        expected += "          8         11         14          9\n";
        expected += "          neighbors          1\n";
        expected += "          2          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          3          1\n";
        expected += "          6          7         15         12\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          3          2\n";
        expected += "          8          9          7          6\n";
        expected += "          neighbors          1\n";
        expected += "          1          3\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          3          3\n";
        expected += "         11         12         15         14\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          3          4\n";
        expected += "          8          6         12         11\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          3          5\n";
        expected += "          9         14         15          7\n";
        expected += "          neighbors          1\n";
        expected += "          0          1";
        std::string actual = m.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_spheres_1d", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d p;
        Node n;
        Grid g;
        p = Vector3d(0.0, 0.0, 0.0);
        n = Node(0, p, p);
        g.add_node(n);
        FacePtr f;
        ZonePtr z;
        SpherePtr s;
        Mesh m(2);

        // Bounding Sphere Zone
        z = std::make_shared<Zone>(0);
        m.add_zone(z);
        f = s = std::make_shared<Sphere>(0, 0); // outer Face
        z->add_face(f);
        f->add_node(0); // location of Sphere's center
        s->setr(13.0);  // Sphere radius, orientation outward (r is positive)
        f = s = std::make_shared<Sphere>(0, 1); // inner Face
        z->add_face(f);
        f->add_node(0); // location of Sphere's center
        s->setr(-5.0);  // Sphere radius, orientation inward (r is negative)
        f->add_neighbor(1, 0);

        // generic Sphere Zone
        z = std::make_shared<Zone>(1);
        m.add_zone(z);
        f = s = std::make_shared<Sphere>(1, 0);
        z->add_face(f);
        f->add_node(0);
        s->setr(5.0);
        f->add_neighbor(0, 1);

        std::string expected("Number_of_zones          2");
        expected += cnststr::ZONE_SEPARATOR;
        expected += "Zone          0\n";
        expected += "          2\n";
        expected += "Sphere\n";
        expected += "          0          0\n";
        expected += "          0\n";
        expected += "          neighbors          0\n";
        expected += "   1.300000e+01   0.000000e+00\n";
        expected += "Sphere\n";
        expected += "          0          1\n";
        expected += "          0\n";
        expected += "          neighbors          1\n";
        expected += "          1          0\n";
        expected += "  -5.000000e+00   0.000000e+00";
        expected += cnststr::ZONE_SEPARATOR;
        expected += "Zone          1\n";
        expected += "          1\n";
        expected += "Sphere\n";
        expected += "          1          0\n";
        expected += "          0\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "   5.000000e+00   0.000000e+00";
        std::string actual = m.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_cones", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <mesh_cones.inc>
        std::string expected("Number_of_zones          3");
        expected += cnststr::ZONE_SEPARATOR;
        expected += "Zone          0\n";
        expected += "          2\n";
        expected += "Sphere\n";
        expected += "          0          0\n";
        expected += "          5\n";
        expected += "          neighbors          0\n";
        expected += "   1.000000e+02   0.000000e+00\n";
        expected += "Surface\n";
        expected += "          4\n";
        expected += "          0          1\n";
        expected += "          neighbors          4\n";
        expected += "          1          0\n";
        expected += "          1          2\n";
        expected += "          2          0\n";
        expected += "          2          1\n";
        expected += "Cone\n";
        expected += "          0         -1\n";
        expected += "          3          0\n";
        expected += "          neighbors          1\n";
        expected += "          1          0\n";
        expected += "Cone\n";
        expected += "          1         -1\n";
        expected += "          1          2\n";
        expected += "          neighbors          1\n";
        expected += "          1          2\n";
        expected += "Cone\n";
        expected += "          2         -1\n";
        expected += "          4          3\n";
        expected += "          neighbors          1\n";
        expected += "          2          0\n";
        expected += "Cone\n";
        expected += "          3         -1\n";
        expected += "          2          4\n";
        expected += "          neighbors          1\n";
        expected += "          2          1";
        expected += cnststr::ZONE_SEPARATOR;
        expected += "Zone          1\n";
        expected += "          3\n";
        expected += "Cone\n";
        expected += "          1          0\n";
        expected += "          0          3\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Cone\n";
        expected += "          1          1\n";
        expected += "          3          2\n";
        expected += "          neighbors          1\n";
        expected += "          2          2\n";
        expected += "Cone\n";
        expected += "          1          2\n";
        expected += "          2          1\n";
        expected += "          neighbors          1\n";
        expected += "          0          1";
        expected += cnststr::ZONE_SEPARATOR;
        expected += "Zone          2\n";
        expected += "          3\n";
        expected += "Cone\n";
        expected += "          2          0\n";
        expected += "          3          4\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Cone\n";
        expected += "          2          1\n";
        expected += "          4          2\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Cone\n";
        expected += "          2          2\n";
        expected += "          2          3\n";
        expected += "          neighbors          1\n";
        expected += "          1          1";
        std::string actual = m.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        Mesh m(path, tlabel);
        size_t expected = 2;
        size_t actual = m.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        Mesh m(path, tlabel);
        std::string fname = path + "mesh_" + tlabel + ".txt";
        std::string expected(utils::file_to_string(fname));
/*
        std::string expected("Number_of_zones          2");
        expected += cnststr::ZONE_SEPARATOR;
        expected += "Zone          0\n";
        expected += "          2\nSphere\n          0          0\n";
        expected += "          0\n          neighbors          0\n";
        expected += "   1.300000e+01  -5.000000e+00\nSurface\n          6\n";
        expected += "          0          1\n          neighbors          6\n";
        expected += "          1          0\n";
        expected += "          1          1\n";
        expected += "          1          2\n";
        expected += "          1          3\n";
        expected += "          1          4\n";
        expected += "          1          5\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          0         -1\n";
        expected += "          0          1          5          4\n";
        expected += "          neighbors          1\n";
        expected += "          1          0\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1         -1\n";
        expected += "          2          6          7          3\n";
        expected += "          neighbors          1\n";
        expected += "          1          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          2         -1\n";
        expected += "          0          2          3          1\n";
        expected += "          neighbors          1\n";
        expected += "          1          2\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          3         -1\n";
        expected += "          4          5          7          6\n";
        expected += "          neighbors          1\n";
        expected += "          1          3\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          4         -1\n";
        expected += "          0          4          6          2\n";
        expected += "          neighbors          1\n";
        expected += "          1          4\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          5         -1\n";
        expected += "          1          3          7          5\n";
        expected += "          neighbors          1\n";
        expected += "          1          5";
        expected += cnststr::ZONE_SEPARATOR;
        expected += "Zone          1\n          6\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          0\n";
        expected += "          0          4          5          1\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          1\n";
        expected += "          2          3          7          6\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          2\n";
        expected += "          0          1          3          2\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          3\n";
        expected += "          4          6          7          5\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          4\n";
        expected += "          0          2          6          4\n";
        expected += "          neighbors          1\n";
        expected += "          0          1\n";
        expected += "Polygon\n";
        expected += "          4\n";
        expected += "          1          5\n";
        expected += "          1          5          7          3\n";
        expected += "          neighbors          1\n";
        expected += "          0          1";
*/
        std::string actual = m.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_Zone1_te", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        Mesh m(path, tlabel);
        double expected = 6400.0;
        double actual = m.get_zone(1)->get_te();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_Zone1_tr", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        Mesh m(path, tlabel);
        double expected = 200.0;
        double actual = m.get_zone(1)->get_tr();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_Zone1_np", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        Mesh m(path, tlabel);
        double expected = 1.0e16;
        double actual = m.get_zone(1)->get_np();

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e5);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_Zone1_nmat", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        Mesh m(path, tlabel);
        unsigned short int expected = 3;
        unsigned short int actual = m.get_zone(1)->get_nmat();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_Zone1_fp0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        Mesh m(path, tlabel);
        double expected = 0.5;
        double actual = m.get_zone(1)->fp_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_Zone1_fp1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        Mesh m(path, tlabel);
        double expected = 0.1;
        double actual = m.get_zone(1)->fp_at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_Zone1_fp2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        Mesh m(path, tlabel);
        double expected = 0.4;
        double actual = m.get_zone(1)->fp_at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro4_Mesh0_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro4/");
        std::string tlabel("0");
        Mesh m(path, tlabel);
        std::string fname = path + "mesh_" + tlabel + ".txt";
        std::string expected(utils::file_to_string(fname));
        std::string actual = m.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Mesh.cpp
