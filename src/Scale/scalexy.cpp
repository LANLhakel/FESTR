/*=============================================================================

scalexy.cpp
Takes data from <file_name>, scales ordinates and shifts abscissas according to
scale.txt and creates scaled_<file_name> in which these scaled ordinates were
projected onto hv_grid.txt

Usage: ./scalexy <file_name>
Input:  <file_name>, hv_grid.txt, scale.txt
Output: scaled_<file_name>

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 15 October 2015
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

const std::string main_name = "./scalexy <file_name>";

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

    std::ifstream hv_grid("hv_grid.txt");
    if (!hv_grid.is_open())
    {
        std::cerr << "Error: file hv_grid.txt is not open." << std::endl;
        exit(EXIT_FAILURE);
    }
    utils::find_line(hv_grid, "Number of grid points:");
    size_t nhv;
    hv_grid >> nhv;
    std::cout << "\nhv_grid.txt\nnew nhv   = " << nhv << std::endl;
    utils::find_line(hv_grid, "Grid points:");
    std::vector<double> hv(nhv);
    size_t i;
    for (size_t ihv = 0; ihv < nhv; ++ihv)
    {
        hv_grid >> i >> hv.at(ihv);
        if (ihv == 0) std::cout << "new hvmin = "
                                << hv.at(ihv) << std::endl;
        if (ihv == nhv-1) std::cout << "new hvmax = "
                                    << hv.at(ihv) << std::endl;
    }
    hv_grid.close();
    hv_grid.clear();

    std::ifstream scale("scale.txt");
    if (!scale.is_open())
    {
        std::cerr << "\nError: file scale.txt is not open." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string lname;
    getline(scale, lname);
    std::cout << "\nscale.txt" << std::endl;
    double pold, pnew, sc;
    std::vector<double> hvold, hvnew, scint;
    size_t nlines = 0;
    while (scale >> lname >> pold >> pnew >> sc)
    {
        std::cout << lname << " " << pold << " " << pnew << " "
                  << sc << std::endl;
        hvold.push_back(pold);
        hvnew.push_back(pnew);
        scint.push_back(sc);
        ++nlines;
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
    size_t nold = 0;
    const double SMALL = 1.0e-99;
    while (infile >> pold >> pnew)
    {
        xold.push_back(pold);
        if (pnew < SMALL) pnew = SMALL;
        yold.push_back(pnew);
        ++nold;
    }
    infile.close();
    infile.clear();

    std::vector<double> ynew(nhv);
    utils::rescale(hvold, scint, hvnew, nlines,
                   xold, yold, nold, "lin", "log", hv, ynew, nhv);

    std::string fname_out("scaled_" + fname_in);
    std::ofstream outfile(fname_out.c_str());
    if (!outfile.is_open())
    {
        std::cerr << "Error: file " << fname_out
                  << " is not open." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (size_t ihv = 0; ihv < nhv; ++ihv)
    {
        outfile << utils::double_to_string(hv.at(ihv)) << " "
                << utils::double_to_string(ynew.at(ihv)) << std::endl;
    }
    outfile.close();
    outfile.clear();

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
