/*=============================================================================

test_Database.cpp
Definitions for unit, integration, and regression tests for class Database.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 31 December 2014
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

void test_Database(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "Database";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_tops_cmnd", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "none";
        std::string actual = d.get_tops_cmnd();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_path", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = path;
        std::string actual = d.get_path();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
// Electron temperature grid
//-----------------------------------------------------------------------------
{
    Test t(GROUP, "Dbase1_nbits_te", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 6;
        size_t actual = d.get_nbits_te();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_nte", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 64;
        size_t actual = d.get_nte();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_te_double_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 100.0;
        double actual = d.get_te_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_te_string_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "00100";
        std::string actual = d.get_te_str_at(0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_te_double_last", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 6400.0;
        double actual = d.get_te_at(63);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_te_string_last", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "06400";
        std::string actual = d.get_te_str_at(63);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_nearest_te_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "02500";
        size_t i = 3;
        std::string actual = d.nearest_te_str(2455.0, i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_nearest_te_index", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 24;
        size_t i = 3;
        d.nearest_te_str(2455.0, i);
        size_t actual = i;
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
// Radiation temperature grid
//-----------------------------------------------------------------------------
{
    Test t(GROUP, "Dbase1_nbits_tr", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 1;
        size_t actual = d.get_nbits_tr();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_ntr", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 2;
        size_t actual = d.get_ntr();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_tr_double_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 0.0;
        double actual = d.get_tr_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_tr_string_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "00000";
        std::string actual = d.get_tr_str_at(0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_tr_double_last", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 6400.0;
        double actual = d.get_tr_at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_tr_string_last", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "06400";
        std::string actual = d.get_tr_str_at(1);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_nearest_tr_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "06400";
        size_t i = 0;
        std::string actual = d.nearest_tr_str(7000.0, i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_nearest_tr_index", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 1;
        size_t i = 0;
        d.nearest_tr_str(7000.0, i);
        size_t actual = i;
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
// Electron number density grid (mantissa)
//-----------------------------------------------------------------------------
{
    Test t(GROUP, "Dbase1_nbits_neman", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 3;
        size_t actual = d.get_nbits_neman();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_nneman", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 8;
        size_t actual = d.get_nneman();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_neman_double_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 1.0;
        double actual = d.get_neman_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_neman_string_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "1.0";
        std::string actual = d.get_neman_str_at(0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_neman_double_last", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 8.0;
        double actual = d.get_neman_at(7);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_neman_string_last", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "8.0";
        std::string actual = d.get_neman_str_at(7);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
// Electron number density grid (exponent)
//-----------------------------------------------------------------------------
{
    Test t(GROUP, "Dbase1_nbits_neexp", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 2;
        size_t actual = d.get_nbits_neexp();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_nneexp", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 4;
        size_t actual = d.get_nneexp();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_neexp_double_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 17.0;
        double actual = d.get_neexp_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_neexp_string_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "17";
        std::string actual = d.get_neexp_str_at(0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_neexp_double_last", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 20.0;
        double actual = d.get_neexp_at(3);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_neexp_string_last", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "20";
        std::string actual = d.get_neexp_str_at(3);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
// Electron number density grid
//-----------------------------------------------------------------------------
{
    Test t(GROUP, "Dbase1_nbits_ne", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 5;
        size_t actual = d.get_nbits_ne();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_nne", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 32;
        size_t actual = d.get_nne();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_ne_double_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 1.0e17;
        double actual = d.get_ne_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e2);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_ne_string_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "1.0e17";
        std::string actual = d.get_ne_str_at(0);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_ne_double_last", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 8.0e20;
        double actual = d.get_ne_at(31);

        failed_test_count += t.check_equal_real_num(expected, actual, 8.0e9);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_ne_string_last", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected = "8.0e20";
        std::string actual = d.get_ne_str_at(31);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
// Photon energy grid
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_nhv", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        size_t expected = 3;
        size_t actual = d.get_nhv();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_hv_double_first", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 300.0;
        double actual = d.get_hv_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_hv_double_last", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        double expected = 900.0;
        double actual = d.get_hv_at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase1_to_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        std::string path(cnst::PATH + "UniTest/Dbase1/");
        Database d("none", path, false);
        std::string expected("Database path: " + path + "\n");
        expected += "nte:         64\nntr:          2\nnne:         32\n";
        expected += "nhv:          3";
        std::string actual = d.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
// Lookups
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase3_ne_value", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "dbase3.inc"
        double expected = 4.6e16;
        double actual = ne_pair.first;

        failed_test_count += t.check_equal_real_num(expected, actual, 1.0e5);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase3_ne_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "dbase3.inc"
        std::string expected("_te06400ev_tr00000ev_ne5.0e16pcc_");
        std::string actual = ne_pair.second;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Dbase3_ne_index", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "dbase3.inc"
        size_t expected(5);
        size_t actual = ine;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

// end test_Database.cpp
