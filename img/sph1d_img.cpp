/*=============================================================================

sph1d_img.cpp
Postprocess spatially resolved spectra to generate a synthetic image file
for a spherically symmetric case.

Input:
<root_file_name>_ix*_iy0<time>.txt (space-resolved spectra)
<root_file_name>_hv_grid.txt (photon-energy grid)

Output:
<root_file_name><time>_img.dat (2-D image data file in gnuplot's splot format)

Example using the outputs of the unit test suite in ../src/Test/Output/:
./sph1d_img SphSym1d-yt 0.5 0.001 300 900 y/n none

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 30 March 2015
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

#include "../src/src/utilities.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <numeric>
#include <cmath>

const std::string main_name = "./sph1d_img";

//-----------------------------------------------------------------------------

void print_usage()
{
    std::cout << "Usage: " << main_name << " <root_file_name> "
              << "<radius (cm)> <spacing (cm)> "
              << "<hv_min (eV)> <hv_max (eV)> y/n <time/none>" << std::endl;
}

//-----------------------------------------------------------------------------

double get_yv(const double xx, const double yy, const double vmax,
              const size_t n,
              const std::vector<double> &v, const std::vector<double> &y,
              size_t &i)
{
    double yv;
    size_t j;
    double r = sqrt(xx*xx + yy*yy);
    if (r >= vmax)
    {
        i = n - 1;
        j = i - 1;
        yv = 0.0;
    }
    else
    {
        j = utils::nearest(r, v, n, i);
        if (j == n-1)
            yv = 0.0;
        else
            yv = y.at(j)
               + (r-v.at(j)) * (y.at(j+1)-y.at(j)) / (v.at(j+1)-v.at(j));
    }
    return yv;
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
    double r = atof(argv[2]);     // radius (cm)
    double d = atof(argv[3]);     // Ray spacing (cm): may be adjusted
    double hvmin = atof(argv[4]); // lower end of the photon energy band
    double hvmax = atof(argv[5]); // upper end of the photon energy band
    std::cout << "Running: " << main_name << " " << froot
              << " " << r << " " << d << " " << hvmin << " " << hvmax << " "
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

    // set patch discretization (taken from FESTR's class Detector constructor)
    size_t n = static_cast<size_t>(utils::nint(2.0*r/d));
    n /= 2;
    if (n % 2 == 0) ++n; // this modified n is always odd
    d = r / (static_cast<double>(n) - 0.5); // Eq.(1)
    int nd = utils::ndigits(n);

    // load space-resolved spectra and integrate across the selected band
    std::vector<double> a, v, y;
    a.assign(nj, 0.0); // spectrum for the selected band
    v.reserve(n);      // position coordinates (cm)
    y.reserve(n);      // integrated intensity across the band at location "v"
    std::string fname; // file name for the space-resolved spectrum at "v"
    for (j = 0; j < n; ++j)
    {
        std::string xstr(utils::int_to_string(j, '0', nd));
        fname = froot + "_ix" + xstr + "_iy0" + time_str + ".txt";
        utils::load_array(fname, nhv, jmin, jmax, a);

        // integrate "a" using trapezoidal rule
        double s(accumulate(a.begin()+1, a.end()-1, (a[0]+a[nj-1])/2.0));
        y.push_back(s * dhv);
        v.push_back(j * d);
    }
    double vmax = (n - 1) * d;

    // write image data file (rotate "a" content into a circular disk)
    fname = froot + time_str + "_img.dat";
    std::ofstream outfile(fname.c_str());
    double xx, yy, yv;
    size_t ix, iy;
    i = n - 1;
    if (std::string(argv[6]) == "y") outfile << 2*n-1 << std::endl << std::endl;
    for (iy = n-1; iy > 0; --iy)
    {
        yy = - (iy * d);
        for (ix = n - 1; ix > 0; --ix)
        {
            xx = - (ix * d);
            yv = get_yv(xx, yy, vmax, n, v, y, i);
            outfile << xx << "  " << yy << "  " << yv << std::endl;
        }
        for (ix = 0; ix < n; ++ix)
        {
            xx = ix * d;
            yv = get_yv(xx, yy, vmax, n, v, y, i);
            outfile << xx << "  " << yy << "  " << yv << std::endl;
        }
        outfile << std::endl;
    }
    for (iy = 0; iy < n; ++iy)
    {
        yy = iy * d;
        for (ix = n - 1; ix > 0; --ix)
        {
            xx = - (ix * d);
            yv = get_yv(xx, yy, vmax, n, v, y, i);
            outfile << xx << "  " << yy << "  " << yv << std::endl;
        }
        for (ix = 0; ix < n; ++ix)
        {
            xx = ix * d;
            yv = get_yv(xx, yy, vmax, n, v, y, i);
            outfile << xx << "  " << yy << "  " << yv << std::endl;
        }
        outfile << std::endl;
    }
    outfile.close();
    outfile.clear();

    std::cout << "\nend" << std::endl;
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------

// end sph1d_img.cpp
