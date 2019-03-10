/*=============================================================================

objprep_plot.cpp
Takes data from <file_name>, adds weights to each photon energy point
according to ranges.txt and creates obj_<file_name> in which these weights
were added as the third column and obj_plot_<file_name> in which the third
column has the error bars (which are set to 0, if its weight is 0).

Usage: ./objprep_plot <file_name> <half_width>
Input:  <file_name>, ranges.txt
Output: obj_<file_name>, obj_plot_<file_name>

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 25 October 2015
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
#include "ArrSection.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <utility>

typedef std::pair<double, double> DblPair;

const std::string main_name = "./objprep_plot <file_name> <half_width>";

//-----------------------------------------------------------------------------

void print_usage()
{
    std::cout << "Usage: " << main_name << std::endl;
}

//-----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }

    int nw, m;
    nw = atoi(argv[2]);
    if (nw < 2)
    {
        std::cerr << "Error: Savitzky-Golay window half-width must be "
                  << "an integer greater than 1: nw = " << nw << std::endl;
        exit(EXIT_FAILURE);
    }
    m = 2*nw + 1;
    std::cout << "Savitzky-Golay window half-width: " << nw << std::endl;
    std::cout << "Number of Savitzky-Golay points:  " << m << std::endl;
    ArrSection c(-nw, nw, true);
    for (int i = -nw; i <= nw; ++i)
    {
        c[i] = ((3*m*m - 7 - 20*i*i)/4.0) / (m*(m*m - 4)/3.0);
        if (i >= 0) std::cout << i << "  " << c[i] << std::endl;
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

    ArrSection ywrk(0, nold-1, false), ynew(0, nold-1, false);
    for (int i = 0; i < nold; ++i) ywrk[i] = yold[i];
    
    std::string fname_out("obj_" + fname_in);
    std::ofstream outfile(fname_out.c_str());
    if (!outfile.is_open())
    {
        std::cerr << "Error: file " << fname_out
                  << " is not open." << std::endl;
        exit(EXIT_FAILURE);
    }
    outfile << "oname ObjectiveName\ndata in arbitrary_units" << std::endl;

    std::string fname_plot("obj_plot_" + fname_in);
    std::ofstream outfile_plot(fname_plot.c_str());
    if (!outfile_plot.is_open())
    {
        std::cerr << "Error: file " << fname_plot
                  << " is not open." << std::endl;
        exit(EXIT_FAILURE);
    }
    outfile_plot << "#  x               y               "
                 << "error(y)" << std::endl;


    // calculate smoothed spectrum ynew from ywrk, residuals ewrk/enew
    ArrSection ewrk(0, nold-1, false), enew(0, nold-1, false);
    for (int ihv = 0; ihv < nold; ++ihv)
    {
        for (int i = -nw; i <= nw; ++i) ynew[ihv] += c(i) * ywrk(ihv+i);
        ewrk[ihv] = fabs( ynew(ihv) - ywrk(ihv) );
    }
    for (int ihv = 0; ihv < nold; ++ihv)
        for (int i = -nw; i <= nw; ++i) enew[ihv] += c(i) * ewrk(ihv+i);

    double w;
    for (int ihv = 0; ihv < nold; ++ihv)
    {
        if (utils::is_contained_in(xold.at(ihv), intervals))
        {
            enew[ihv] *= 2.0;
            w = 1.0 / pow(enew(ihv), 2);
        }
        else
        {
            enew[ihv] = 0.0;
            w = 0.0;
        }
        outfile << utils::double_to_string(xold.at(ihv)) << " "
                << utils::double_to_string(ynew(ihv)) << " "
                << utils::double_to_string(w) << std::endl;
        outfile_plot << utils::double_to_string(xold.at(ihv)) << " "
                     << utils::double_to_string(ynew(ihv)) << " "
                     << utils::double_to_string(enew(ihv)) << std::endl;
    }
    outfile.close();
    outfile.clear();
    outfile_plot.close();
    outfile_plot.clear();

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
