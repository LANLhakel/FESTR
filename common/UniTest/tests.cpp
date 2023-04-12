/*=============================================================================

tests.cpp
Driver for unit tests.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 30 October 2018
Last modified on 11 April 2023

Copyright (c) 2018, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

=============================================================================*/

#include <Test.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

//-----------------------------------------------------------------------------

#include <tests_headers.inc>

//-----------------------------------------------------------------------------

const std::string MAIN_NAME = "./tests";

//-----------------------------------------------------------------------------

std::string trim_char(std::string str, const char c)
{
    std::string::size_type pos = str.find_last_not_of(c);

    if (pos != std::string::npos)
    {
        str.erase(pos + 1);
        pos = str.find_first_not_of(c);
        if (pos != std::string::npos) str.erase(0, pos);
    }
    else
        str.erase(str.begin(), str.end());

    return str;
}

//-----------------------------------------------------------------------------

std::string trim(std::string str) {return trim_char(str, ' ');}

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
    std::ifstream disabled_infile("UniTest/disabled_tests.txt");
    if (!disabled_infile.is_open())
    {
        std::cout << "Error opening file: UniTest/disabled_tests.txt" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    while (!disabled_infile.eof())
    {
        getline(disabled_infile, str);
        str = trim(str);
        if (str == "fast" || str == "slow")
            Test::set_disabled_speed(str);
        else
            Test::disabled_tests_insert(str);
    }
    disabled_infile.close();

    // run tests
#include <tests_runs.inc>

    // print test statistics
    std::cout << "\n";
    if (Test::tests_were_run())
    {
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
