/*=============================================================================

test_Ray.cpp
Definitions for unit, integration, and regression tests for class Ray.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 24 December 2014
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
#include "../src/Database.h"
#include "../src/Vector3d.h"
#include "../src/Node.h"
#include "../src/Grid.h"
#include "../src/Face.h"
#include "../src/Sphere.h"
#include "../src/Polygon.h"
#include "../src/Cone.h"
#include "../src/Surface.h"
#include "../src/Zone.h"
#include "../src/Mesh.h"
#include "../src/Ray.h"

#define CurntZone const_cast<Zone *>(m.get_zone(ray.wpt.top().outface.my_zone))

void test_Ray(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "Ray";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_ctor_diag_id", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Ray rx;
        int expected(-1);
        int actual(rx.diag_id);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_ctor_patch_id_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Ray rx;
        size_t expected(0);
        size_t actual(rx.patch_id.first);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_ctor_patch_id_second", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Ray rx;
        size_t expected(0);
        size_t actual(rx.patch_id.second);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_ctor_bundle_id_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Ray rx;
        size_t expected(0);
        size_t actual(rx.bundle_id.first);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_ctor_bundle_id_second", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Ray rx;
        size_t expected(0);
        size_t actual(rx.bundle_id.second);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_ctor_zid", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Ray rx;
        size_t expected(0);
        size_t actual(rx.zid);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_ctor_n", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Ray rx;
        size_t expected(0);
        size_t actual(rx.size());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_ctor_nzones", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Ray rx;
        size_t expected(0);
        size_t actual(rx.get_nzones());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_tracking", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Ray rx;
        bool expected(false);
        bool actual = rx.get_tracking();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "abs_diff_no_array", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d vx(1.0, 2.0, 3.0);
        Vector3d vy(5.0, -10.0, 0.0);
        Ray rx(0, 0, 2, 0, 1, false, vx, vx, false, "", "");
        Ray ry(0, 0, 2, 0, 1, false, vy, vy, false, "", "");
        double expected = 26.0;
        double actual = rx.abs_diff(ry);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "abs_diff", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d vx(1.0, 2.0, 3.0);
        Vector3d vy(5.0, -10.0, 0.0);
        ArrDbl x(2);
        x.at(0) = 7.0;
        x.at(1) = -2.0;
        ArrDbl y(1);
        y.at(0) = -5.0;
        Ray rx(0, 0, 2, 0, 1, false, vx, vx, false, x, "", "");
        Ray ry(0, 0, 2, 0, 1, false, vy, vy, false, y, "", "");
        double expected = 39.0;
        double actual = rx.abs_diff(ry);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d vx(7.0e-11, 0.0, -500.0);
        ArrDbl x(2);
        x.at(0) = 7.0;
        x.at(1) = -2.0;
        Ray rx(0, 0, 2, 0, 1, false, vx, vx, false, x, "", "");
        size_t expected = 2;
        size_t actual = rx.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_no_array", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d vx(7.0e-11, 0.0, -500.0);
        Ray rx(0, 0, 0, 0, 0, false, vx, vx, false, "", "");
        std::string expected = "   7.000000e-11   0.000000e+00  -5.000000e+02";
                    expected+= "   7.000000e-11   0.000000e+00  -5.000000e+02";
                    expected+= "\n          0\n          0";
        std::string actual = rx.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Vector3d vx(7.0e-11, 0.0, -500.0);
        ArrDbl x(2);
        x.at(0) = 7.0;
        x.at(1) = -2.0;
        Ray rx(0, 0, 2, 0, 1, false, vx, vx, false, x, "", "");
        std::string expected = "   7.000000e-11   0.000000e+00  -5.000000e+02";
                    expected+= "   7.000000e-11   0.000000e+00  -5.000000e+02";
                    expected+= "\n          0\n          2\n";
                    expected+= "   7.000000e+00\n  -2.000000e+00";
        std::string actual = rx.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_backlighter_flat", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string back_type("flat");
        #include "backlit_Ray.inc"
        double expected(500.0);
        double actual(ray.y.at(0));

        failed_test_count += t.check_equal_real_num(expected, actual, 100*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_backlighter_temp", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string back_type("blackbody");
        #include "backlit_Ray.inc"
        double expected(788906361433.20398); // 0.5 keV Planckian at hv = 1 keV
        double actual(ray.y.at(0));

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "transport_thin", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "transport_Ray.inc"
        double expected(139.99999999976001);
        double actual(ray.y.at(0));

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "transport_intermediate", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "transport_Ray.inc"
        double expected(75.904463047023839);
        double actual(ray.y.at(1));

        failed_test_count += t.check_equal_real_num(expected, actual, 100*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "transport_thick", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "transport_Ray.inc"
        double expected(10.000061442123533);
        double actual(ray.y.at(2));

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "trace_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        Vector3d expected(-12.968712349342937, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "trace_v", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        Vector3d expected(2.0, 0.0, 0.0);
        Vector3d actual(ray.v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "trace_zid", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        size_t expected(0);
        size_t actual(ray.zid);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone0_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(0.0, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone0_v", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(2.0, 0.0, 0.0);
        Vector3d actual(ray.v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone0_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        size_t expected(3); // number of remaining HitPoints
        size_t actual(ray.wpt.size());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone1_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(1.0, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone1_v", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(2.0, 0.0, 0.0);
        Vector3d actual(ray.v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone1_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        size_t expected(2); // number of remaining HitPoints
        size_t actual(ray.wpt.size());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone3_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(2.0, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone3_v", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(2.0, 0.0, 0.0);
        Vector3d actual(ray.v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone3_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        size_t expected(1); // number of remaining HitPoints
        size_t actual(ray.wpt.size());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone_last_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(12.968712349342937, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone_last_v", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(2.0, 0.0, 0.0);
        Vector3d actual(ray.v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone_last_zid", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        size_t expected(0);
        size_t actual(ray.zid);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Zone_last_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        size_t expected(0); // number of remaining HitPoints
        size_t actual(ray.wpt.size());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Mesh_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Mesh(m, d, tbl, "none", 0);
        Vector3d expected(12.968712349342937, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Mesh_v", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Mesh(m, d, tbl, "none", 0);
        Vector3d expected(2.0, 0.0, 0.0);
        Vector3d actual(ray.v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Mesh_zid", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Mesh(m, d, tbl, "none", 0);
        size_t expected(0);
        size_t actual(ray.zid);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Mesh_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace.inc"
        ray.cross_Mesh(m, d, tbl, "none", 0);
        size_t expected(0); // number of remaining HitPoints
        size_t actual(ray.wpt.size());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_trace_y", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ArrDbl expected;
        expected.assign(3, 0.0);
        ArrDbl actual(ray.y);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_trace_ite", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        size_t expected(0);
        size_t actual = ray.ite;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_trace_itr", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        size_t expected(0);
        size_t actual = ray.itr;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_trace_ine", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        size_t expected(0);
        size_t actual = ray.ine;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_trace_em", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ArrDbl expected;
        expected.assign(3, -1.0);
        ArrDbl actual(ray.em);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_trace_ab", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ArrDbl expected;
        expected.assign(3, -2.0);
        ArrDbl actual(ray.ab);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_trace_sc", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ArrDbl expected;
        expected.assign(3, -3.0);
        ArrDbl actual(ray.sc);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_trace_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        Vector3d expected(-12.968712349342937, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_trace_v", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        Vector3d expected(2.0, 0.0, 0.0);
        Vector3d actual(ray.v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_em_Zone0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        CurntZone->load_spectra(d, tbl, ray.ite, ray.itr, ray.ine,
                                  "none", 0, false, 0, 2,
                                  ray.em, ray.ab, ray.sc);
        ArrDbl expected;
        expected.assign(3, 0.0); // vacuum (Zone's nmat = 0)
        ArrDbl actual(ray.em);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_ab_Zone0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        CurntZone->load_spectra(d, tbl, ray.ite, ray.itr, ray.ine,
                                  "none", 0, false, 0, 2,
                                  ray.em, ray.ab, ray.sc);
        ArrDbl expected;
        expected.assign(3, 0.0); // vacuum (Zone's nmat = 0)
        ArrDbl actual(ray.ab);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "load_sc_Zone0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        CurntZone->load_spectra(d, tbl, ray.ite, ray.itr, ray.ine,
                                  "none", 0, false, 0, 2,
                                  ray.em, ray.ab, ray.sc);
        ArrDbl expected;
        expected.assign(3, 0.0); // vacuum (Zone's nmat = 0)
        ArrDbl actual(ray.sc);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "number_of_crossed_Zones", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        size_t expected(4);
        size_t actual(ray.get_nzones());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone0_y", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected;
        expected.assign(3, 0.0);
        ArrDbl actual(ray.y);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone0_y_to_file", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 1);
        std::string expected("File name for zone_iz0\nRest of header");
        expected += "\niz 0   1.296871e+01 cm\nZoneID 0\ndata in W/cm2/sr/eV";
        expected += "\n   0.000000e+00\n   0.000000e+00\n   0.000000e+00";
        std::string actual(utils::file_to_string("UniTest/Output/partial_iz0.txt"));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone0_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(0.0, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone1_ine", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        size_t expected(5);
        size_t actual(ray.ine);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone1_em", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3);
        expected.at(0) = 4.06e30;
        expected.at(1) = 8.12e30;
        expected.at(2) = 2.03e31;
        ArrDbl actual(ray.em);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone1_ab", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3);
        expected.at(0) = 6.04e-12;
        expected.at(1) = 6.04e-1;
        expected.at(2) = 6.04e0;
        ArrDbl actual(ray.ab);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone1_sc", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3);
        expected.at(0) = 6.04e-13;
        expected.at(1) = 6.04e-2;
        expected.at(2) = 6.04e-1;
        ArrDbl actual(ray.sc);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone1_y", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3);
        expected.at(0) = 4.06e30;
        expected.at(1) = 5.932559696843195e+30;
        expected.at(2) = 3.0514107865117147e+30;
        ArrDbl actual(ray.y);

        failed_test_count += t.check_equal_real_obj(expected, actual, 1.0e16);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone1_y_to_file", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 1);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 1);
        std::string expected("File name for zone_iz1\nRest of header");
        expected += "\niz 1   1.396871e+01 cm\nZoneID 1\ndata in W/cm2/sr/eV";
        expected += "\n   4.060000e+30\n   5.932560e+30\n   3.051411e+30";
        std::string actual(utils::file_to_string("UniTest/Output/partial_iz1.txt"));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone1_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(1.0, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone3_ine", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        size_t expected(5);
        size_t actual(ray.ine);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone3_em", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3);
        expected.at(0) = 4.06e30;
        expected.at(1) = 8.12e30;
        expected.at(2) = 2.03e31;
        ArrDbl actual(ray.em);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone3_ab", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3);
        expected.at(0) = 6.04e-12;
        expected.at(1) = 6.04e-1;
        expected.at(2) = 6.04e0;
        ArrDbl actual(ray.ab);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone3_sc", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3);
        expected.at(0) = 6.04e-13;
        expected.at(1) = 6.04e-2;
        expected.at(2) = 6.04e-1;
        ArrDbl actual(ray.sc);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone3_y", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3);
        expected.at(0) = 8.1199999999730247e+30;
        expected.at(1) = 8.9853492247934706e+30;
        expected.at(2) = 3.0553831422974185e+30;
        ArrDbl actual(ray.y);

        failed_test_count += t.check_equal_real_obj(expected, actual, 1.0e16);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone3_y_to_file", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 1);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 1);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 1);
        std::string expected("File name for zone_iz2\nRest of header");
        expected += "\niz 2   1.496871e+01 cm\nZoneID 3\ndata in W/cm2/sr/eV";
        expected += "\n   8.120000e+30\n   8.985349e+30\n   3.055383e+30";
        std::string actual(utils::file_to_string("UniTest/Output/partial_iz2.txt"));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone3_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(2.0, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone_last_ine", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        size_t expected(5);
        size_t actual(ray.ine);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone_last_em", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3); // vacuum (Zone nmat = 0)
        ArrDbl actual(ray.em);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone_last_ab", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3); // vacuum (Zone nmat = 0)
        ArrDbl actual(ray.ab);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone_last_sc", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3); // vacuum (Zone nmat = 0)
        ArrDbl actual(ray.sc);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone_last_y", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ArrDbl expected(3);
        expected.at(0) = 8.1199999999730247e+30;
        expected.at(1) = 8.9853492247934706e+30;
        expected.at(2) = 3.0553831422974185e+30;
        ArrDbl actual(ray.y);

        failed_test_count += t.check_equal_real_obj(expected, actual, 1.0e16);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone_last_y_to_file", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 1);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 1);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 1);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 1);
        std::string expected("File name for zone_iz3\nRest of header");
        expected += "\niz 3   2.593742e+01 cm\nZoneID 0\ndata in W/cm2/sr/eV";
       expected += "\n   8.120000e+30\n   8.985349e+30\n   3.055383e+30";
        std::string actual(utils::file_to_string("UniTest/Output/partial_iz3.txt"));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "after_Zone_last_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        ray.cross_Zone(CurntZone, d, tbl, "none", 0, 0);
        Vector3d expected(12.968712349342937, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Mesh_from_Hydro1_y", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Mesh(m, d, tbl, "none", 0);
        ArrDbl expected(3);
        expected.at(0) = 8.1199999999730247e+30;
        expected.at(1) = 8.9853492247934706e+30;
        expected.at(2) = 3.0553831422974185e+30;
        ArrDbl actual(ray.y);

        failed_test_count += t.check_equal_real_obj(expected, actual, 1.0e16);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Mesh_from_Hydro1_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Mesh(m, d, tbl, "none", 0);
        Vector3d expected(12.968712349342937, 0.75, 0.5);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Mesh_from_Hydro1_v", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_Mesh.inc"
        ray.cross_Mesh(m, d, tbl, "none", 0);
        Vector3d expected(2.0, 0.0, 0.0);
        Vector3d actual(ray.v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
// pmh_2015_0522: path through material between HitPoints #1 and #3
// #1 - #3 = (5 - 2.75, 7 - 3.625, 10 - 1) = (2.25, 3.375, 9.0)
// chord length t = 9.871834935816
// y = em / op * (1 - exp(-op*t)) in general
// y = em * t in the optically thin limit (element at 0)
    Test t(GROUP, "cross_Mesh_from_Hydro4_y", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_conic_Mesh.inc"
        ray.cross_Mesh(m, d, tbl, "none", 0);
        ArrDbl expected(3);
        expected.at(0) = 4.007964983915389e+31;
        expected.at(1) = 1.220422899739185e+31;
        expected.at(2) = 3.055388320288982e+30;
        ArrDbl actual(ray.y);

        failed_test_count += t.check_equal_real_obj(expected, actual, 1.0e16);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Mesh_from_Hydro4_r", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_conic_Mesh.inc"
        ray.cross_Mesh(m, d, tbl, "none", 0);
        Vector3d expected(-20.6592869168006,
                          -31.488930375200901, -92.637147667202399);
        Vector3d actual(ray.r);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "cross_Mesh_from_Hydro4_v", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "trace_conic_Mesh.inc"
        ray.cross_Mesh(m, d, tbl, "none", 0);
        Vector3d expected(-2.0, -3.0, -8.0);
        Vector3d actual(ray.v);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

}

#undef CurntZone

// end test_Ray.cpp
