/*=============================================================================

test_Detector.cpp
Definitions for unit, integration, and regression tests for class Detector.

pmh_2015_0210

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 28 January 2015
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
#include "../src/Detector.h"
#include "../src/Sphere.h"
#include "../src/Surface.h"
#include "../src/Mesh.h"

#include <cstdlib>

void test_Detector(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "Detector";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Detector det;
        std::string s("no_name");
        s += "\nrc   0.000000e+00   0.000000e+00   0.000000e+00";
        s += "\nrx   0.000000e+00   0.000000e+00   0.000000e+00";
        s += "\nry   0.000000e+00   0.000000e+00   0.000000e+00";
        s += "\ndx   0.000000e+00\ndy   0.000000e+00";
        s += "\nfwhm  -1.000000e+00\nbacklighter none  -9.000000e+00";
        s += "\ntracking false";
        std::string expected(s);
        std::string actual = det.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        std::string s("DetectorName");
        s += "\nrc   1.000000e+01   2.000000e+01   5.000000e+01";
        s += "\nrx   3.000000e+00   4.000000e+00   1.200000e+01";
        s += "\nry  -4.000000e+00   3.000000e+00   0.000000e+00";
        s += "\ndx   5.000000e-01\ndy   2.000000e-01";
        s += "\nfwhm  -2.000000e+00\nbacklighter flat   7.000000e+00";
        s += "\ntracking true";
        std::string expected(s);
        std::string actual = det.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "path_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Detector det;
        std::string expected("no_path");
        std::string actual = det.get_path();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "path", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        std::string expected("UniTest/Output/");
        std::string actual = det.get_path();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "hv_grid", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string fname(cnst::PATH + "UniTest/Output/DetectorName-hv_grid.txt");

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test "
                      << "Detector_hv_grid" << std::endl;
            exit(EXIT_FAILURE);
        }

        #include "detector_init.inc"
        std::string expected("\n Number of bits:\n           0\n\n");
        expected += " Number of grid points:\n           3\n\n";
        expected += " Grid points:\n           0     3.000000e+02\n";
        expected += "           1     6.000000e+02\n";
        expected += "           2     9.000000e+02";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "backlighter", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string fname(cnst::PATH + "UniTest/Output/DetectorName-backlighter.txt");

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test "
                      << "Detector_backlighter" << std::endl;
            exit(EXIT_FAILURE);
        }

        #include "detector_init.inc"
        std::string expected("DetectorName-backlighter\n");
        expected += "data in W/cm2/sr/eV\n";
        expected += "   7.000000e+00\n   7.000000e+00\n   7.000000e+00";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "dname_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Detector det;
        std::string expected("no_name");
        std::string actual = det.get_dname();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fwhm_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Detector det;
        double expected(-1.0);
        double actual = det.get_fwhm();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "back_type_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Detector det;
        std::string expected("none");
        std::string actual = det.get_back_type();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "back_value_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Detector det;
        double expected(-9.0);
        double actual = det.get_back_value();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "tracking_empty", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Detector det;
        bool expected(false);
        bool actual = det.get_tracking();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "dname", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        std::string expected("DetectorName");
        std::string actual = det.get_dname();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "symmetry", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        std::string expected("none");
        std::string actual = det.get_symmetry();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "my_id", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        int expected(7);
        int actual = det.get_my_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rc", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(10.0, 20.0, 50.0);
        Vector3d actual = det.get_rc();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "rx", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(3.0, 4.0, 12.0);
        Vector3d actual = det.get_rx();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ry", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(-4.0, 3.0, 0.0);
        Vector3d actual = det.get_ry();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ex", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(3.0/13.0, 4.0/13.0, 12.0/13.0);
        Vector3d actual = det.get_ex();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ey", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(-0.8, 0.6, 0.0);
        Vector3d actual = det.get_ey();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ez", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(-0.55384615384615388,
                          -0.7384615384615385,
                           0.38461538461538464);
        Vector3d actual = det.get_ez();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nhv", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        size_t expected(3);
        size_t actual = det.get_nhv();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "hv", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        std::string expected = utils::double_to_string(300.0)
                             + utils::double_to_string(600.0)
                             + utils::double_to_string(900.0);
        std::vector<double> act = det.get_hv();
        std::string actual = "   3.000000e+02   6.000000e+02   9.000000e+02";

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fwhm", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        double expected(-2.0);
        double actual = det.get_fwhm();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nx", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        size_t expected(52);
        size_t actual = det.get_nx();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ny", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        size_t expected(50);
        size_t actual = det.get_ny();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "vertex0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(11.0, 13.0, 38.0);
        Vector3d actual = det.get_vertex(0);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "vertex1", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(17.0, 21.0, 62.0);
        Vector3d actual = det.get_vertex(1);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "vertex2", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(9.0, 27.0, 62.0);
        Vector3d actual = det.get_vertex(2);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "vertex3", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(3.0, 19.0, 38.0);
        Vector3d actual = det.get_vertex(3);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ux", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(3.0/26.0, 4.0/26.0, 12.0/26.0);
        Vector3d actual = det.get_ux();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "uy", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        Vector3d expected(-0.16, 0.12, 0.0);
        Vector3d actual = det.get_uy();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ro", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        double x = 11.0  +  1.5 / 26.0  -  0.08;
        double y = 13.0  +  2.0 / 26.0  +  0.06;
        double z = 38.0  +  6.0 / 26.0;
        Vector3d expected(x, y, z);
        Vector3d actual = det.get_ro();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "theta_max_init", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        double expected(0.0);
        double actual = det.get_theta_max();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ntheta_init", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        size_t expected(0);
        size_t actual = det.get_ntheta();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nphi_init", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        size_t expected(0);
        size_t actual = det.get_nphi();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "dtheta_init", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        double expected(0.0);
        double actual = det.get_dtheta();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "dtheta2_init", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        double expected(0.0);
        double actual = det.get_dtheta2();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "dphi_init", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        double expected(0.0);
        double actual = det.get_dphi();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "theta_max", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        det.set_bundle(1.5, 30, 360);
        double expected(1.5);
        double actual = det.get_theta_max();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ntheta", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        det.set_bundle(1.5, 30, 360);
        size_t expected(30);
        size_t actual = det.get_ntheta();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nphi", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        det.set_bundle(1.5, 30, 360);
        size_t expected(360);
        size_t actual = det.get_nphi();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "dtheta", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        det.set_bundle(1.5, 30, 360);
        double expected(0.05);
        double actual = det.get_dtheta();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "dtheta2", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        det.set_bundle(1.5, 30, 360);
        double expected(0.025);
        double actual = det.get_dtheta2();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "dphi", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        det.set_bundle(1.5, 30, 360);
        double expected(cnst::PI/180.0); // 0.017453292519943295
        double actual = det.get_dphi();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "theta_max", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        #include "mesh.inc"
        double expected(0.22436832280435448);
        double actual = det.compute_theta_max(sc, 13.0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_bx", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        #include "mesh.inc"
        Vector3d expected(0.5457958860232597,
                          0.727727848031013,
                          -0.4153541019422291);
        Vector3d actual = det.get_bx();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_by", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        #include "mesh.inc"
        Vector3d expected(-0.8164952874166548,
                          0.5732739253570094,
                          -0.06850147540133968);
        Vector3d actual = det.get_by();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_bz", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        #include "mesh.inc"
        Vector3d expected(0.1882612451527908,
                          0.3765224903055816,
                          0.9070769084634466);
        Vector3d actual = det.get_bz();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "local_to_global", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        #include "mesh.inc"
        Vector3d expected(2.743570196314942,
                          0.7107474682337391,
                          2.4428795742507896);
        Vector3d actual = det.local_to_global(Vector3d(1.0, -2.0, 3.0));

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "patch_string_symmetry_none", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        IntPair patch(2, 1);
        std::string expected;
        expected = ("ix  2   1.250000e+00 cm\niy  1   3.000000e-01 cm\n");
        std::string actual = det.patch_string(patch);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "patch_string_symmetry_spherical", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_sph.inc"
        IntPair patch(2, 1);
        std::string expected;
        expected = ("ix 2   4.000000e-01 cm\niy 1   0.000000e+00 cm\n");
        std::string actual = det.patch_string(patch);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sph_nx", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_sph.inc"
        size_t expected(3);
        size_t actual = det.get_nx();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sph_ny", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_sph.inc"
        size_t expected(1);
        size_t actual = det.get_ny();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sph_back_type", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_sph.inc"
        std::string expected("blackbody");
        std::string actual = det.get_back_type();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sph_back_value", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_sph.inc"
        double expected(7.0);
        double actual = det.get_back_value();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "sph_tracking", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_sph.inc"
        bool expected(false);
        bool actual = det.get_tracking();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "init_jmin", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        size_t expected(0);
        size_t actual = det.get_jmin();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "init_hvmin", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        double expected(300.0);
        double actual = det.get_hvmin();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "init_jmax", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        size_t expected(2);
        size_t actual = det.get_jmax();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "init_hvmax", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_init.inc"
        double expected(900.0);
        double actual = det.get_hvmax();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "hv_grid_jmin", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_hv_grid.inc"
        size_t expected(1);
        size_t actual = det.get_jmin();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "hv_grid_hvmin", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_hv_grid.inc"
        double expected(600.0);
        double actual = det.get_hvmin();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "hv_grid_jmax", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_hv_grid.inc"
        size_t expected(1);
        size_t actual = det.get_jmax();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "hv_grid_hvmax", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_hv_grid.inc"
        double expected(600.0);
        double actual = det.get_hvmax();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "hv_grid_nhv", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_hv_grid.inc"
        size_t expected(1);
        size_t actual = det.get_nhv();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "hv_grid_back_type", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_hv_grid.inc"
        std::string expected("blackbody");
        std::string actual = det.get_back_type();

        failed_test_count += t.check_equal(expected, actual);
    }
}
    
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "hv_grid_back_value", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_hv_grid.inc"
        double expected(7.0);
        double actual = det.get_back_value();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "hv_grid_tracking", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "detector_hv_grid.inc"
        bool expected(false);
        bool actual = det.get_tracking();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

// end test_Detector.cpp
