/*=============================================================================

time_intavg.cpp
Computes a time-integrated spectrum and a time-averaged spectrum for a selected
time interval.

Usage: ./time_intavg <file_name> <tmin> <tmax>
Input:  times.txt, <file_name>_time*.txt, <dname->hv_grid.txt
Output: <file_name>_<tmin>_<tmax>_int.dat, <file_name>_<tmin>_<tmax>_avg.dat

Note:
The code looks for the first hyphen in the <file_name> in order to extract
the FESTR Detector <dname>. The X values are picked up from the file called
<dname>-hv_grid.txt. Spectra from <file_name>_time*.txt files are
integrated within the time interval specified via command-line arguments;
time-integrated spectrum is written to <file_name>_<tmin>_<tmax>_int.dat
time-averaged spectrum is written to <file_name>_<tmin>_<tmax>_avg.dat

To ensure validity of results, the user should choose <tmin> and <tmax> values
that EXACTLY match time instants listed in the times.txt input file, while
also satisfying tmin < tmax.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 19 August 2016 from time_hist.cpp
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

const std::string main_name = "./time_intavg <file_name_root> <tmin> <tmax>";

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
    times.reserve(nt);
    size_t ii;
    double t;
    for (size_t it = 0; it < nt; ++it) // the last time instant has nothing
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

    double tmin = atof(argv[2]); // beginning of the time interval
    double tmax = atof(argv[3]); // end of the time interval
    std::string tmin_str(argv[2]);
    std::string tmax_str(argv[3]);

    // find integer labels jmin, jmax corresponding to tmin, tmax
    size_t i = ntm1 / 2;
    size_t jmin = utils::nearest(tmin, times, ntm1, i);
    size_t jmax = utils::nearest(tmax, times, ntm1, i);
    double deltat = tmax - tmin;

    std::string fname_int;
    fname_int = froot + "_" + tmin_str + "_" + tmax_str + "_int.dat";
    std::ofstream intfile(fname_int.c_str());
    if (!intfile.is_open())
    {
        std::cerr << "Error: file " << fname_int << " is not open."
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string fname_avg;
    fname_avg = froot + "_" + tmin_str + "_" + tmax_str + "_avg.dat";
    std::ofstream avgfile(fname_avg.c_str());
    if (!avgfile.is_open())
    {
        std::cerr << "Error: file " << fname_avg << " is not open."
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<double> y, yprev, yout;
    y.assign(nhv, 0.0);
    yout.assign(nhv, 0.0);
    double yin, tstep;
    for (size_t it = jmin; it <= jmax; ++it) // main time loop
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
        if (it == jmin)
        {
            size_t found = units.find("W"); // Watts
            if (found == std::string::npos)
            {
                std::cerr << "Error: unit W not found." << std::endl;
                exit(EXIT_FAILURE);
            }
            avgfile << "# hv in eV\n# data in "
                    << units << std::endl; // in the average keep Watts
            units.replace(found, 1, "J"); // in the integral use Joules instead
            intfile << "# hv in eV\n# data in "
                    << units << std::endl;
        }

        for (ihv = 0; ihv < nhv; ++ihv) // read current spectrum
        {
            infile >> yin;
            y.at(ihv) = yin;
        }
        infile.close();
        infile.clear();

        if (it > jmin)
        {
            tstep = times.at(it) - times.at(it-1);
            for (ihv = 0; ihv < nhv; ++ihv)
            {
                yout.at(ihv) += tstep * (y.at(ihv) + yprev.at(ihv)) / 2.0;
            }
        }
        yprev = y;
    } // end main time loop

    for (ihv = 0; ihv < nhv; ++ihv)
    {
        intfile << utils::double_to_string(hv.at(ihv)) << " "
                << utils::double_to_string(yout.at(ihv)) << std::endl;
        avgfile << utils::double_to_string(hv.at(ihv)) << " "
                << utils::double_to_string(yout.at(ihv) / deltat) << std::endl;
    }
    intfile.close();
    intfile.clear();
    avgfile.close();
    avgfile.clear();

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
