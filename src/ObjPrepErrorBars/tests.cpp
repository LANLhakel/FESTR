/*=============================================================================

tests.cpp
Driver for unit, integration, and regression tests.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 23 October 2014
Last modified on 28 March 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.9 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

#include <Test.h>
#include <utils.h>

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cmath>

//-----------------------------------------------------------------------------

void test_ArrSection(int &, int &);

//-----------------------------------------------------------------------------

const std::string MAIN_NAME = "./tests";

//-----------------------------------------------------------------------------

void print_usage()
{
    std::cout << "Usage: " << MAIN_NAME << "\n"
              << "       " << MAIN_NAME << " <test_group (default=all)>\n"
              << "       " << MAIN_NAME
              << " <test_group (default=all)> verbose/silent\n"
              << "       " << MAIN_NAME << " only <test_full_name>"
              << std::endl;
}

//-----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    int failed_test_count = 0;
    int disabled_test_count = 0;

    // process command-line arguments
    std::string str = "";
    std::string stt = "";
    switch (argc)
    {
        case 1:
            Test::set_requested("all");
            Test::set_verbose(false);
            break;

        case 2:
            Test::set_requested(std::string(argv[1]));
            Test::set_verbose(false);
            break;

        case 3:
            str = std::string(argv[1]);
            Test::set_requested(str);
            stt = std::string(argv[2]);
            if (str == "only")
            {
                Test::set_only_test(stt);
                Test::set_verbose(true);
            }
            else
                Test::set_verbose(stt == "verbose");
            break;

        default:
            print_usage();
            std::exit(EXIT_FAILURE);
    }

    if (Test::get_requested() == "only")
        std::cout << "Running: " << MAIN_NAME << " only "
                  << Test::get_only_test() << " (verbose)";
    else
    {
        std::cout << "Running: " << MAIN_NAME << " " << Test::get_requested();
        if (Test::get_verbose())
            std::cout << " verbose";
        else
            std::cout << " silent";
    }
    std::cout << std::endl;

    // read in disabled tests
    std::ifstream disabled_infile("../UniTest/disabled_tests.txt");
    while (!disabled_infile.eof())
    {
        getline(disabled_infile, str);
        str = utils::trim(str);
        if (str == "fast" || str == "slow")
            Test::set_disabled_speed(str);
        else
            Test::disabled_tests_insert(str);
    }
    disabled_infile.close();

    // run tests
    test_ArrSection(failed_test_count, disabled_test_count);

    // print test statistics
    std::cout << "\n";
    if (Test::tests_were_run())
    {
        std::cout << Test::get_requested() << " tests run: "
                  << Test::get_run_test_count() << std::endl;
        if (failed_test_count != 0)
                std::cout << failed_test_count << " of "
                          << Test::get_requested()
                          << " tests FAIL" << std::endl;
        else
            if (Test::get_run_test_count() > 0)
                std::cout << Test::get_requested()
                          << " tests PASS" << std::endl;

        if (disabled_test_count != 0)
        {
            if (disabled_test_count == 1)
                std::cout << "There was 1 disabled test.";
            else
                std::cout << "There were " << disabled_test_count
                          << " disabled tests.";
            std::cout << std::endl;
        }

        if (Test::get_disabled_speed() != "")
            std::cout << Test::get_disabled_speed()
                      << " tests were disabled." << std::endl;
    }
    else
    {
        std::cout << "There are no " << Test::get_requested()
                  << " tests to be run. Check <test_group> "
                  << "command-line argument." << std::endl;
        print_usage();
    }

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
