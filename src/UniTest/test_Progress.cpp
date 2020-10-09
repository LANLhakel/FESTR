/*=============================================================================

test_Progress.cpp
Definitions for unit, integration, and regression tests for class Progress.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 8 August 2015
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

#include <test_Progress.h>
#include <Test.h>

#include <utils.h>

#include <cstdlib>
#include <fstream>

void test_Progress(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Progress";

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_get_level", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Progress counter;
        int expected(0);
        int actual = counter.get_level();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_level", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Progress counter("name", 2, 100, 0, "", std::cout);
        int expected(2);
        int actual = counter.get_level();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "default_to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Progress counter;
        std::string expected("Progress: empty\nlevel: 0\nn: 0\nfreq: 0");
        std::string actual = counter.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Progress counter("name", 2, 100, 0, "", std::cout);
        std::string expected("Progress: name\nlevel: 2\nn: 100\nfreq: 0");
        std::string actual = counter.to_string();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "silent", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const int nlevel = 1;
        const size_t n = 10, freq = 0;
        const size_t ncount = n;
        std::string name("Progress_silent");
        #include <progress.inc>
        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "commensurable_n_freq", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const int nlevel = 2;
        const size_t n = 10, freq = 5;
        const size_t ncount = n;
        std::string name("Progress_comm");
        #include <progress.inc>
        expected += label + " 0 of 10,   0%\n";
        expected += label + " 5 of 10,  50%\n";
        expected += label + "10 of 10, 100%";

        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "not_commensurable_n_freq", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const int nlevel = 4;
        const size_t n = 10, freq = 3;
        const size_t ncount = n;
        std::string name("Progress_not_comm");
        #include <progress.inc>
        expected += label + " 0 of 10,   0%\n";
        expected += label + " 3 of 10,  30%\n";
        expected += label + " 6 of 10,  60%\n";
        expected += label + " 9 of 10,  90%\n";
        expected += label + "10 of 10, 100%";

        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "n1_freq1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const int nlevel = 2;
        const size_t n = 1, freq = 1;
        const size_t ncount = n;
        std::string name("Progress_n1_freq1");
        #include <progress.inc>
        expected += label + "0 of 1,   0%\n";
        expected += label + "1 of 1, 100%";

        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "n2_freq1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const int nlevel = 1;
        const size_t n = 2, freq = 1;
        const size_t ncount = n;
        std::string name("Progress_n2_freq1");
        #include <progress.inc>
        expected += label + "0 of 2,   0%\n";
        expected += label + "1 of 2,  50%\n";
        expected += label + "2 of 2, 100%";

        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "unknown_total_count", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const int nlevel = 0;
        const size_t n = 0, freq = 2;
        const size_t ncount = 11;
        std::string name("Progress_unknown_total_count");
        #include <progress.inc>
        expected += label + "0 of ?\n";
        expected += label + "2 of ?\n";
        expected += label + "4 of ?\n";
        expected += label + "6 of ?\n";
        expected += label + "8 of ?\n";
        expected += label + "10 of ?\n";
        expected += label + "11 of ?\n";
        expected += label + "? = 11";

        std::string actual(utils::file_to_string(fname));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 5;
        const size_t freq = 2;
        #include <freq.inc>
        (void)(freq_next);
        ostr.close();
        ostr.clear();

        size_t expected = 2;
        size_t actual = counter.get_freq();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq20", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 5;
        const size_t freq = 2;
        #include <freq.inc>
        ostr.close();
        ostr.clear();

        size_t expected = 0; // = will not print (#1 in progress, 1%freq != 0)
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq21", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 5;
        const size_t freq = 2;
        #include <freq.inc>
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 3; // = freq_next, will print (#2 in progress)
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq22", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 5;
        const size_t freq = 2;
        #include <freq.inc>
        counter.advance();
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 0; // = will not print (#3 in progress, 3%freq != 0)
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq23", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 5;
        const size_t freq = 2;
        #include <freq.inc>
        counter.advance();
        counter.advance();
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 3; // = freq_next, will print (#4 in progress)
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq24", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 5;
        const size_t freq = 2;
        #include <freq.inc>
        counter.advance();
        counter.advance();
        counter.advance();
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 0; // = will not print (#5 in progress, 5%freq != 0)
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq00", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 5;
        const size_t freq = 0;
        #include <freq.inc>
        ostr.close();
        ostr.clear();

        size_t expected = 0;
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq01", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 5;
        const size_t freq = 0;
        #include <freq.inc>
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 0;
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq02", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 5;
        const size_t freq = 0;
        #include <freq.inc>
        counter.advance();
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 0;
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq03", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 5;
        const size_t freq = 0;
        #include <freq.inc>
        counter.advance();
        counter.advance();
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 0;
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq04", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 5;
        const size_t freq = 0;
        #include <freq.inc>
        counter.advance();
        counter.advance();
        counter.advance();
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 0;
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 0;
        const size_t freq = 2;
        #include <freq.inc>
        ostr.close();
        ostr.clear();

        size_t expected = 0; // = will not print (#1 in progress, 1%freq != 0)
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 0;
        const size_t freq = 2;
        #include <freq.inc>
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 3; // = freq_next, will print (#2 in progress)
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 0;
        const size_t freq = 2;
        #include <freq.inc>
        counter.advance();
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 0; // = will not print (#3 in progress, 3%freq != 0)
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq3", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 0;
        const size_t freq = 2;
        #include <freq.inc>
        counter.advance();
        counter.advance();
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 3; // = freq_next, will print (#4 in progress)
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "get_freq4", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        const size_t n = 0;
        const size_t freq = 2;
        #include <freq.inc>
        counter.advance();
        counter.advance();
        counter.advance();
        counter.advance();
        ostr.close();
        ostr.clear();

        size_t expected = 0; // = will not print (#5 in progress, 5%freq != 0)
        size_t actual = counter.get_next_freq(freq_next);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Progress.cpp
