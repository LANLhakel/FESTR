/**
 * @file Diagnostics.cpp
 * @brief A collection of Detector objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 5 February 2015\n
 * Last modified on 16 March 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*=============================================================================

Diagnostics.cpp

=============================================================================*/

#include <Diagnostics.h>

#include <Progress.h>
#include <Vector3d.h>
#include <utils.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

#ifdef MPI
#include <mpi.h>
#endif

//-----------------------------------------------------------------------------

Diagnostics::Diagnostics(): level(0), freq(0), path(""), outpath(""), det()
{}

//-----------------------------------------------------------------------------

Diagnostics::Diagnostics(const int level_in,
                         const std::string &diag_path,
                         const std::string &hydro_path,
                         const std::string &out_path,
                         const Database &d):
    level(level_in), freq(0), path(diag_path), outpath(""), det()
{
    std::string fname(hydro_path + "times.txt");
    std::string times_string(utils::file_to_string(fname));

    size_t nhv = d.get_nhv();
    double x, y, z, sr;
    std::ifstream bsphere((hydro_path + "bounding_sphere.txt").c_str());
    if (!bsphere.is_open())
    {
        std::cerr << "Error: file " << hydro_path << "bounding_sphere.txt "
                  << "is not open in "
                  << "Diagnostics::Diagnostics(parametrized)" << std::endl;
        exit(EXIT_FAILURE);
    }
    bsphere >> x >> y >> z >> sr;
    Vector3d sc(x, y, z);
    bsphere.close();
    bsphere.clear();

    std::ifstream infile((diag_path + "list.txt").c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: file " << diag_path << "list.txt is not open in "
                  << "Diagnostics::Diagnostics(parametrized)" << std::endl;
        exit(EXIT_FAILURE);
    }
    utils::find_word(infile, "prints");
    infile >> freq;
    utils::find_word(infile, "Detectors");
    int i, n;
    size_t ntheta, nphi, freq_Ray, freq_patch, freq_trace;
    std::string dname, symmetry, back_type, tracking_str;
    double dx, dy, theta_max, hv_min, hv_max, fwhm;
    std::string back_value;
    infile >> n;
    utils::find_line(infile, "Detector_Name ntheta nphi freq_Ray");
    for (i = 0; i < n; ++i)
    {
        infile >> dname >> ntheta >> nphi >> freq_Ray;
        if (ntheta == 0) nphi = 0; // parallel Rays only
        std::ifstream indet((diag_path + dname + ".txt").c_str());
        if (!indet.is_open())
        {
            std::cerr << "Error: file " << diag_path + dname
                      << ".txt is not open in "
                      << "Diagnostics::Diagnostics(parametrized)" << std::endl;
            exit(EXIT_FAILURE);
        }

        utils::find_word(indet, "path");
        indet >> outpath;
        if (outpath == "/")
            outpath = out_path;
        else
            outpath = out_path + outpath;

        utils::find_word(indet, "freq_patch");
        indet >> freq_patch;

        utils::find_word(indet, "freq_trace");
        indet >> freq_trace;

        utils::find_word(indet, "symmetry");
        indet >> symmetry;

        utils::find_word(indet, "rc");
        indet >> x >> y >> z;
        Vector3d rc(x, y, z);

        utils::find_word(indet, "rx");
        indet >> x >> y >> z;
        Vector3d rx(x, y, z);

        utils::find_word(indet, "ry");
        indet >> x >> y >> z;
        Vector3d ry(x, y, z);

        utils::find_word(indet, "dx");
        indet >> dx;

        utils::find_word(indet, "dy");
        indet >> dy;

        utils::find_word(indet, "pc");
        indet >> x >> y >> z;
        Vector3d pc(x, y, z);

        utils::find_word(indet, "theta_max");
        indet >> theta_max;

        utils::find_word(indet, "range");
        indet >> hv_min >> hv_max;

        utils::find_word(indet, "fwhm");
        indet >> fwhm;

        utils::find_word(indet, "backlighter");
        indet >> back_type >> back_value;

        utils::find_word(indet, "tracking");
        indet >> tracking_str;
        bool tracking(utils::string_to_bool(tracking_str));
        
        indet.close();
        indet.clear();

        std::string dbpth(d.get_path());
        Detector detctr(freq_patch, freq_Ray, freq_trace, diag_path,
                        dname, outpath, dbpth, symmetry, i, rc, rx, ry, dx, dy,
                        nhv, hv_min, hv_max, fwhm, pc, back_type, back_value,
                        tracking);
        if ((detctr.get_symmetry() != "none") && (n != 1))
        {
            std::cerr << "Error: Only 1 Detector is permitted in 1-D"
                      << std::endl;
            exit(EXIT_FAILURE);
        }
        if (theta_max <= 0.0) theta_max = detctr.compute_theta_max(sc, sr);
        detctr.set_bundle(theta_max, ntheta, nphi);
        det.emplace_back(std::move(detctr));

        fname = outpath + "times.txt";
        std::ofstream times_file(fname.c_str());
        times_file << times_string << std::endl;
        times_file.close();
        times_file.clear();
    }
    infile.close();
    infile.clear();
}

//-----------------------------------------------------------------------------

size_t Diagnostics::size() const {return det.size();}

//-----------------------------------------------------------------------------

std::string Diagnostics::to_string() const
{
    std::string s("Number of Detectors ");
    s += utils::int_to_string(det.size(), ' ', 2);
    s += "\nDetector_Name ntheta nphi";
    for (size_t i = 0; i < det.size(); ++i)
    {
        const Detector & d = det.at(i);
        s += "\n" + d.get_dname()
           + " " + utils::int_to_string(d.get_ntheta(), ' ', cnst::INT_WIDTH)
           + " " + utils::int_to_string(d.get_nphi(), ' ', cnst::INT_WIDTH);
    }
    return s;
}

//-----------------------------------------------------------------------------

std::string Diagnostics::get_name(const size_t i) const
{return det.at(i).get_dname();}

//-----------------------------------------------------------------------------

size_t Diagnostics::get_index(const std::string &s) const
{
    size_t n = size();
    size_t i;
    for (i = 0; i < n; ++i) if (s == get_name(i)) return i;
    return n;
}

//-----------------------------------------------------------------------------

void Diagnostics::postprocess(const Database &d, const Hydro &h, Goal &gol)
{
    #include <diag_exec.inc>
    std::string name("Time step");

    { // begin block defining Progress diag_counter scope
    Progress diag_counter(name, level, nintervals, freq, DIAGSEP, std::cout);
    for (size_t j = 0; j < nintervals; ++j) // loop over time
    {
        size_t it = h.time_index_at(j);
        double t = h.time_at(it);
        double dt = h.dt_at(it);
        h.load_at(it, g, m);
        Progress det_counter("Detector", level+1, ndet,                          diag_counter.get_next_freq(freq_det), DETSEP, std::cout);
        for (size_t id = 0; id < ndet; ++id) // loop over Detectors
        {
            det.at(id).do_patches(&det_counter, g, m, d,
                                  tbl, it, t, dt, ntd, gol);
            det_counter.advance();
        }
        diag_counter.advance();
    } // end loop over time
    } // end block defining Progress diag_counter scope

    #ifdef MPI
    MPI_Barrier(MPI_COMM_WORLD);
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if (my_rank == 0)
    {
    #endif

    if (freq_det > 0)
    {
        std::cout << "\nbegin processing time-integrated, "
                  << "space-resolved spectra ...\n" << std::endl;
    }

    Progress det_counter("Detector", level+1, ndet, freq_det,
                         DETSEP, std::cout);
    for (size_t id = 0; id < ndet; ++id) // loop over Detectors
    {
        Detector &deti = det.at(id);
        std::string header(deti.get_dname() + "-yst");
        std::string fname(deti.get_path() + header + ".txt");
        header += "\n";

        if (deti.get_ntheta() == 0)
            header += "data in J/sr/eV";
        else
            header += "data in J/eV";

        deti.yt_to_files(&det_counter, gol, h);

        std::vector<double> hv(deti.get_hv());
        double fwhm = deti.get_fwhm();
        size_t nhv = deti.yst.size();
        ArrDbl ybroad(nhv);
        utils::convolution(fwhm, hv, deti.yst, hv, ybroad);
        ybroad.to_file(fname, header);

        det_counter.advance();
    }

    if (freq_det > 0)
    {
        std::cout << "... done processing time-integrated, "
                  << "space-resolved spectra.\n" << std::endl;
    }

    #ifdef MPI
    }
    #endif
}

//-----------------------------------------------------------------------------

void Diagnostics::analyze(const Database &d, Hydro &h, Goal &gol)
{
    #include <diag_exec.inc>
    std::vector<size_t> ndim = h.get_ndim();
    size_t n = ndim.size();
    size_t current_zone;
    size_t previous_zone = n;
    std::string name("Case");

    { // begin block defining Progress diag_counter scope
    Progress diag_counter(name, level, nintervals, freq, DIAGSEP, std::cout);

    for (size_t j = 0; j < nintervals; ++j) // loop over cases
    {
        size_t it = h.time_index_at(j);
        double t = h.time_at(0);
        double dt = h.dt_at(0);

        if (det.at(0).get_symmetry() == "spherical")
        {
            size_t jt = nintervals - it - 1;  // peeling the onion
            h.load_at(jt, g, m);      // using summation-based index jt
            if (it == 0)
            {   // set bounding Zone (fixed) on first pass through it loop
                previous_zone = n - 1;
                h.load_at(0, g, m);
            }
            else // it > 0
            {
                current_zone = utils::one_to_two(ndim, jt).first;
                if (current_zone != previous_zone)
                {
                    auto obj = gol.get_objective(previous_zone-1);
                    h.load_at(obj->get_best_case(), g, m);
                    previous_zone = current_zone;
                }
            }
            det.at(0).evaluate(ndim, g, m, d, tbl, jt, t, dt, ntd, gol);
            }

        else // "symmetry == none" path
        {
            h.load_at(it, g, m); // using product-based index it
            Progress det_counter("Detector", level+1, ndet,
                                 diag_counter.get_next_freq(freq_det),
                                 DETSEP, std::cout);
            for (size_t id = 0; id < ndet; ++id) // loop over Detectors
            {
                det.at(id).do_patches(&det_counter, g, m, d, tbl, it, t, dt,
                                      ntd, gol);
                det_counter.advance();
            }
        } // det.at(0).get_symmetry()

        gol.update_best(it);
        diag_counter.advance();
    } // end loop over cases
    } // end block defining Progress diag_counter scope

    // redo the best case and write results
    gol.set_analysis(false);

    // switching from summation-based indices jt to product-based index it,
    // as if we hadn't taken advantage of spherical symmetry during search
    if (h.get_symmetry() == "spherical") h.set_symmetry("none");

    size_t it = gol.get_best_case();
    h.load_at(it, g, m);
    double t = h.time_at(0);
    double dt = h.dt_at(0);
    ntd = h.get_ntd();
    for (size_t id = 0; id < ndet; ++id) // loop over Detectors
        det.at(id).do_patches(nullptr, g, m, d, tbl, it, t, dt, ntd, gol);

    gol.set_analysis(true);
    size_t nzones = m.size();
    std::string zone_content;
    std::string best_case_fname(outpath + "best_case.dat");
    std::ofstream best_case_plot(best_case_fname.c_str());
    best_case_fname = outpath + "best_case.txt";
    std::ofstream best_case_full(best_case_fname.c_str());
    best_case_full << "time 0 s";
    std::string header("#      Zone   ");
    header += "ne(el./cm3)    te(eV)         tr(eV)         ";
    header += "np(ions/cm3)   fps";
    std::cout << header;
    best_case_plot << header;
    for (size_t iz = 0; iz < nzones; ++iz)
    {
        if (iz > 0)
        {
            zone_content = "\n"
                         + utils::int_to_string(iz, ' ', cnst::INT_WIDTH)
                         + m.get_zone(iz)->mat_to_string_plot();
            std::cout << zone_content;
            best_case_plot << zone_content;
        }
        best_case_full << "\n\n" << m.get_zone(iz)->mat_to_string_full();
    }
    std::cout << std::endl;
    best_case_plot << std::endl;
    best_case_plot.close();
    best_case_plot.clear();
    best_case_full << std::endl;
    best_case_full.close();
    best_case_full.clear();
}

//-----------------------------------------------------------------------------

void Diagnostics::execute(const Database &d, Hydro &h, Goal &gol)
{
    if (gol.get_analysis())
        analyze(d, h, gol);
    else
        postprocess(d, h, gol);
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Diagnostics &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

//  end Diagnostics.cpp
