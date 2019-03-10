/*=============================================================================

test_Goal.cpp
Definitions for unit, integration, and regression tests for class Goal.

pmh_2015_0210
pmh_2015_0312

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 28 June 2015
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
#include "../src/Goal.h"
#include "../src/ArrDbl.h"
#include "../src/constants.h"

#include <stdexcept>

void test_Goal(int &failed_test_count, int &disabled_test_count)
{

const std::string GROUP = "Goal";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol;
        size_t expected(0);
        size_t actual = gol.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "analysis0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol;
        bool expected(false);
        bool actual = gol.get_analysis();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_analysis_true", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol;
        gol.set_analysis(true);
        bool expected(true);
        bool actual = gol.get_analysis();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_best_scale", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol;
        double expected(1.0);
        double actual = gol.get_best_scale("non_existent_name");

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_analysis_false", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        gol.set_analysis(false);
        bool expected(false);
        bool actual = gol.get_analysis();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        size_t expected(4);
        size_t actual = gol.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "analysis", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        bool expected(true);
        bool actual = gol.get_analysis();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size_none", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(false, cnst::PATH + "UniTest/Goal1/");
        size_t expected(0);
        size_t actual = gol.size();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "analysis_none", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(false, cnst::PATH + "UniTest/Goal1/");
        bool expected(false);
        bool actual = gol.get_analysis();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        std::string s("Number of Objectives           4");
        s += "\nObjective_Name weight x_is_present w_is_present";
        s += "\nObjectiveNameXYW    2.000000e+00 true true";
        s += "\nObjectiveNameYW    3.000000e+00 false true";
        s += "\nObjectiveNameXY    4.000000e+00 true false";
        s += "\nObjectiveNameY    5.000000e+00 false false";
        std::string expected(s);
        std::string actual = gol.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "initial_fitness", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        std::string expected(" -1.000000e+300");
        double act = gol.get_fitness_at(0);
        std::string actual(utils::double_to_string(act));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_name", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        std::string expected("ObjectiveNameXY");
        std::string actual = gol.get_name(2);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_index", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        size_t expected(2);
        size_t actual = gol.get_index("ObjectiveNameXY");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_index_nonexistent", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        size_t expected(4);
        size_t actual = gol.get_index("nonexistent");

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_weight", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        double expected(2.0);
        double actual = gol.get_objective(0)->get_weight();

        failed_test_count += t.check_equal_real_num(expected, actual, EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fit_eval0", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        ArrDbl a(2);
        a.fill(0.0);
        gol.fit_eval("ObjectiveNameXYW", a);
        double expected(-41.0);
        double actual = gol.get_fitness_at(0);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fit_eval1", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        ArrDbl a(2);
        a.fill(1.0);
        gol.fit_eval("ObjectiveNameYW", a);
        double expected(-44.4);
        double actual = gol.get_fitness_at(1);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fit_eval2", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        ArrDbl a(2);
        a.fill(2.0);
        gol.fit_eval("ObjectiveNameXY", a);
        double expected(-388.0);
        double actual = gol.get_fitness_at(2);

        failed_test_count += t.check_equal_real_num(expected, actual, 100*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "fit_eval3", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        ArrDbl a(2);
        a.fill(3.0);
        gol.fit_eval("ObjectiveNameY", a);
        double expected(-80.0);
        double actual = gol.get_fitness_at(3);

        failed_test_count += t.check_equal_real_num(expected, actual, 10*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_fitness", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "goal1.inc"
        double expected(-138.35);
        double actual = gol.get_fitness();

        failed_test_count += t.check_equal_real_num(expected, actual, 100*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_best_fitness", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(false, cnst::PATH + "UniTest/Goal1/");
        std::string expected(" -1.000000e+300");
        double act = gol.get_best_fitness();
        std::string actual(utils::double_to_string(act));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "initial_best_fitness", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        std::string expected(" -1.000000e+300");
        double act = gol.get_best_fitness();
        std::string actual(utils::double_to_string(act));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_best_case", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(false, cnst::PATH + "UniTest/Goal1/");
        size_t expected(0);
        size_t actual(gol.get_best_case());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "initial_best_case", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(true, cnst::PATH + "UniTest/Goal1/");
        size_t expected(0);
        size_t actual(gol.get_best_case());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_best_case", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        Goal gol(false, cnst::PATH + "UniTest/Goal1/");
        gol.set_best_case(11);
        size_t expected(11);
        size_t actual(gol.get_best_case());

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "update_best_fitness_accept", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "goal1.inc"
        double expected(-138.35);
        double actual = gol.get_best_fitness();

        failed_test_count += t.check_equal_real_num(expected, actual, 100*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "update_best_case_accept", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "goal1.inc"
        size_t expected(11);
        size_t actual = gol.get_best_case();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "update_best_fitness_reject", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "poor_guess.inc"
        double expected(-138.35);
        double actual = gol.get_best_fitness();

        failed_test_count += t.check_equal_real_num(expected, actual, 100*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "update_best_case_reject", "fast");

    check_to_disable_test(t, disabled_test_count);
    if (t.is_enabled())
    {
        #include "poor_guess.inc"
        size_t expected(11);
        size_t actual = gol.get_best_case();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

// end test_Goal.cpp
