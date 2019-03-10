/*=============================================================================

plotxy.cpp
Combines computed Y-data with X-data from file hv_grid.txt (Database) or
<dname>-hv_grid.txt (Detector) for plotting.

Usage: ./plotxy <file_name>
Input:  <file_name>.txt, <dname->hv_grid.txt
Output: <file_name>.dat

Note:
The code looks for the first hyphen in the <file_name>. If one is found, then
the spectrum came from a FESTR Detector <dname> and so the X values are picked
up from the file called <dname>-hv_grid.txt. If a hyphen is not found in
<file_name>, the spectrum is a raw database file and file hv_grid.txt must be
present in the same (working) directory to provide the X values.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 3 March 2015
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

#include "../src/utilities.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

const std::string main_name = "./plotxy <file_name_root>";

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

    std::string froot(argv[1]);
    size_t k(froot.find_first_of("-"));
    bool detector(k != std::string::npos);
    std::string dname;
    if (detector) dname = froot.substr(0, k);
    std::string fname_in(froot + ".txt");
    std::string fname_out(froot + ".dat");
    std::ifstream infile(fname_in.c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: file " << fname_in << " is not open." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string fgrid;
    if (detector)
        fgrid = dname + "-hv_grid.txt";
    else // e.g., a Database table file
        fgrid = "hv_grid.txt";
    std::ifstream hv_grid(fgrid.c_str());
    if (!hv_grid.is_open())
    {
        std::cerr << "Error: file " << fgrid << " is not open." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ofstream outfile(fname_out.c_str());
    if (!outfile.is_open())
    {
        std::cerr << "Error: file " << fname_out << " is not open." << std::endl;
        exit(EXIT_FAILURE);
    }

    utils::find_word(infile, "data");
    std::string s, units;
    while (true)
    {
        infile >> s;
        if (s == "in") break;
    }
    infile >> units;
    outfile << "# hv in eV\n# data in " << units << std::endl;

    utils::find_line(hv_grid, "Number of grid points:");
    size_t nhv;
    hv_grid >> nhv;

    utils::find_line(hv_grid, "Grid points:");
    size_t ihv, j;
    double x, y;
    for (ihv = 0; ihv < nhv; ++ihv)
    {
        hv_grid >> j >> x;
        infile >> y;
        outfile << utils::double_to_string(x) << " "
                << utils::double_to_string(y) << std::endl;
    }
    hv_grid.close();
    hv_grid.clear();
    infile.close();
    infile.clear();
    outfile.close();
    outfile.clear();

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
