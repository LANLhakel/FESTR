/*=============================================================================

test_Hydro.cpp
Definitions for unit, integration, and regression tests for class Hydro.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 7 January 2015
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
#include "../src/constants.h"
#include "../src/Hydro.h"
#include "../src/Goal.h"

#include <stdexcept>

void test_Hydro(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "Hydro";
const double EQT = 1.0e-24;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Table_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        size_t expected = 3;
        Table tbl = h.get_table();
        size_t actual = tbl.size();
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Table_argon_Z", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        int expected = 18;
        int actual = h.get_table().get_Z("ar");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Table_argon_A", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        double expected = 39.948;
        double actual = h.get_table().get_A("ar");

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Table_argon_N", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        int expected = 22;
        int actual = h.get_table().get_N("ar");
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Table_argon_F", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        std::string expected("z18");
        std::string actual = h.get_table().get_F("ar");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Table_not_present_Z", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        std::string expected = "heavy_water is not present in Table";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            int i = h.get_table().get_Z("heavy_water");
            std::cout << i << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Table_not_present_A", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        std::string expected = "heavy_water is not present in Table";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            double x = h.get_table().get_A("heavy_water");
            std::cout << x << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Table_not_present_N", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        std::string expected = "heavy_water is not present in Table";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            int i = h.get_table().get_N("heavy_water");
            std::cout << i << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Table_not_present_F", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        std::string expected = "heavy_water is not present in Table";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            std::string s = h.get_table().get_F("heavy_water");
            std::cout << s << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_analysis", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        bool expected(false);
        bool actual = h.get_analysis();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_nzones", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        size_t expected(0);
        size_t actual = h.get_nzones();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_path", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        std::string expected = hydro_path;
        std::string actual = h.get_path();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_ntimes", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        size_t expected = 3;
        size_t actual = h.get_ntimes();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_nintervals", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        size_t expected = 2;
        size_t actual = h.get_nintervals();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_ntd", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        int expected = 1;
        int actual = h.get_ntd();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_time_at_2", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        double expected = 7.0e-9;
        double actual = h.time_at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_dt_at_1", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        double expected = 6.0e-9;
        double actual = h.dt_at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Time0_Grid_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        Grid g;
        Mesh m;
        h.load_at(0, g, m);
        size_t expected = 8;
        size_t actual = g.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Time0_Grid_Node5", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        Grid g;
        Mesh m;
        h.load_at(0, g, m);
        Vector3d v(1.0, 0.0, 1.0);
        Node expected(5, v, v);
        Node actual = g.get_node(5);

        failed_test_count += t.check_equal_real_obj(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Time0_Mesh_size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        Grid g;
        Mesh m;
        h.load_at(0, g, m);
        size_t expected = 2;
        size_t actual = m.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Time0_Mesh_to_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        Grid g;
        Mesh m;
        h.load_at(0, g, m);
        std::string fname = hydro_path + "mesh_0.txt";
        std::string expected(utils::file_to_string(fname));
        std::string actual = m.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Time0_Mesh_Zone1_te", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        Grid g;
        Mesh m;
        h.load_at(0, g, m);
        double expected = 6400.0;
        double actual = m.get_zone(1)->get_te();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Time0_Mesh_Zone1_tr", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        Grid g;
        Mesh m;
        h.load_at(0, g, m);
        double expected = 200.0;
        double actual = m.get_zone(1)->get_tr();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Time0_Mesh_Zone1_np", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        Grid g;
        Mesh m;
        h.load_at(0, g, m);
        double expected = 1.0e16;
        double actual = m.get_zone(1)->get_np();

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e5);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Time0_Mesh_Zone1_nmat", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        Grid g;
        Mesh m;
        h.load_at(0, g, m);
        unsigned short int expected = 3;
        unsigned short int actual = m.get_zone(1)->get_nmat();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Time0_Mesh_Zone1_fp0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        Grid g;
        Mesh m;
        h.load_at(0, g, m);
        double expected = 0.5;
        double actual = m.get_zone(1)->fp_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Time0_Mesh_Zone1_fp1", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        Grid g;
        Mesh m;
        h.load_at(0, g, m);
        double expected = 0.1;
        double actual = m.get_zone(1)->fp_at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Hydro1_Time0_Mesh_Zone1_fp2", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "hydro1.inc"
        Grid g;
        Mesh m;
        h.load_at(0, g, m);
        double expected = 0.4;
        double actual = m.get_zone(1)->fp_at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis1_analysis", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis1_hydro.inc"
        bool expected(true);
        bool actual = h.get_analysis();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis1_nzones", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis1_hydro.inc"
        size_t expected(4);
        size_t actual = h.get_nzones();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis1_ndim", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis1_hydro.inc"
        std::string expected("          1        240          9          6");
        std::vector<size_t> act = h.get_ndim();
        std::string actual = utils::int_to_string(act.at(0), ' ', cnst::INT_WIDTH)
                           + utils::int_to_string(act.at(1), ' ', cnst::INT_WIDTH)
                           + utils::int_to_string(act.at(2), ' ', cnst::INT_WIDTH)
                           + utils::int_to_string(act.at(3), ' ', cnst::INT_WIDTH);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis1_ncases", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis1_hydro.inc"
        size_t expected(12960); // = Product(ndim) = 1 * 240 * 9 * 6
        size_t actual = h.get_nintervals(); // used for "ncases" in analysis

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis1_ntimes", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis1_hydro.inc"
        size_t expected(12961);
        size_t actual = h.get_ntimes(); // used for "ncases+1" in analysis

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis1_get_symmetry", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis1_hydro.inc"
        std::string expected("none");
        std::string actual = h.get_symmetry();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis1_get_symmetry_spherical", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis1_hydro.inc"
        h.set_symmetry("spherical");
        std::string expected("spherical");
        std::string actual = h.get_symmetry();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis1_get_symmetry", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis1_hydro.inc"
        std::string expected("none");
        std::string actual = h.get_symmetry();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis1_ntd", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis1_hydro.inc"
        int expected = 1;
        int actual = h.get_ntd();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis1_time_at_1", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis1_hydro.inc"
        double expected = 1.0;
        double actual = h.time_at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis1_dt_at_0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis1_hydro.inc"
        double expected = 1.0;
        double actual = h.dt_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis2_ncases", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis2_hydro.inc"
        size_t expected(256); // = Sum(ndim) = 1 + 240 + 9 + 6
        size_t actual = h.get_nintervals(); // used for "ncases" in analysis

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis2_ntimes", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis2_hydro.inc"
        size_t expected(257);
        size_t actual = h.get_ntimes(); // used for "ncases+1" in analysis

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Analysis2_get_symmetry", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "analysis2_hydro.inc"
        std::string expected("spherical");
        std::string actual = h.get_symmetry();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

// end test_Hydro.cpp
