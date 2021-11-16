/* Prepare 2D cylindrically symmetric FESTR mesh (Faces=>Cones) for plotting

Usage: ./plot2dcyl <time_label> <quantity> [nth=1]
Input files: grid_<time_label>.txt, mesh_<time_label>.txt, time_<time_label>.txt
Output file: <quantity>_<time_label>.dat

Examples (see Notes pmh_2015_0522 and ../UniTest/Hydro4/):
Input files: grid_0.txt, mesh_0.txt, time_0.txt

Example 1: ./plot2dcyl 0 te eV 2
Output file 1: te_0.dat

Example 2: ./plot2dcyl 0 d 1
Output file 2: d_0.dat

Peter Hakel, LANL XCP-5

Created on 18 August 2021
Last modified on 15 November 2021

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

*/

#include <Polygon.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

//-----------------------------------------------------------------------------

template <typename T> // T must be callable as void(const int64_t ibegin, const int64_t iend)
void thread_tasks(T tasks, const int64_t ntasks, const int nthreads)
{
    if (nthreads == 1)
    {
        tasks(0, ntasks);
    }
    else
    {
        std::vector<std::thread> t;
        if (ntasks <= nthreads)
        {
            for (int64_t i = 1; i < ntasks; ++i)
            {
                t.emplace_back(std::thread(tasks, i, i+1));
            }
            tasks(0, 1);
        }
        else
        {
            int64_t blocksize = ntasks / nthreads;
            for (int i = 0; i < nthreads-1; ++i)
            {
                t.emplace_back(std::thread(tasks, i*blocksize, (i+1)*blocksize));
            }
            tasks((nthreads-1)*blocksize, ntasks);
        }
        for (int64_t i = 0; i < t.size(); ++i)
        {
            t[i].join();
        }
    }
}

//-----------------------------------------------------------------------------

/** @brief Name of this code */
const std::string main_name = "plot2dcyl";

//-----------------------------------------------------------------------------

/** @brief Prints the format of the execution command */
void print_usage()
{
    std::cout << "Usage: ./" << main_name  << " <time_label> <quantity> <unit>"
              << " [nth=1]" << std::endl;
}

//-----------------------------------------------------------------------------

class IndexQueue // for threading zone processing
{
  public:
    explicit IndexQueue(const int nin): i(0), n(nin), m() {}

    int next_index()
    {
        std::lock_guard<std::mutex> l(m);
        if (i < n) ++i;
        return i;
    }

  private:
    int i; // current index
    int n; // maximum index + 1
    std::mutex m;
};

//-----------------------------------------------------------------------------

/** @brief Main driver of this code */
int main(int argc, char **argv)
{
    if (argc != 4  &&  argc != 5)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }
    std::cout << "Running: ";
    for (int i = 0; i < argc; ++i) std::cout << " " << argv[i];
    std::cout << "\n" << std::endl;

    std::string path = "./";
    std::string tlabel(argv[1]);
    std::string q(argv[2]);
    std::string u(argv[3]); // u="1" for a dimensionless quantity
    int nth = 1;
    if (argc == 5) nth = atoi(argv[4]);
    Grid g(path, tlabel);
    int grid_size = g.size();
    std::cout << "grid_size: " << grid_size << std::endl;
    double d = 1.0e99; // grid discretization
    double xmin = 0.0;
    double xmax = -1.0e99;
    double ymin = 1.0e99;
    double ymax = -1.0e99;
    for (int i = 0; i < grid_size; ++i)
    {
        Node n = g.get_node(i);
        Vector3d r = n.getr();
        double x = r.getx();
        double y = r.gety();
        double z = r.getz();
        double ax = fabs(x);
        if (ax < 1.0e-12)
        {
            n.setr(Vector3d(0.0, y, z));
        }
        else
        {
            if (ax < d) d = ax;
        }
        if (x < xmin) xmin = x;
        if (x > xmax) xmax = x;
        if (y < ymin) ymin = y;
        if (y > ymax) ymax = y;
    }
    d /= 2;
    std::cout << "xmin: " << xmin << std::endl;
    std::cout << "xmax: " << xmax << std::endl;
    std::cout << "ymin: " << ymin << std::endl;
    std::cout << "ymax: " << ymax << std::endl;
    std::cout << "d: " << d << std::endl;
    std::cout << "\nReenter or change the discretization value d: ";
    std::cin >> d;
    std::cout << "d: " << d << std::endl;
    int64_t nx = utils::nint(xmax/d) + 1;
    int64_t ny = utils::nint((ymax-ymin)/d) + 1;
    std::cout << "nx: " << nx << "\nny: " << ny << std::endl;
    // z0: values
    std::vector<double> z0(nx, 0.0); // horizontal (x) index is 2nd (faster moving)
    std::vector<std::vector<double>> z(ny, z0); // vertical (y) index is 1st
    // p0: paint flags
    std::vector<int> p0(nx, 0.0); // horizontal (x) index is 2nd (faster moving)
    std::vector<std::vector<int>> painted(ny, p0); // vertical (y) index is 1st

    std::string ftime = "./time_" + std::string(argv[1]) + ".txt";
    std::ifstream timef(ftime.c_str());
    utils::find_word(timef, "Zone");

    std::string fmesh = "./mesh_" + std::string(argv[1]) + ".txt";
    std::ifstream mesh(fmesh.c_str());
    utils::find_word(mesh, "Number_of_zones");
    int nzones = 0;
    mesh >> nzones;
    std::cout << "nzones-1: " << nzones-1 << std::endl;
    utils::find_word(mesh, "Zone");
    std::vector<double> v(nzones, 0.0);
    std::vector<Polygon> zones(nzones);
    double vmin = 1.0e99;
    double vmax = -1.0e99;
    for (int i = 1; i < nzones; ++i) // read all zones
    {
        utils::find_word(timef, "Zone");
        utils::find_word(timef, q);
        double val = 0.0;
        timef >> val;
        if (val < vmin) vmin = val;
        if (val > vmax) vmax = val;
        v[i] = val;

        utils::find_word(mesh, "Zone");
        int zoneid, nfaces;
        mesh >> zoneid >> nfaces;
        std::cout << "reading zone: " << zoneid << ", value: " << val << std::endl;
        std::vector<int> nodeids;
        for (int j = 0; j < nfaces; ++j)
        {
            utils::find_word(mesh, "Cone");
            int i1, i2, nodeid1, nodeid2;
            mesh >> i1 >> i2 >> nodeid1 >> nodeid2;
            if (nodeids.empty())
            {
                nodeids.push_back(nodeid1);
            }
            else
            {
                auto it = std::find(nodeids.begin(), nodeids.end(), nodeid1);
                if (it == nodeids.end()) nodeids.push_back(nodeid1);
            }
            auto it = std::find(nodeids.begin(), nodeids.end(), nodeid2);
            if (it == nodeids.end()) nodeids.push_back(nodeid2);
        }

        // build the zone (as a Polygon)
        int nds = nodeids.size();
        for (int j = 0; j < nds; ++j) zones[i].add_node(nodeids[j]);
    } // read all zones
    mesh.clear();
    mesh.close();
    timef.clear();
    timef.close();
    std::cout << "vmin: " << vmin << std::endl;
    std::cout << "vmax: " << vmax << std::endl;

    // zone processing kernel
    std::mutex mg;
    auto process_zone = [&](const int i)
    {
        double val = v[i];
        mg.lock();
        std::cout << "processing zone: " << i << ", value: " << val << std::endl;
        mg.unlock();
        Polygon& zone = zones[i];
        Vector3d rc; // zone center
        int nds = zone.size();
        for (int j = 0; j < nds; ++j) rc += g.get_node(zone.get_node(j)).getr();
        rc /= nds;
        double x = rc.getx();
        double y = rc.gety();
        int64_t ixc = utils::nint((x-xmin)/d);
        int64_t iyc = utils::nint((y-ymin)/d);
        // canvas point nearest to zone center
        double xp = xmin  +  ixc * d;
        double yp = ymin  +  iyc * d;
        if (zone.contains(g, Vector3d(xp, yp, 0.0)))
        {
            z[iyc][ixc] = val; // paint the (approximate) center of the zone
            painted[iyc][ixc] = 1;

            // limiting indeces for the square expanding around ixc, iyc
            int64_t ixmin = ixc;
            int64_t ixmax = ixc;
            int64_t iymin = iyc;
            int64_t iymax = iyc;

            // keep expanding the square and painting the canvas (z)
            // until all (xp, yp) points are outside of this zone
            while (true)
            {
                bool all_are_outside = true;
                --ixmin;
                ++ixmax;
                --iymin;
                ++iymax;
                int64_t ix = ixc;
                int64_t iy = iyc;

                // south edge
                xp = xmin  +  ixmin * d;
                yp = ymin  +  iymin * d;
                if (iymin >= 0  &&  iymin < ny)
                for (ix = ixmin; ix <= ixmax; ++ix)
                {
                    if (zone.contains(g, Vector3d(xp, yp, 0.0)))
                    {
                        all_are_outside = false;
                        if (ix >= 0  &&  ix < nx)
                        {
                            z[iymin][ix] = val;
                            painted[iymin][ix] = 1;
                        }
                    }
                    xp += d;
                }

                // east edge
                xp = xmin  +  ixmax * d;
                yp = ymin  +  iymin * d;
                if (ixmax >= 0  &&  ixmax < nx)
                {
                    for (iy = iymin; iy <= iymax; ++iy)
                    {
                        if (zone.contains(g, Vector3d(xp, yp, 0.0)))
                        {
                            all_are_outside = false;
                            if (iy >= 0  &&  iy < ny)
                            {
                                z[iy][ixmax] = val;
                                painted[iy][ixmax] = 1;
                            }
                        }
                        yp += d;
                    }
                }

                // north edge
                xp = xmin  +  ixmin * d;
                yp = ymin  +  iymax * d;
                if (iymax >= 0  &&  iymax < ny)
                {
                    for (ix = ixmin; ix <= ixmax; ++ix)
                    {
                        if (zone.contains(g, Vector3d(xp, yp, 0.0)))
                        {
                            all_are_outside = false;
                            if (ix >= 0  &&  ix < nx)
                            {
                                z[iymax][ix] = val;
                                painted[iymax][ix] = 1;
                            }
                        }
                        xp += d;
                    }
                }

                // west edge
                xp = xmin  +  ixmin * d;
                yp = ymin  +  iymin * d;
                if (ixmin >= 0  &&  ixmin < nx)
                {
                    for (iy = iymin; iy <= iymax; ++iy)
                    {
                        if (zone.contains(g, Vector3d(xp, yp, 0.0)))
                        {
                            all_are_outside = false;
                            if (iy >= 0  &&  iy < ny)
                            {
                                z[iy][ixmin] = val;
                                painted[iy][ixmin] = 1;
                            }
                        }
                        yp += d;
                    }
                }

                if (all_are_outside) break;

            } // while (true)
        } // if (zone.contains(g, Vector3d(xp, yp, 0.0)))
        mg.lock();
        std::cout << "finished zone: " << i << ", value: " << val << std::endl;
        mg.unlock();
    }; // zone processing kernel

    IndexQueue iq(nzones);
    auto process_zones = [&]()
    {
        while (true)
        {
            int i = iq.next_index();
            if (i == nzones) break;
            process_zone(i);
        }
    };
 
    // original serial code: version 1
    // for (int i = 1; i < nzones; ++i) process_zone(i);

    // original serial code: version 2
    // process_zones();

    std::vector<std::thread> th(nth);
    for (int ith = 1; ith < nth; ++ith) th[ith] = std::thread(process_zones);
    process_zones();
    for (int ith = 1; ith < nth; ++ith) th[ith].join();

    // painting skipped points
    auto paint_row = [&](const int64_t iy)
    {
        for (int64_t ix = nx-1; ix > 0; --ix)
        {
            if (painted[iy][ix-1] == 0   &&   painted[iy][ix] == 1)
            {
                z[iy][ix-1] = z[iy][ix];
                painted[iy][ix-1] = 1;
            }
        }
    };
    auto paint_rows = [&](const int64_t ibegin, const int64_t iend)
    {
        for (int64_t iy = ibegin; iy < iend; ++iy) paint_row(iy);
    };
    thread_tasks(paint_rows, ny, nth);

    // write output file
    std::string pfname = "./" + q + "_" + tlabel + ".dat";
    std::cout << "writing output file: " << pfname << std::endl;
    std::ofstream p(pfname.c_str());
    p << "# name: " + q + "\n# unit: " + u + "\n# nx: " << nx << "\n# ny: " << ny
      << "\n# xmin: " << xmin << "\n# xmax: " << xmax
      << "\n# ymin: " << ymin << "\n# ymax: " << ymax
      << "\n# vmin: " << vmin << "\n# vmax: " << vmax
      << "\n# m: 0\n\n# start\n";
    for (int64_t iyc = 0; iyc < ny; ++iyc)
    {
        p << '\n';
        for (int64_t ixc = 0; ixc < nx; ++ixc)
            p << z[iyc][ixc] << '\n';
    }
    p.clear();
    p.close();

    std::cout << "\nend" << std::endl;

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------

// end plot2dcyl_main.cpp

