/*=============================================================================

time_hist.cpp
Computes a time history of signal intensity within a given photon-energy band.

Usage: ./time_hist <file_name> <hvmin> <hvmax>
Input:  times.txt, <file_name>_time*.txt, <dname->hv_grid.txt
Output: <file_name>_<hvmin>_<hvmax>.dat

Note:
The code looks for the first hyphen in the <file_name> in order to extract
the FESTR Detector <dname>. The X values are picked up from the file called
<dname>-hv_grid.txt. Spectra from all <file_name>_time*.txt files are
integrated within the photon-energy band specified as command-line
arguments; results are written to <file_name>_<band>.dat as the Y-axis,
with the X-axis data provides by input file times.txt.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 25 March 2016
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

const std::string main_name = "./time_hist <file_name_root> <hvmin> <hvmax>";

//-----------------------------------------------------------------------------

void print_usage()
{
    std::cout << "Usage: " << main_name << std::endl;
}

//-----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }

    std::ifstream intimes("times.txt");
    if (!intimes.is_open())
    {
        std::cerr << "Error: file times.txt is not open." << std::endl;
        exit(EXIT_FAILURE);
    }
    utils::find_word(intimes, "start");
    size_t nt;
    intimes >> nt;
    int nd = utils::ndigits(nt);
    size_t ntm1 = nt - 1;
    std::vector<double> times;
    times.reserve(ntm1);
    size_t ii;
    double t;
    for (size_t it = 0; it < ntm1; ++it) // the last time instant has nothing
    {
        intimes >> ii >> t;
        if (ii != it)
        {
            std::cerr << "Error: time index mismatch: " << ii << " " << it
                      << " " << t << std::endl;
            exit(EXIT_FAILURE);
        }
        times.push_back(t);
    }
    intimes.close();
    intimes.clear();

    std::string froot(argv[1]);
    size_t k(froot.find_first_of("-"));
    bool detector(k != std::string::npos);
    std::string dname;
    if (detector) dname = froot.substr(0, k);

    std::string fgrid;
    if (detector)
        fgrid = dname + "-hv_grid.txt";
    else
    {
        std::cerr << "Error: hyphen to extract Detector name not found."
                  << std::endl;
        exit(EXIT_FAILURE);
    }
    std::ifstream hv_grid(fgrid.c_str());
    if (!hv_grid.is_open())
    {
        std::cerr << "Error: file " << fgrid << " is not open." << std::endl;
        exit(EXIT_FAILURE);
    }
    utils::find_line(hv_grid, "Number of grid points:");
    size_t nhv;
    hv_grid >> nhv;

    utils::find_line(hv_grid, "Grid points:");
    size_t ihv, j;
    double x;
    std::vector<double> hv;
    hv.reserve(nhv);
    for (ihv = 0; ihv < nhv; ++ihv)
    {
        hv_grid >> j >> x;
        if (j != ihv)
        {
            std::cerr << "Error: photon-energy index mismatch: " << j
                      << " " << ihv << " " << t << std::endl;
            exit(EXIT_FAILURE);
        }
        hv.push_back(x);
    }
    hv_grid.close();
    hv_grid.clear();

    double hvmin = atof(argv[2]); // lower end of the photon energy band
    double hvmax = atof(argv[3]); // upper end of the photon energy band
    std::string hvmin_str(argv[2]);
    std::string hvmax_str(argv[3]);

    // find integer labels jmin, jmax corresponding to hvmin, hvmax
    size_t i = nhv / 2;
    size_t jmin = utils::nearest(hvmin, hv, nhv-1, i);
    size_t jmax = utils::nearest(hvmax, hv, nhv-1, i);
    size_t nj = jmax - jmin + 1;
    std::vector<double> yint;
    yint.assign(nj, 0.0);

    std::string fname_out(froot + "_" + hvmin_str + "_" + hvmax_str + ".dat");
    std::ofstream outfile(fname_out.c_str());
    if (!outfile.is_open())
    {
        std::cerr << "Error: file " << fname_out << " is not open."
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<double> y;
    y.assign(nhv, 0.0);
    double yin, yout;
    for (size_t it = 0; it < ntm1; ++it) // main time loop
    {
        std::string time_str("_time" + utils::int_to_string(it, '0', nd));
        std::string fname_in(froot + time_str + ".txt");
        std::ifstream infile(fname_in.c_str());
        if (!infile.is_open())
        {
            std::cerr << "Error: file " << fname_in << " is not open."
                      << std::endl;
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
        size_t found = units.find("/eV");
        if (found == std::string::npos)
        {
            std::cerr << "Error: unit /eV not found." << std::endl;
            exit(EXIT_FAILURE);
        }
        units.erase(found, 3);
        if (it == 0) outfile << "# time in s\n# data in " << units
                             << std::endl;

        for (ihv = 0; ihv < nhv; ++ihv) // read current spectrum
        {
            infile >> yin;
            y.at(ihv) = yin;
        }
        infile.close();
        infile.clear();

        yout = utils::integrate_trapezoid(hvmin, hvmax, hv, y, nhv);
        outfile << utils::double_to_string(times.at(it)) << " "
                << utils::double_to_string(yout) << std::endl;
    } // end main time loop
    outfile.close();
    outfile.clear();

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
