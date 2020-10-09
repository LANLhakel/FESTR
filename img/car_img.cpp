/*=============================================================================

car_img.cpp
Postprocess spatially resolved spectra to generate a synthetic image file
for a general ("Cartesian", i.e., non-symmetric) case.

Input:
<root_file_name>_ix*_iy*<time>.txt (space-resolved spectra)
<root_file_name>_hv_grid.txt (photon-energy grid)

Output:
<root_file_name><time>_img.dat (2-D image data file in gnuplot's splot format)

Example using the outputs of the unit test suite in ../src/Test/Output/:
./car_img Sphere1d-yp 5 5 300 900 y/n 0

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 26 July 2017
Last modified on 9 October 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.8 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

#include <utils.h>

#include <iostream>
#include <cstdlib>
#include <string>
#include <numeric>
#include <cmath>

const std::string main_name = "./car_img";

//-----------------------------------------------------------------------------

void print_usage()
{
    std::cout << "Usage: " << main_name << " <root_file_name> <nx> <ny> "
              << "<hv_min (eV)> <hv_max (eV)> y/n <time/none>" << std::endl;
}

//-----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    print_usage();
    if (argc != 8)
    {
        std::cerr << "Error: incorrect number of arguments" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string froot(argv[1]);   // Detector etc. root file name
    size_t nx = atoi(argv[2]);    // Number of data points along the x-axis
    size_t ny = atoi(argv[3]);    // Number of data points along the y-axis
    double hvmin = atof(argv[4]); // lower end of the photon energy band
    double hvmax = atof(argv[5]); // upper end of the photon energy band
    std::cout << "Running: " << main_name << " " << froot
              << " " << nx << " " << ny << " " << hvmin << " " << hvmax << " "
              << argv[6] << " " << argv[7] << std::endl;
    std::string time_str(argv[7]);
    if (time_str == "none")
        time_str = "";
    else
        time_str = "_time" + time_str;

    // extract Detector name (dname): substring of froot before the first -
    std::string dname(froot.substr(0, froot.find_first_of("-")));

    // read photon-energy grid
    std::string fgrid(dname + "-hv_grid.txt");
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
        hv.push_back(x);
    }
    hv_grid.close();
    hv_grid.clear();
    double dhv = hv.at(1) - hv.at(0); // assuming uniform linear grid

    // find integer labels jmin, jmax corresponding to hvmin, hvmax
    size_t i = nhv / 2;
    size_t jmin = utils::nearest(hvmin, hv, nhv, i);
    size_t jmax = utils::nearest(hvmax, hv, nhv, i);
    size_t nj = jmax - jmin + 1;

    // read and integrate space-resolved spectra, and write to image file
    int ndx = utils::ndigits(nx);
    int ndy = utils::ndigits(ny);
    std::vector<double> a;
    a.assign(nj, 0.0); // spectrum for the selected band
    size_t m;
    double y;
    std::string fname;
    fname = froot + time_str + "_img.dat";
    std::ofstream outfile(fname.c_str());
    if (std::string(argv[6]) == "y")
        outfile << nx << "\n" << ny << "\n" << std::endl;
    for (size_t iy = 0; iy < ny; ++iy)
    {
        std::string ystr(utils::int_to_string(iy, '0', ndy));
        for (size_t ix = 0; ix < nx; ++ix)
        {
            std::string xstr(utils::int_to_string(ix, '0', ndx));
            fname = froot + "_ix" + xstr + "_iy" + ystr + time_str + ".txt";
            std::ifstream srs(fname.c_str());
            utils::find_word(srs, "ix");
            srs >> m >> x;
            utils::find_word(srs, "iy");
            srs >> m >> y;
            srs.close();
            srs.clear();
            utils::load_array(fname, nhv, jmin, jmax, a);

            // integrate "a" using trapezoidal rule
            double s(accumulate(a.begin()+1, a.end()-1, (a[0]+a[nj-1])/2.0));
            s *= dhv;
            outfile << x << "  " << y << "  " << s << std::endl;
        }
        outfile << std::endl;
    }
    outfile.close();
    outfile.clear();

    std::cout << "\nend" << std::endl;
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------

// end car_img.cpp
