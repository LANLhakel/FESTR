/*=============================================================================

test_Cell.cpp
Definitions for unit, integration, and regression tests for class Cell.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 4 July 2015
Last modified on 2 February 2020

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

#include <test_Cell.h>
#include <Test.h>

#include <ArrDbl.h>
#include <constants.h>
#include <utils.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

void test_Cell(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Cell";

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_id", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Cell z;
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
        Cell z(5);
        size_t expected = 5;
        size_t actual = z.get_id();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "0_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        std::string expected = "Cell          0\n";
        expected += "te   0.000000e+00   0.000000e+00           1 lin eV\n";
        expected += "tr   0.000000e+00   0.000000e+00           1 lin eV\n";
        expected += "nmat           0\nmaterial densities (particles/cm3)";
        std::string actual = z0.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "1_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        std::string expected = "Cell          1\n";
        expected += "te   6.100000e+03   6.400000e+03           4 lin eV\n";
        expected += "tr   0.000000e+00   0.000000e+00           1 lin eV\n";
        expected += "nmat           2\nmaterial densities (particles/cm3)\n";
        expected += "d   1.000000e+19   2.000000e+19           6 lin\n";
        expected += "ar   3.000000e+19   4.000000e+19          10 lin";
        std::string actual = z1.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_nte", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        size_t expected = 4;
        size_t actual = z1.get_nte();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_tegrid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        std::string expected = "   6.100000e+03   6.200000e+03";
        expected += "   6.300000e+03   6.400000e+03";
        std::vector<double> act = z1.get_tegrid();
        std::string actual = utils::double_to_string(act.at(0))
                           + utils::double_to_string(act.at(1))
                           + utils::double_to_string(act.at(2))
                           + utils::double_to_string(act.at(3));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_ntr", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        size_t expected = 1;
        size_t actual = z1.get_ntr();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_trgrid", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        std::string expected = "   0.000000e+00";
        std::vector<double> act = z1.get_trgrid();
        std::string actual = utils::double_to_string(act.at(0));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_nmat", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        unsigned short int expected = 2;
        unsigned short int actual = z1.get_nmat();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_nfp", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        // (6 grid points for "d" ) and (10 grid points for "ar")
        std::string expected = "          6         10";
        std::vector<size_t> act = z1.get_nfp();
        std::string actual = utils::int_to_string(act.at(0), ' ', cnst::INT_WIDTH)
                           + utils::int_to_string(act.at(1), ' ', cnst::INT_WIDTH);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_nall", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        // 60 = (6 grid points for "d" ) * (10 grid points for "ar")
        std::string expected = "          4          1         60";
        std::vector<size_t> act = z1.get_nall();
        std::string actual = utils::int_to_string(act.at(0), ' ', cnst::INT_WIDTH)
                           + utils::int_to_string(act.at(1), ' ', cnst::INT_WIDTH)
                           + utils::int_to_string(act.at(2), ' ', cnst::INT_WIDTH);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_ncases", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        size_t expected = 240; // = (nte=4) * (ntr=1) * (nall=60)
        size_t actual = z1.get_ncases();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_fpgrid_d", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        std::string expected("   0.000000e+00   1.000000e+19   1.250000e+19");
        expected += "   1.500000e+19   1.750000e+19   2.000000e+19";
        std::vector<double> act = z1.get_fpgrid()["d"];
        std::string actual = utils::double_to_string(act.at(0))
                           + utils::double_to_string(act.at(1))
                           + utils::double_to_string(act.at(2))
                           + utils::double_to_string(act.at(3))
                           + utils::double_to_string(act.at(4))
                           + utils::double_to_string(act.at(5));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_fpgrid_ar", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        std::string expected("   0.000000e+00   3.000000e+19   3.125000e+19");
        expected += "   3.250000e+19   3.375000e+19   3.500000e+19";
        expected += "   3.625000e+19   3.750000e+19   3.875000e+19";
        expected += "   4.000000e+19";
        std::vector<double> act = z1.get_fpgrid()["ar"];
        std::string actual = utils::double_to_string(act.at(0))
                           + utils::double_to_string(act.at(1))
                           + utils::double_to_string(act.at(2))
                           + utils::double_to_string(act.at(3))
                           + utils::double_to_string(act.at(4))
                           + utils::double_to_string(act.at(5))
                           + utils::double_to_string(act.at(6))
                           + utils::double_to_string(act.at(7))
                           + utils::double_to_string(act.at(8))
                           + utils::double_to_string(act.at(9));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_0eos_0_0_0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        std::string expected = "   0.000000e+00   0.000000e+00          0";
        CellEOS act = z0.get_eos(0, 0, 0);
        std::string actual = utils::double_to_string(act.te)
                           + utils::double_to_string(act.tr)
                           + utils::int_to_string(act.nmat, ' ', cnst::INT_WIDTH);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_1eos_2_0_34", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        std::string expected = "   6.300000e+03   0.000000e+00          2";
        expected += "\nd   1.500000e+19\nar   3.375000e+19";
        CellEOS act = z1.get_eos(2, 0, 34);
        std::string actual = utils::double_to_string(act.te)
                           + utils::double_to_string(act.tr)
                           + utils::int_to_string(act.nmat, ' ', cnst::INT_WIDTH) + "\n"
                           + act.mat.at(0) + utils::double_to_string(act.fp.at(0))
                           + "\n"
                           + act.mat.at(1) + utils::double_to_string(act.fp.at(1));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_cell0eos_0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        std::string expected = "   0.000000e+00   0.000000e+00          0";
        CellEOS act = z0.get_cell_eos(0);
        std::string actual = utils::double_to_string(act.te)
                           + utils::double_to_string(act.tr)
                           + utils::int_to_string(act.nmat, ' ', cnst::INT_WIDTH);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_cell1eos_2_0_154", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <analysis1.inc>
        std::string expected = "   6.300000e+03   0.000000e+00          2";
        expected += "\nd   1.500000e+19\nar   3.375000e+19";
        CellEOS act = z1.get_cell_eos(154);
        std::string actual = utils::double_to_string(act.te)
                           + utils::double_to_string(act.tr)
                           + utils::int_to_string(act.nmat, ' ', cnst::INT_WIDTH) + "\n"
                           + act.mat.at(0) + utils::double_to_string(act.fp.at(0))
                           + "\n"
                           + act.mat.at(1) + utils::double_to_string(act.fp.at(1));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Cell.cpp
