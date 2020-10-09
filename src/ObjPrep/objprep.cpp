/*=============================================================================

objprep.cpp
Takes data from <file_name>, adds 0 or 1 weights to each photon energy point
according to ranges.txt and creates obj_<file_name> in which these weights
were added as the third column.

Usage: ./objprep <file_name>
Input:  <file_name>, ranges.txt
Output: obj_<file_name>

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 25 October 2015
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

#include <utils.h>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <utility>

typedef std::pair<double, double> DblPair;

const std::string main_name = "./objprep <file_name>";

//-----------------------------------------------------------------------------

void print_usage()
{
    std::cout << "Usage: " << main_name << std::endl;
}

//-----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }

    std::ifstream ranges("ranges.txt");
    if (!ranges.is_open())
    {
        std::cerr << "\nError: file ranges.txt is not open." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string lname;
    getline(ranges, lname);
    getline(ranges, lname);
    std::cout << "\nranges.txt" << std::endl;
    double hvmin, hvmax;
    std::vector<DblPair> intervals;
    size_t nranges = 0;
    while (ranges >> lname >> hvmin >> hvmax)
    {
        std::cout << lname << " " << hvmin << " " << hvmax << std::endl;
        intervals.push_back(std::make_pair(hvmin, hvmax));
        ++nranges;
    }

    std::string fname_in(argv[1]);
    std::ifstream infile(fname_in.c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: file " << fname_in
                  << " is not open." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<double> xold, yold;
    double x, y;
    size_t nold = 0;
    while (infile >> x >> y)
    {
        xold.push_back(x);
        yold.push_back(y);
        ++nold;
    }
    infile.close();
    infile.clear();

    std::string fname_out("obj_" + fname_in);
    std::ofstream outfile(fname_out.c_str());
    if (!outfile.is_open())
    {
        std::cerr << "Error: file " << fname_out
                  << " is not open." << std::endl;
        exit(EXIT_FAILURE);
    }
    outfile << "oname ObjectiveName\ndata in arbitrary_units" << std::endl;

    double w;
    for (size_t ihv = 0; ihv < nold; ++ihv)
    {
        if (utils::is_contained_in(xold.at(ihv), intervals))
            w = 1.0;
        else
            w = 0.0;
        outfile << utils::double_to_string(xold.at(ihv)) << " "
                << utils::double_to_string(yold.at(ihv)) << " "
                << w << std::endl;
    }
    outfile.close();
    outfile.clear();

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
