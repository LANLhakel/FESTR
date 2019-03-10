/*=============================================================================

test_Diagnostics.cpp
Definitions for unit, integration, and regression tests for class Diagnostics.

pmh_2015_0210
pmh_2015_0312

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 5 February 2015
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
#include "../src/Diagnostics.h"
#include "../src/Goal.h"
#include "../src/Node.h"
#include "../src/Grid.h"
#include "../src/Mesh.h"
#include "../src/Database.h"
#include "../src/Hydro.h"
#include "../src/utilities.h"

#include <cstdlib>

void test_Diagnostics(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "Diagnostics";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Diagnostics diag;
        size_t expected(0);
        size_t actual = diag.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Hydro2/");
        std::string tlabel("0");
        Database d("none", cnst::PATH + "UniTest/Dbase3/", false);
        Diagnostics diag(0, cnst::PATH + "UniTest/Diagnostics1/", path, cnst::PATH, d);
        size_t expected(2);
        size_t actual = diag.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Hydro2/");
        std::string tlabel("0");
        Database d("none", cnst::PATH + "UniTest/Dbase3/", false);
        Diagnostics diag(0, cnst::PATH + "UniTest/Diagnostics1/", path, cnst::PATH, d);
        std::string s("Number of Detectors  2\n");
        s += "Detector_Name ntheta nphi";
        s += "\nDetectorName0           0           0";
        s += "\nDetectorName1           0           0";
        std::string expected(s);
        std::string actual = diag.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_to_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        std::string s("DetectorName0");
        s += "\nrc   2.000000e+01   5.000000e-01   5.000000e-01";
        s += "\nrx   0.000000e+00   5.000000e-01   0.000000e+00";
        s += "\nry   0.000000e+00   0.000000e+00   5.000000e-01";
        s += "\ndx   5.000000e-01\ndy   2.000000e-01";
        s += "\nfwhm  -3.000000e+00\nbacklighter flat   0.000000e+00";
        s += "\ntracking false";
        std::string expected(s);
        std::string actual = det.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_get_name", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        (void)(det);
        std::string expected("DetectorName0");
        std::string actual = diag.get_name(0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_get_index", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        (void)(det);
        size_t expected(0);
        size_t actual = diag.get_index("DetectorName0");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "nonexistent_get_index", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        (void)(det);
        size_t expected(2);
        size_t actual = diag.get_index("nonexistent");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_nhv", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        size_t expected(3);
        size_t actual = det.get_nhv();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_nx", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        size_t expected(2);
        size_t actual = det.get_nx();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_ny", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        size_t expected(5);
        size_t actual = det.get_ny();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_vertex0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Vector3d expected(20.0, 0.0, 0.0);
        Vector3d actual = det.get_vertex(0);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_vertex1", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Vector3d expected(20.0, 1.0, 0.0);
        Vector3d actual = det.get_vertex(1);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_vertex2", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Vector3d expected(20.0, 1.0, 1.0);
        Vector3d actual = det.get_vertex(2);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_vertex3", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Vector3d expected(20.0, 0.0, 1.0);
        Vector3d actual = det.get_vertex(3);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_ux", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Vector3d expected(0.0, 0.5, 0.0);
        Vector3d actual = det.get_ux();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_uy", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Vector3d expected(0.0, 0.0, 0.2);
        Vector3d actual = det.get_uy();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_ex", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Vector3d expected(0.0, 1.0, 0.0);
        Vector3d actual = det.get_ex();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_ey", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Vector3d expected(0.0, 0.0, 1.0);
        Vector3d actual = det.get_ey();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_ez", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Vector3d expected(1.0, 0.0, 0.0);
        Vector3d actual = det.get_ez();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_ro", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Vector3d expected(20.0, 0.25, 0.1);
        Vector3d actual = det.get_ro();

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_theta_max", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        double expected(0.7535206165997118); // asin(13.0/19.0)
        double actual = det.get_theta_max();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_ntheta0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        size_t expected(0);
        size_t actual = det.get_ntheta();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_nphi0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        size_t expected(0);
        size_t actual = det.get_nphi();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_dtheta0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        double expected(0.0);
        double actual = det.get_dtheta();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_dtheta2_0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        double expected(0.0);
        double actual = det.get_dtheta2();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_dphi0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        double expected(0.0);
        double actual = det.get_dphi();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_ntheta", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        #include "set_bundle.inc"
        size_t expected(10);
        size_t actual = det.get_ntheta();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_nphi", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        #include "set_bundle.inc"
        size_t expected(360);
        size_t actual = det.get_nphi();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_dtheta", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        #include "set_bundle.inc"
        double expected(0.07535206165997118);
        double actual = det.get_dtheta();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_dtheta2", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        #include "set_bundle.inc"
        double expected(0.03767603082998559);
        double actual = det.get_dtheta2();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_dphi", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        #include "set_bundle.inc"
        double expected(cnst::PI/180.0);
        double actual = det.get_dphi();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_times_file_copy", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        (void)(det);
        std::string fname(cnst::PATH + "UniTest/Output/times.txt");
        std::string expected("# Number of time instants");
        expected += "\n# Time instants in seconds";
        expected += "\n# start\n3\n0 0.0e-9\n1 1.0e-9\n2 7.0e-9";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_time1_do_patch", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Goal gol;
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-yp_ix1_iy2_time1.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "Detector0_time1_do_patch" << std::endl;
            exit(EXIT_FAILURE);
        }

        det.do_patch(NULL, IntPair(1, 2), g, m, d, tbl, it,
                     h.time_at(it), h.dt_at(it), h.get_ntd(), false, gol);
        std::string expected("DetectorName0-yp_ix1_iy2_time1");
        expected += "\ntime 1    1.000000e-09 s";
        expected += "\nix 1   7.500000e-01 cm";
        expected += "\niy 2   5.000000e-01 cm\ndata in W/cm2/sr/eV";
        expected += "\n   8.120000e+30\n   8.985349e+30\n   3.055383e+30";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_do_patches_last_yp", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Goal gol;
        std::string fname;
        std::string fnamer(cnst::PATH + "UniTest/Output/" + det.get_dname() + "-yp");
        for (size_t ix = 0; ix < det.get_nx(); ++ix)
            for (size_t iy = 0; iy < det.get_ny(); ++iy)
            {
                fname = fnamer + det.patch_fname(IntPair(ix, iy))
                      + "_time1.txt";

                std::string cmnd("rm -rf " + fname);
                if (system(cmnd.c_str()) != 0)
                {
                    std::cerr << "\nError: system call failure in test "
                              << "Diagnostics_Detector0_do_patches_last_yp"
                              << std::endl;
                    exit(EXIT_FAILURE);
                }
            }

        det.do_patches(NULL, g, m, d, tbl, it,
                       h.time_at(it), h.dt_at(it), h.get_ntd(), gol);
        std::string expected("DetectorName0-yp_ix1_iy4_time1");
        expected += "\ntime 1    1.000000e-09 s";
        expected += "\nix 1   7.500000e-01 cm";
        expected += "\niy 4   9.000000e-01 cm\ndata in W/cm2/sr/eV";
        expected += "\n   8.120000e+30\n   8.985349e+30\n   3.055383e+30";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector0_do_patches_ys", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Goal gol;
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-ys_time1.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "Detector0_do_patches_ys" << std::endl;
            exit(EXIT_FAILURE);
        }

        det.do_patches(NULL, g, m, d, tbl, it,
                       h.time_at(it), h.dt_at(it), h.get_ntd(), gol);
        std::string expected("DetectorName0-ys_time1");
        expected += "\ntime 1    1.000000e-09 s";
        expected += "\ndata in W/sr/eV";
        expected += "\n   8.120000e+30\n   8.985349e+30\n   3.055383e+30";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_Detector0_yst", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Goal gol;
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-yst.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_Detector0_yst" << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("DetectorName0-yst\ndata in J/sr/eV");
        #ifdef MPIYES
        expected += "\n   5.278000e+22\n   5.984465e+22\n   2.138371e+22";
        #else
        expected += "\n   5.278000e+22\n   5.984466e+22\n   2.138371e+22";
        #endif
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_Detector0_last_yt", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Goal gol;
        std::string fname;
        std::string fnamer(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fnamer += "-yt";
        for (size_t ix = 0; ix < det.get_nx(); ++ix)
            for (size_t iy = 0; iy < det.get_ny(); ++iy)
            {
                fname = fnamer + det.patch_fname(IntPair(ix, iy)) + ".txt";

                std::string cmnd("rm -rf " + fname);
                if (system(cmnd.c_str()) != 0)
                {
                    std::cerr << "\nError: system call failure in test "
                              << "Diagnostics_execute_Detector0_last_yt"
                              << std::endl;
                    exit(EXIT_FAILURE);
                }
            }

        diag.execute(d, h, gol);
        std::string expected("DetectorName0-yt_ix1_iy4");
        expected += "\nix 1   7.500000e-01 cm";
        expected += "\niy 4   9.000000e-01 cm\ndata in J/cm2/sr/eV";
        #ifdef MPIYES
        expected += "\n   5.278000e+22\n   5.984465e+22\n   2.138371e+22";
        #else
        expected += "\n   5.278000e+22\n   5.984466e+22\n   2.138371e+22";
        #endif
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Detector1_do_patches_ys", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Goal gol;
        det = diag.det.at(1);
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-ys_time1.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "Detector1_do_patches_ys" << std::endl;
            exit(EXIT_FAILURE);
        }

        det.do_patches(NULL, g, m, d, tbl, it,
                       h.time_at(it), h.dt_at(it), h.get_ntd(), gol);
        std::string expected("DetectorName1-ys_time1");
        expected += "\ntime 1    1.000000e-09 s";
        expected += "\ndata in W/sr/eV";
        expected += "\n   8.120000e+30\n   1.186512e+31\n   6.102822e+30";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_Detector1_yst", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics1.inc"
        Goal gol;
        det = diag.det.at(1);
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-yst.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_Detector1_yst" << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("DetectorName1-yst\ndata in J/sr/eV");
        expected += "\n   5.278000e+22\n   7.712328e+22\n   3.966834e+22";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_Sphere1d_symmetry_none_center_patch", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics2.inc"
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-yp_ix2_iy2_time0.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_Sphere1d_symmetry_none_center_patch"
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("Sphere1d-yp_ix2_iy2_time0\n");
        expected += "time 0    0.000000e+00 s\n";
        expected += "ix 2   5.000000e-01 cm\n";
        expected += "iy 2   5.000000e-01 cm\ndata in W/cm2/sr/eV\n";
        expected += "   4.060000e+30\n   5.932560e+30\n   3.051411e+30";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_Sphere1d_symmetry_none_time0_ys", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics2.inc"
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-ys_time0.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_Sphere1d_symmetry_none_time0_ys"
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("Sphere1d-ys_time0\ntime 0    0.000000e+00 s\n");
        expected += "data in W/sr/eV\n";
        expected += "   2.264222e+30\n   3.602169e+30\n   2.504046e+30";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_Sphere1d_symmetry_none_yst", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics2.inc"
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-yst.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_Sphere1d_symmetry_none_yst"
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("Sphere1d-yst\ndata in J/sr/eV\n");
        expected += "   1.584955e+22\n   2.521518e+22\n   1.752832e+22";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_Sphere1d_nhv1_symm_none_center_patch", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics2.inc"
        det = diag.det.at(1);
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-yp_ix2_iy2_time0.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_Sphere1d_nhv1_symm_none_center_patch"
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("Sphere1d_nhv1-yp_ix2_iy2_time0\n");
        expected += "time 0    0.000000e+00 s\n";
        expected += "ix 2   5.000000e-01 cm\n";
        expected += "iy 2   5.000000e-01 cm\ndata in W/cm2/sr/eV\n";
        expected += "   5.932560e+30";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_Sphere1d_nhv1_symm_none_time0_ys", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics2.inc"
        det = diag.det.at(1);
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-ys_time0.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_Sphere1d_nhv1_symm_none_time0_ys"
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("Sphere1d_nhv1-ys_time0\n");
        expected += "time 0    0.000000e+00 s\n";
        expected += "data in W/sr/eV\n";
        expected += "   3.602169e+30";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_Sphere1d_nhv1_symm_none_yst", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics2.inc"
        det = diag.det.at(1);
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-yst.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_Sphere1d_nhv1_symm_none_yst"
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("Sphere1d_nhv1-yst\ndata in J/sr/eV\n");
        expected += "   2.521518e+22";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP,"execute_SphSym1d_symmetry_spherical_center_patch","fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics3.inc"
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-yp_ix000_iy0_time0.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_SphSym1d_symmetry_spherical_center_patch"
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("SphSym1d-yp_ix000_iy0_time0\n");
        expected += "time 0    0.000000e+00 s\n";
        expected += "ix   0   0.000000e+00 cm\n";
        expected += "iy 0   0.000000e+00 cm\ndata in W/cm2/sr/eV\n";
        expected += "   4.060000e+30\n   5.932560e+30\n   3.051411e+30";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_SphSym1d_symmetry_spherical_time0_ys", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics3.inc"
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-ys_time0.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_SphSym1d_symmetry_spherical_time0_ys"
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("SphSym1d-ys_time0\ntime 0    0.000000e+00 s\n");
        expected += "data in W/sr/eV\n";
        expected += "   2.125861e+30\n   3.356824e+30\n   2.292266e+30";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_SphSym1d_symmetry_spherical_yst", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics3.inc"
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-yst.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_SphSym1d_symmetry_spherical_yst"
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("SphSym1d-yst\ndata in J/sr/eV\n");
        #ifdef MPIYES
        expected += "   1.488103e+22\n   2.349777e+22\n   1.604586e+22";
        #else
        expected += "   1.488103e+22\n   2.349777e+22\n   1.604587e+22";
        #endif
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "execute_SphSym1d_flat_backlighter_center_patch", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "diagnostics4.inc"
        std::string fname(cnst::PATH + "UniTest/Output/" + det.get_dname());
        fname += "-yp_ix000_iy0_time0.txt";

        std::string cmnd("rm -rf " + fname);
        if (system(cmnd.c_str()) != 0)
        {
            std::cerr << "\nError: system call failure in test Diagnostics_"
                      << "execute_SphSym1d_flat_backlighter_center_patch"
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        diag.execute(d, h, gol);
        std::string expected("SphSym1d-yp_ix000_iy0_time0\n");
        expected += "time 0    0.000000e+00 s\n";
        expected += "ix   0   0.000000e+00 cm\n";
        expected += "iy 0   0.000000e+00 cm\ndata in W/cm2/sr/eV\n";
        expected += "   7.060000e+30\n   7.476306e+30\n   3.055316e+30";
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

// end test_Diagnostics.cpp
