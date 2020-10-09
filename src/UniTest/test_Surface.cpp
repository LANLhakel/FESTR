/*=============================================================================

test_Surface.cpp
Definitions for unit, integration, and regression tests for class Surface.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 17 December 2014
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

#include <test_Surface.h>
#include <Test.h>

#include <constants.h>
#include <Polygon.h>
#include <Sphere.h>
#include <utils.h>

#include <fstream>
#include <stdexcept>

void test_Surface(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Surface";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{   // Tests common to Faces
    Test t(GROUP, "set_get_my_zone", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Surface>();
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
        FacePtr f = std::make_shared<Surface>();
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
        FacePtr f = std::make_shared<Surface>(mz, mi);
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
        FacePtr f = std::make_shared<Surface>(mz, mi);
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
        FacePtr f = std::make_shared<Surface>();
        size_t expected = 0;
        size_t actual = f->size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size0_three_argument_ctor", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Surface>(3, 6, 9);
        size_t expected = 0;
        size_t actual = f->size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size0_single_argument_ctor", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Surface>(9);
        size_t expected = 0;
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
        #include <cube_Surface.inc>
        bool expected = true;
        bool actual = a->is_curved(g);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "is_flat", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        bool expected = false;
        bool actual = a->is_flat(g);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ctor0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr expected = std::make_shared<Surface>(0, -2);
        FacePtr actual = std::make_shared<Surface>();

        failed_test_count += t.check_equal_real_obj(*expected, *actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "assignment", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr expected = std::make_shared<Surface>(4, 5);
        FacePtr actual = std::make_shared<Surface>();
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
        FacePtr f = std::make_shared<Surface>(3, 1);
        f->add_neighbor(2, 4);
        f->add_neighbor(9, 5);
        size_t expected = 9;
        size_t actual = f->get_neighbor(1).my_zone;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "add_get_neighboring_Surface", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        FacePtr f = std::make_shared<Surface>(3, 1);
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
        FacePtr f = std::make_shared<Surface>(3, 1);
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
        FacePtr f = std::make_shared<Surface>(3, 1);
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
    Test t(GROUP, "area2_normal", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        Vector3d expected(0.0, 0.0, 0.0);
        Vector3d actual = a->area2_normal_center(g, expected);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "center", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        Vector3d expected(1.0, 4.0/3.0, 1.0/3.0);
        Vector3d actual(expected);
        a->area2_normal_center(g, actual);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "normal", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        Vector3d expected;
        Vector3d actual = a->normal(g);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "area", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        double expected = 6.0;
        double actual = a->area(g);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "signed_distance", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        Vector3d v(1.0, 4.0/3.0, 1.0/3.0);
        double expected = 0.0;
        double actual = a->distance(g, v);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "subpoint", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        Vector3d expected;
        Vector3d actual = a->subpoint(g, expected);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "face_point", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        Vector3d expected;
        Vector3d actual = a->subpoint(g, expected);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "has_point_above", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        Vector3d v;
        bool expected = false;
        bool actual = a->has_above(g, v);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "has_point_below", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        Vector3d v;
        bool expected = false;
        bool actual = a->has_below(g, v);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "contains_point", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        Vector3d v(1.0, 4.0/3.0, 1.0/3.0);
        bool expected = true;
        bool actual = a->contains(g, v);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{   // Tests of Surface that are similar to Tests of Zone
    Test t(GROUP, "size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        size_t expected = 6;
        size_t actual = a->size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cube_surface_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        std::string expected = "Surface\n          6\n";
        expected += "          0          1\n          neighbors          6\n";
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
        std::string actual = a->to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "outer_sphere_to_cube_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        a->set_my_zone(8);
        a->set_my_id(2);
        FaceID this_face(8, 1);
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        double expected = 1.0;
        double actual = a->intercept(g, w, u, EQT, this_face).t;

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "outer_sphere_to_cube_w", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        a->set_my_zone(8);
        a->set_my_id(2);
        FaceID this_face(8, 1);
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        Vector3d expected(0.0, 0.5, 0.5); // exit point
        Vector3d actual = a->intercept(g, w, u, EQT, this_face).w;

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------
    
{
    Test t(GROUP, "outer_sphere_to_cube_fid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        a->set_my_zone(8);
        a->set_my_id(2);
        FaceID this_face(8, 1);
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        FaceID expected(2, -1);        // exit component Face of this Surface
        FaceID actual = a->intercept(g, w, u, EQT, this_face).fid;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "outer_sphere_to_cube_is_found", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        a->set_my_zone(8);
        a->set_my_id(1);
        FaceID this_face(8, 2);
        Vector3d w(-4.0, -6.0, -15.0); // Ray starting point
        Vector3d u(4.0, 6.5, 15.5);    // Ray direction
        bool expected = true;
        bool actual = a->intercept(g, w, u, EQT, this_face).is_found;

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
        a->set_my_zone(8);
        a->set_my_id(1);
        a->clear();
        size_t expected = 0;
        size_t actual = a->size();

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
        a->set_my_zone(8);
        a->set_my_id(1);
        a->clear();
        std::string expected("out of range exception");
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            a->get_face(0);
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
        #include <cube_Surface.inc>
        a->set_my_zone(8);
        a->set_my_id(1);
        a->clear();
        size_t expected = 0;
        size_t actual = a->num_nbr();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_Neighbor", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        a->set_my_zone(8);
        a->set_my_id(1);
        a->clear();
        std::string expected("out of range exception");
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            a->get_neighbor(0);
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
        #include <cube_Surface.inc>
        a->set_my_zone(8);
        a->set_my_id(1);
        a->clear();
        size_t expected = 0;
        size_t actual = a->get_my_zone();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "clear_get_my_id", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <cube_Surface.inc>
        a->set_my_zone(8);
        a->set_my_id(1);
        a->clear();
        short int expected = -2;
        short int actual = a->get_my_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_Hydro1_Mesh0_1st_Surface", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnststr::PATH + "UniTest/Hydro1/");
        std::string tlabel("0");
        std::string fname = path + "mesh_" + tlabel + ".txt";
        std::ifstream infile(fname.c_str());
        utils::find_line(infile, "Surface");
        Surface f(infile);
        infile.close();
        infile.clear();
        std::string expected("Surface\n          6\n          0          1\n");
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
        std::string actual = f.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Surface.cpp
