/**
 * @file
 * @brief A collection of Detector objects
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 5 February 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*=============================================================================

Diagnostics.cpp

=============================================================================*/

#include "Diagnostics.h"
#include "Vector3d.h"
#include "utilities.h"
#include "Progress.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

//-----------------------------------------------------------------------------

#ifdef MPIYES
#include "TaskPool.h"
#endif

/// Used as IT type in TaskPool for MPI parallelization of time steps
struct TimeStepID
{
public:

    // user defined members
    size_t it; // time-step integer label

//-----------------------------------------

    // members required by class TaskPool
    char *b;     // buffer

//-----------------------------------------

    TimeStepID(void): it(0), b(NULL) {};

//-----------------------------------------

    explicit TimeStepID(const size_t it_in): it(it_in), b(NULL) {};

//-----------------------------------------

    void allocate_buffer(const size_t nbytes)
    {
        b = (char *)malloc(nbytes);
        if (b == NULL)
        {
            std::cerr << "Error in TimeStepID.allocate_buffer()"
                      << std::endl;
            exit(EXIT_FAILURE);
        }
    }

//-----------------------------------------

    void clear_buffer(void) {free(b); b = NULL;}

//-----------------------------------------

    size_t pack(void)
    {
        size_t nbytes = 0;
        size_t chunk_size = 0;
        size_t offset = 0;

        nbytes += sizeof(size_t);

        allocate_buffer(nbytes);

        chunk_size = sizeof(size_t);
        memcpy(b+offset, &it, chunk_size);
        offset += chunk_size;

        return nbytes;
    }

//-----------------------------------------

    void unpack(void)
    {
        size_t chunk_size = 0;
        size_t offset = 0;

        chunk_size = sizeof(size_t);
        memcpy(&it, b+offset, chunk_size);
        offset += chunk_size;

        clear_buffer();
    }
};

//-----------------------------------------------------------------------------

/// Used as OT type in TaskPool for MPI parallelization of time steps
struct TimeStepOutput
{
public:

    // user defined members
    size_t it;

//-----------------------------------------

    // members required by class TaskPool
    char *b;     // buffer
    int case_id; // (e.g. for Progress)
    int rank;    // (e.g. for tracking of tasks)

//-----------------------------------------

    TimeStepOutput(void): it(0), b(NULL), case_id(-1), rank(-1) {};

//-----------------------------------------

    void allocate_buffer(const size_t nbytes)
    {
        b = (char *)malloc(nbytes);
        if (b == NULL)
        {
            std::cerr << "Error in TimeStepOutput.allocate_buffer()"
                      << std::endl;
            exit(EXIT_FAILURE);
        }
    }

//-----------------------------------------

    void clear_buffer(void) {free(b); b = NULL;}

//-----------------------------------------

    size_t pack(void)
    {
        size_t nbytes = 0;
        size_t chunk_size = 0;
        size_t offset = 0;

        nbytes += sizeof(size_t);

        allocate_buffer(nbytes);

        chunk_size = sizeof(size_t);
        memcpy(b+offset, &it, chunk_size);
        offset += chunk_size;

        return nbytes;
    }

//-----------------------------------------

    void unpack(void)
    {
        size_t chunk_size = 0;
        size_t offset = 0;

        chunk_size = sizeof(size_t);
        memcpy(&it, b+offset, chunk_size);
        offset += chunk_size;

        clear_buffer();
    }
};

//-----------------------------------------------------------------------------

/// Encapsulates "globals" for MPI parallelization using TaskPool
namespace HistoryEnvironment
{
    const Database *d;
    Grid *g;
    Mesh *m;
    const Hydro *h;
    Table *tbl;
    Goal *gol;
    size_t ndet;
    int ntd;
    int level;
    size_t freq_det;
    size_t next_freq;
    std::string DETSEP;
    std::vector<Detector> *det;

//-----------------------------------------

    /// HistoryEnvironment "constructor"
    void construct(const Database *d_in,
                   Grid *g_in,
                   Mesh *m_in,
                   const Hydro *h_in,
                   Table *tbl_in,
                   Goal *gol_in,
                   size_t ndet_in,
                   int ntd_in,
                   int level_in,
                   size_t freq_det_in,
                   size_t next_freq_in,
                   std::string DETSEP_in,
                   std::vector<Detector> *det_in)
    {
        d = d_in;
        g = g_in;
        m = m_in;
        h = h_in;
        tbl = tbl_in;
        gol = gol_in;
        ndet = ndet_in;
        ntd = ntd_in;
        level = level_in;
        freq_det = freq_det_in;
        next_freq = next_freq_in;
        DETSEP = DETSEP_in;
        det = det_in;
    }

//-----------------------------------------

    /// Used as the distributed task function TaskPool::perform_task
    void do_time_step(const TimeStepID &tid, TimeStepOutput &tout)
    {
        tout.it = tid.it;
        double t = h->time_at(tid.it);
        double dt = h->dt_at(tid.it);
        h->load_at(tid.it, *g, *m);
        Progress det_counter("Detector", level+1, ndet,
                             next_freq, DETSEP, std::cout);
        for (size_t id = 0; id < ndet; ++id) // loop over Detectors
        {
            (*det).at(id).do_patches(&det_counter, *g, *m, *d,
                                     *tbl, tid.it, t, dt, ntd, *gol);
            det_counter.advance();
        }
    }
}

//-----------------------------------------------------------------------------

/// Enables Progress counter within MPI parallelization using TaskPool
namespace ProgressEnvironment
{
    Progress *p;

    /// ProgressEnvironment "constructor"
    void construct(Progress *p_in) {p = p_in;}

    /// Used as the root-process task function TaskPool::process_results
    void advance(const TimeStepOutput &tout) {(void)(tout); p->advance();}
}

//-----------------------------------------------------------------------------

Diagnostics::Diagnostics(void): level(0), freq(0), path(""), outpath(""), det()
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
    double dx, dy, theta_max, hv_min, hv_max, fwhm, back_value;
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
        Detector detctr(freq_patch, freq_Ray, freq_trace,
                        dname, outpath, dbpth, symmetry, i, rc, rx, ry, dx, dy,
                        nhv, hv_min, hv_max, fwhm, sc, back_type, back_value,
                        tracking);
        if ((detctr.get_symmetry() != "none") && (n != 1))
        {
            std::cerr << "Error: Only 1 Detector is permitted in 1-D"
                      << std::endl;
            exit(EXIT_FAILURE);
        }
        theta_max = detctr.compute_theta_max(sc, sr);
        detctr.set_bundle(theta_max, ntheta, nphi);
        det.push_back(detctr);

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

Diagnostics::~Diagnostics(void)
{
    level = 0;
    freq = 0;
    path = "";
    det.clear();
}

//-----------------------------------------------------------------------------

size_t Diagnostics::size(void) const {return det.size();}

//-----------------------------------------------------------------------------

std::string Diagnostics::to_string(void) const
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
    #include "diag_exec.inc"
    std::string name("Time step");

    { // begin block defining Progress diag_counter scope
    Progress diag_counter(name, level, nt, freq, DIAGSEP, std::cout);
    HistoryEnvironment::construct(&d, &g, &m, &h, &tbl, &gol, ndet, ntd, level,
                                  freq_det,
                                  diag_counter.get_next_freq(freq_det),
                                  DETSEP, &det);
    ProgressEnvironment::construct(&diag_counter);

    #ifdef MPIYES
    std::queue<TimeStepID> qin; // passed to TaskPool::q member
    for (size_t it = 0; it < nt; ++it)
    {
        TimeStepID tin(it);
        qin.push(tin);
    }
    TaskPool<TimeStepID, TimeStepOutput> time_steps(MPI_COMM_WORLD,
        HistoryEnvironment::do_time_step, ProgressEnvironment::advance, qin);
    time_steps.execute();
    #else
    for (size_t it = 0; it < nt; ++it) // loop over time
    {
        TimeStepOutput tout;
        TimeStepID tin(it);
        HistoryEnvironment::do_time_step(tin, tout);
        ProgressEnvironment::advance(tout);
    } // end loop over time
    #endif
    } // end block defining Progress diag_counter scope

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

        std::vector<double> hv(deti.get_hv());

        #ifdef MPIYES
        deti.yst_using_mpi(nt, ntd, h); // yst already convolved with fwhm
        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        if (my_rank == 0) deti.yst.to_file(fname, header);
        #else
        double fwhm = deti.get_fwhm();
        size_t nhv = deti.yst.size();
        ArrDbl ybroad(nhv);
        utils::convolution(fwhm, hv, deti.yst, hv, ybroad);
        ybroad.to_file(fname, header);
        #endif

        deti.yt_to_files(&det_counter, gol, nt, ntd, h);
        det_counter.advance();
    }

    if (freq_det > 0)
    {
        std::cout << "... done processing time-integrated, "
                  << "space-resolved spectra.\n" << std::endl;
    }
}

//-----------------------------------------------------------------------------

void Diagnostics::analyze(const Database &d, Hydro &h, Goal &gol)
{
    #include "diag_exec.inc"
    std::vector<size_t> ndim = h.get_ndim();
    size_t n = ndim.size();
    size_t current_zone;
    size_t previous_zone = n;
    std::string name("Case");

    { // begin block defining Progress diag_counter scope
    Progress diag_counter(name, level, nt, freq, DIAGSEP, std::cout);
    for (size_t it = 0; it < nt; ++it) // loop over cases
    {
        double t = h.time_at(0);
        double dt = h.dt_at(0);

        if (det.at(0).get_symmetry() == "spherical")
        {
            size_t jt = nt - it - 1;  // peeling the onion
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
                    const Objective *obj = gol.get_objective(previous_zone-1);
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
        det.at(id).do_patches(NULL, g, m, d, tbl, it, t, dt, ntd, gol);

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

// end Diagnostics.cpp
