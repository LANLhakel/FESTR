/**
 * @file Detector.cpp
 * @brief Detector objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 28 January 2015\n
 * Last modified on 29 April 2022
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*=============================================================================

pmh_2015_0210
pmh_2015_0312

=============================================================================*/

#include <Detector.h>

#include <Node.h>
#include <utils.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

/*
#ifdef OMP
#include <omp.h>
#endif
*/

//-----------------------------------------------------------------------------

#ifdef MPI
#include <TaskPool.h>
#endif

//-----------------------------------------------------------------------------

const size_t Detector::NPT = 4;

//-----------------------------------------------------------------------------

/// Used as IT type in TaskPool for MPI parallelization of patches
struct PatchID
{
public:

    // user defined members
    size_t ix, iy; // patch integer labels
    size_t j; // explicit Progress counter

//-----------------------------------------

    // members required by class TaskPool
    char *b;     // buffer

//-----------------------------------------

    PatchID(): ix(0), iy(0), j(0), b(nullptr) {};

//-----------------------------------------

    PatchID(const size_t ix_in, const size_t iy_in, const size_t j_in):
        ix(ix_in), iy(iy_in), j(j_in), b(nullptr) {};

//-----------------------------------------

    // Pointer member char *b = nullptr when PatchID objects
    // interact with TaskPool's queue
    PatchID(const PatchID &) = default;
    PatchID &operator=(const PatchID &) = default;

//-----------------------------------------

    void allocate_buffer(const size_t nbytes)
    {
        b = (char *)malloc(nbytes);
        if (b == nullptr)
        {
            std::cerr << "Error in PatchID.allocate_buffer()"
                      << std::endl;
            exit(EXIT_FAILURE);
        }
    }

//-----------------------------------------

    void clear_buffer() {free(b); b = nullptr;}

//-----------------------------------------

    size_t pack()
    {
        size_t nbytes = 0;
        size_t chunk_size = 0;
        size_t offset = 0;

        nbytes += 3*sizeof(size_t);

        allocate_buffer(nbytes);

        chunk_size = sizeof(size_t);
        memcpy(b+offset, &ix, chunk_size);
        offset += chunk_size;

        chunk_size = sizeof(size_t);
        memcpy(b+offset, &iy, chunk_size);
        offset += chunk_size;

        chunk_size = sizeof(size_t);
        memcpy(b+offset, &j, chunk_size);
        offset += chunk_size;

        return nbytes;
    }

//-----------------------------------------

    void unpack()
    {
        size_t chunk_size = 0;
        size_t offset = 0;

        chunk_size = sizeof(size_t);
        memcpy(&ix, b+offset, chunk_size);
        offset += chunk_size;

        chunk_size = sizeof(size_t);
        memcpy(&iy, b+offset, chunk_size);
        offset += chunk_size;

        chunk_size = sizeof(size_t);
        memcpy(&j, b+offset, chunk_size);
        offset += chunk_size;

        clear_buffer();
    }
};

//-----------------------------------------------------------------------------

/// Used as OT type in TaskPool for MPI parallelization of patches
struct PatchSpectrum
{
public:

    // user defined members
    size_t ix, iy; // patch integer labels
    size_t nhv; // number of photon-energy points
    std::vector<double> yp; // spectrum

//-----------------------------------------

    // members required by class TaskPool
    char *b;     // buffer
    int case_id; // (e.g. for Progress)
    int rank;    // (e.g. for tracking of tasks)

//-----------------------------------------

    PatchSpectrum(): ix(0), iy(0), nhv(0), yp(), b(nullptr), case_id(-1), rank(-1)
    {};

//-----------------------------------------

    PatchSpectrum(const PatchSpectrum &) = delete;
    PatchSpectrum &operator=(const PatchSpectrum &) = delete;

//-----------------------------------------

    void allocate_buffer(const size_t nbytes)
    {
        b = (char *)malloc(nbytes);
        if (b == nullptr)
        {
            std::cerr << "Error in PatchSpectrum.allocate_buffer()"
                      << std::endl;
            exit(EXIT_FAILURE);
        }
    }

//-----------------------------------------

    void clear_buffer() {free(b); b = nullptr;}

//-----------------------------------------

    size_t pack()
    {
        size_t nbytes = 0;
        size_t chunk_size = 0;
        size_t offset = 0;

        nbytes += 3*sizeof(size_t);
        nbytes += nhv * sizeof(double);

        allocate_buffer(nbytes);

        chunk_size = sizeof(size_t);
        memcpy(b+offset, &ix, chunk_size);
        offset += chunk_size;

        chunk_size = sizeof(size_t);
        memcpy(b+offset, &iy, chunk_size);
        offset += chunk_size;

        chunk_size = sizeof(size_t);
        memcpy(b+offset, &nhv, chunk_size);
        offset += chunk_size;

        chunk_size = sizeof(double);
        for (size_t ihv = 0; ihv < nhv; ++ihv)
        {
            memcpy(b+offset, &yp[ihv], chunk_size);
            offset += chunk_size;
        }

        return nbytes;
    }

//-----------------------------------------

    void unpack()
    {
        size_t chunk_size = 0;
        size_t offset = 0;

        chunk_size = sizeof(size_t);
        memcpy(&ix, b+offset, chunk_size);
        offset += chunk_size;

        chunk_size = sizeof(size_t);
        memcpy(&iy, b+offset, chunk_size);
        offset += chunk_size;

        chunk_size = sizeof(size_t);
        memcpy(&nhv, b+offset, chunk_size);
        offset += chunk_size;

        yp.resize(nhv);
        chunk_size = sizeof(double);
        for (size_t ihv = 0; ihv < nhv; ++ihv)
        {
            memcpy(&yp[ihv], b+offset, chunk_size);
            offset += chunk_size;
        }

        clear_buffer();
    }
};

//-----------------------------------------------------------------------------

/// Encapsulates "globals" for MPI parallelization using TaskPool
namespace PatchEnvironment
{
    Detector *this_det;
    Progress *parent;
    const Grid *g;
    const Mesh *m;
    const Database *d;
    const Table *tbl;
    size_t it;
    double t;
    double dt;
    int ntd;
    Goal *gol;
    size_t j; // explicit Progress counter needed for MPI

//-----------------------------------------

    /// PatchEnvironment "constructor"
    void construct(Detector *this_det_in,
                   Progress *parent_in,
                   const Grid *g_in,
                   const Mesh *m_in,
                   const Database *d_in,
                   const Table *tbl_in,
                   size_t it_in,
                   double t_in,
                   double dt_in,
                   int ntd_in,
                   Goal *gol_in)
    {
        this_det = this_det_in;
        parent = parent_in;
        g = g_in;
        m = m_in;
        d = d_in;
        tbl = tbl_in;
        it = it_in;
        t = t_in;
        dt = dt_in;
        ntd = ntd_in;
        gol = gol_in;
        j = 0;
    }

//-----------------------------------------

/// Used as the distributed task function TaskPool::perform_task
void do_patch(const PatchID &pid, PatchSpectrum &pout)
{
    IntPair patch(pid.ix, pid.iy);
    pout.ix = pid.ix;
    pout.iy = pid.iy;

    // set up Progress counter
    int next_level;
    size_t next_freq;
    if (parent == nullptr)
    {
        next_level = 0;
        next_freq = 0;
    }
    else
    {
        next_level = parent->get_level() + 1;

        #ifdef MPI
        size_t pf = parent->get_freq();
        if (pf == 0)
            next_freq = 0;
        else
            next_freq = ( (pid.j+1) == pf ? this_det->freq_trace : 0 );

        #else
        next_freq = parent->get_next_freq(this_det->freq_Ray);
        #endif
    }

    const std::string SEP("----------------------------------------\n");
    size_t ncount(this_det->ntheta == 0 ? 1 : (this_det->ntheta-1)*this_det->nphi + 1);
    Progress counter(this_det->dname + "_Ray", next_level, ncount, next_freq,
                     SEP, std::cout);

    this_det->yp[patch].fill(0.0);
    std::string cname(this_det->dname + "-yp" + this_det->patch_fname(patch));
    std::string fname(this_det->path + cname);
    std::string tname(time_fname(it, ntd));
    std::string header(time_string(it, ntd, t));
    header += this_det->patch_string(patch);
    this_det->do_Ray(&counter, patch, INT_PAIR_00, *g, *m, *d, *tbl,
                     cname, header, tname, *gol);
    counter.advance();

/*
    #ifdef OMP
    omp_set_num_threads(atoi(getenv("OMP_NUM_THREADS")));
    #pragma omp parallel for default(none) \
     firstprivate(this_det,gol,tname,header,cname,tbl,d,m,g,patch) shared(counter) collapse(2)
    #endif
*/
    for (size_t itheta = 1; itheta < this_det->ntheta; ++itheta)
        for (size_t iphi = 0; iphi < this_det->nphi; ++iphi)
        {
            this_det->do_Ray(&counter, patch, IntPair(itheta, iphi), *g, *m, *d, *tbl,
                             cname, header, tname, *gol);
            counter.advance();
        }

    if (this_det->ntheta > 0) // (W/eV); (W/cm2/sr/eV) for ntheta == 0
    {
        if (this_det->symmetry == "none")
            this_det->yp[patch] *= this_det->da;
        else if (this_det->symmetry == "spherical") // Eq.(2)
        {
            std::cerr << "Spherical symmetry is not available in MPI parallel runs" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    header = cname + "_" + tname + "\n" + header;
    fname += "_" + tname + ".txt";

    ArrDbl ybroad(this_det->nhv);
    utils::convolution(this_det->fwhm, this_det->hv, this_det->yp[patch], this_det->hv, ybroad);

    double scale = gol->get_best_scale(cname);
    if (utils::sign_eqt(scale - 1.0, cnst::SCALE_EQT) == 0)
    {
        if (this_det->ntheta == 0)
            header += "data in W/cm2/sr/eV";
        else
            header += "data in W/eV";
    }
    else
    {
        header += "data in arbitrary_units";
        ybroad *= scale;
    }
    ybroad.to_file(fname, header);

    pout.nhv = this_det->nhv;
    pout.yp.resize(pout.nhv);
    for (size_t ihv = 0; ihv < pout.nhv; ++ihv)
        pout.yp[ihv] = this_det->yp[patch][ihv];

}  // end PatchEnvironment::do_patch


/// Used as the root-process task function TaskPool::process_results
void space_integ(const PatchSpectrum &pout)
{
    IntPair patch(pout.ix, pout.iy);

    if (this_det->symmetry == "none")
    {
        for (size_t ihv = 0; ihv < this_det->nhv; ++ihv)
        {
            this_det->ys[ihv] += pout.yp[ihv]; // (W/eV); (W/cm2/sr/eV) for ntheta == 0
            this_det->yt[patch][ihv] += pout.yp[ihv] * dt; // (J/eV); (J/cm2/sr/eV) for ntheta == 0
        }
    }
    else if (this_det->symmetry == "spherical") // Eq.(2)
    {
        if (this_det->ntheta == 0)
        {
            double xi = static_cast<double>(pout.ix);
            if (pout.ix == 0) // dx = diameter of the central circle
                for (size_t ihv = 0; ihv < this_det->nhv; ++ihv)
                    this_det->ys[ihv] += pout.yp[ihv] / 8.0;
            else // ring width = r>(ix) - r<(ix) = dx, for ix > 0
                for (size_t ihv = 0; ihv < this_det->nhv; ++ihv)
                    this_det->ys[ihv] += pout.yp[ihv] * xi; // xi * dx = r>(ix) + r<(ix)
        }
        else
            for (size_t ihv = 0; ihv < this_det->nhv; ++ihv)
                this_det->ys[ihv] += pout.yp[ihv];
    }
    parent->advance();
    ++j;
    if (parent != nullptr) if (j == parent->get_freq()) {j = 0;}
}

}  // close namespace PatchEnvironment

//-----------------------------------------------------------------------------

Detector::Detector(): yt(), yst(),
    freq_patch(0), freq_Ray(0), freq_trace(0),
    dname("no_name"), path("no_path"), symmetry("none"), my_id(-1),
    rc(), ro(), rx(), ry(), ex(), ey(), ez(), bx(), by(), bz(),
    xr(), yr(), zr(), dx(0.0), dy(0.0), da(0.0),
    ux(), uy(), nhv(0), hv(), hvmin(0.0), hvmax(0.0),
    jmin(0), jmax(0), fwhm(-1.0), back_type("none"), back_fname(""),
    back_value(-9.0), yback(), tracking(false),  write_Ray(true),
    nx(0), ny(0), nxd(0), nyd(0),
    pc(), theta_max(0.0), ntheta(0), nphi(0), nthetad(0), nphid(0),
    dtheta(0.0), dphi(0.0), dtheta2(0.0), gdet(), p(), yp(), ys()
    {}

//-----------------------------------------------------------------------------

Detector::Detector(const size_t freq_patch_in, const size_t freq_Ray_in,
                   const size_t freq_trace_in, const std::string &diag_path,
                   const std::string &dname_in, const std::string &path_in,
                   const std::string &dbase_path, const std::string &sym_in,
                   const int my_id_in, const Vector3d & rc_in,
                   const Vector3d &rx_in, const Vector3d &ry_in,
                   const double dx_in, const double dy_in,
                   const size_t nhv_in,
                   const double hv_min, const double hv_max,
                   const double fwhm_in, const Vector3d &pc_in,
                   const std::string &back_type_in,
                   const std::string &back_value_in, const bool tracking_in,
                   const bool write_Ray_in):
    yt(), yst(),
    freq_patch(freq_patch_in), freq_Ray(freq_Ray_in), freq_trace(freq_trace_in),
    dname(dname_in), path(path_in), symmetry(sym_in), my_id(my_id_in),
    rc(rc_in), ro(), rx(rx_in), ry(ry_in), ex(), ey(), ez(), bx(), by(), bz(),
    xr(), yr(), zr(), dx(dx_in), dy(dy_in), da(dx_in*dy_in),
    ux(), uy(), nhv(0), hv(), hvmin(hv_min), hvmax(hv_max),
    jmin(nhv_in), jmax(0), fwhm(fwhm_in), back_type(back_type_in),
    back_fname(""), back_value(-9.0), yback(), tracking(tracking_in),
    write_Ray(write_Ray_in), nx(0), ny(0), nxd(0), nyd(0), pc(pc_in),
    theta_max(0.0), ntheta(0), nphi(0), nthetad(0), nphid(0), dtheta(0.0),
    dphi(0.0), dtheta2(0.0), gdet(), p(), yp(), ys()
{
    // set hv grid
    std::string hvpath(dbase_path + "grids/hv_grid.txt");
    std::ifstream infile(hvpath.c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: file " << hvpath << " is not open in "
                  << "Detector::Detector(parametrized)" << std::endl;
        exit(EXIT_FAILURE);
    }
    utils::find_line(infile, "Grid points:");
    for (size_t ihv = 0; ihv < nhv_in; ++ihv)
    {
        size_t j;
        double e;
        infile >> j >> e;
        bool min_true(e >= hvmin);
        bool max_true(e <= hvmax);
        if (min_true && max_true) hv.emplace_back(std::move(e));
        if (min_true && ihv < jmin) jmin = ihv;
        if (max_true && ihv > jmax) jmax = ihv;
    }
    infile.close();
    infile.clear();
    if (hv.empty())
    {
        std::cerr << "Error: The hv range of Detector " << dname << " has no "
                  << "overlap with the hv range of the Database" << std::endl;
        exit(EXIT_FAILURE);
    }

    // set patch discretization
    nx = static_cast<size_t>(utils::nint( 2.0 * rx_in.norm() / dx_in ));
    ny = static_cast<size_t>(utils::nint( 2.0 * ry_in.norm() / dy_in ));
    if (sym_in == "spherical")
    {
        nx = nx / 2  +  1;
        dx = rx_in.norm() / (static_cast<double>(nx) - 0.5); // Eq.(1)
        ny = 1; // unused
        dy = 2.0 * ry_in.norm();  // unused
        // unlike for sym_in == "none", da != const, and hence (* da) cannot be
        // factored when calculating space-integrated spectrum in do_patches()
        da = 1.0;
    }
    nxd = utils::ndigits(nx);
    nyd = utils::ndigits(ny);

    // initialize space and time integrated spectral arrays
    nhv = jmax - jmin + 1;

    //#ifndef MPI
    ArrDbl y0;
    y0.assign(nhv, 0.0);
    //#endif

    for (size_t iy = 0; iy < ny; ++iy)
        for (size_t ix = 0; ix < nx; ++ix)
        {
            IntPair patch(ix, iy);
            //#ifndef MPI
            yt.insert(SpecPatch::value_type(patch, y0));
            //#endif
            yp[patch].assign(nhv, 0.0);
        }
    ys.assign(nhv, 0.0);
    yst.assign(nhv, 0.0);

    // set patch vectors
    ex = rx.unit();
    ey = ry.unit();
    ez = ex % ey;
    ux = dx * ex;
    uy = dy * ey;

    // orient the basis for Ray bundles
    bz = (rc - pc).unit();
    bx = ex.perpendicular_to(bz);
    by = ey.perpendicular_to(bz);
    if ( bx.norm() > by.norm() )
    {
        bx.normalize();
        by = bz % bx;
    }
    else
    {
        by.normalize();
        bx = by % bz;
    }
    // set the local_to_global() transformation matrix
    xr = Vector3d(bx.getx(), by.getx(), bz.getx()); // x-row
    yr = Vector3d(bx.gety(), by.gety(), bz.gety()); // y-row
    zr = Vector3d(bx.getz(), by.getz(), bz.getz()); // z-row

    // define Polygon's vertices
    Vector3d r(rc - rx - ry);
    gdet.add_node(Node(0, r));  // lower-left corner (Polygon origin)
    ro = r  +  (ux + uy) / 2.0; // lower-left corner (origin for Rays)
    gdet.add_node(Node(1, rc + rx - ry)); // lower-right corner
    gdet.add_node(Node(2, rc + rx + ry)); // upper-right corner
    gdet.add_node(Node(3, rc - rx + ry)); // upper-left corner
    for (size_t i = 0; i < NPT; ++i) p.add_node(i);

    // set up the backlighter
    if (back_type == "file")
    {
        back_fname = back_value_in;
        back_value = -5.0;
    }
    else
    {
        back_value = atof(back_value_in.c_str());
    }

    yback.assign(nhv, back_value); // treating back_type == "flat" as default
    if (back_type == "file")
    {
        std::string back_path = diag_path + back_fname;
        std::ifstream back_file(back_path.c_str());
        if (!back_file.is_open())
        {
            std::cerr << "Error: file " << back_fname << " is not open in "
                      << "Detector::Detector(parametrized)" << std::endl;
            exit(EXIT_FAILURE);
        }
        utils::find_word(back_file, "nhv:");
        size_t nback;
        back_file >> nback;
        std::vector<double> x(nback), y(nback); // the given backlighter table
        utils::find_line(back_file, "# hv(eV)  I0(W/cm2/sr/eV)");
        for (size_t i = 0; i < nback; ++i) back_file >> x.at(i) >> y.at(i);
        back_file.close();
        back_file.clear();
        utils::syngrids(x, y, nback, "lin", "lin", hv, yback, nhv);
    }
    else if (back_type == "blackbody")
    {
        for (size_t ihv = 0; ihv < nhv; ++ihv)
            yback.at(ihv) = utils::planckian(hv.at(ihv), back_value);
    }

    // write out the working backlighter spectrum
    hvpath = path_in + dname_in + "-hv_grid.txt";
    std::ofstream out_hv(hvpath.c_str());
    if (!out_hv.is_open())
    {
        std::cerr << "Error: file " << hvpath << " is not open." << std::endl;
        exit(EXIT_FAILURE);
    }
    out_hv << "\n Number of bits:\n           0\n\n Number of grid points:\n"
           << utils::int_to_string(nhv, ' ', cnst::INT_WIDTH+1)
           << "\n\n Grid points:\n";
    std::string backpath = path_in + dname_in + "-backlighter.txt";
    std::ofstream out_back(backpath.c_str());
    if (!out_back.is_open())
    {
        std::cerr << "Error: file " << backpath << " is not open." << std::endl;
        exit(EXIT_FAILURE);
    }
    out_back << dname_in + "-backlighter\ndata in W/cm2/sr/eV" << std::endl;
    for (size_t ihv = 0; ihv < nhv; ++ihv)
    {
        out_hv << utils::int_to_string(ihv, ' ', cnst::INT_WIDTH+1) << "  "
               << utils::double_to_string(hv.at(ihv)) << std::endl;
        out_back << utils::double_to_string(yback.at(ihv)) << std::endl;
    }
    out_hv.close();
    out_hv.clear();
    out_back.close();
    out_back.clear();
}

//-----------------------------------------------------------------------------

double Detector::abs_diff(const Detector &o) const
{
    return rc.abs_diff(o.rc);
}

//-----------------------------------------------------------------------------

std::string Detector::to_string() const
{
    std::string s(dname + "\nrc" + rc.to_string());
    s += "\nrx" + rx.to_string() + "\nry" + ry.to_string();
    s += "\ndx" + utils::double_to_string(dx);
    s += "\ndy" + utils::double_to_string(dy);
    s += "\npc" + pc.to_string();
    s += "\ntheta_max" + utils::double_to_string(theta_max);
    s += "\nfwhm" + utils::double_to_string(fwhm);
    s += "\nbacklighter " + back_type;
    if (back_type == "file")
        s += " " + back_fname;
    else
        s += utils::double_to_string(back_value);
    s += "\ntracking " + utils::bool_to_string(tracking);
    s += "\nwrite_Ray " + utils::bool_to_string(write_Ray);
    return s;
}

//-----------------------------------------------------------------------------

void Detector::set_bundle(const double theta_max_in,
                          const size_t ntheta_in, const size_t nphi_in)
{
    theta_max = theta_max_in;
    ntheta = ntheta_in;
    nphi = nphi_in;
    nthetad = utils::ndigits(ntheta);
    nphid = utils::ndigits(nphi);
    if (ntheta > 0) dtheta = theta_max / static_cast<double>(ntheta);
    if (nphi > 0) dphi = cnst::TWO_PI / static_cast<double>(nphi);
    dtheta2 = dtheta / 2.0;
}

//-----------------------------------------------------------------------------

std::string Detector::get_dname() const
{
    return dname;
}

//-----------------------------------------------------------------------------

std::string Detector::get_path() const
{
    return path;
}

//-----------------------------------------------------------------------------

std::string Detector::get_symmetry() const
{
    return symmetry;
}

//-----------------------------------------------------------------------------

int Detector::get_my_id() const
{
    return my_id;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_rc() const
{
    return rc;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ro() const
{
    return ro;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_rx() const
{
    return rx;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ry() const
{
    return ry;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ex() const
{
    return ex;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ey() const
{
    return ey;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ez() const
{
    return ez;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_pc() const
{
    return pc;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_bx() const
{
    return bx;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_by() const
{
    return by;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_bz() const
{
    return bz;
}

//-----------------------------------------------------------------------------

size_t Detector::get_nhv() const
{
    return nhv;
}

//-----------------------------------------------------------------------------

std::vector<double> Detector::get_hv() const
{
    return hv;
}

//-----------------------------------------------------------------------------

size_t Detector::get_jmin() const
{
    return jmin;
}

//-----------------------------------------------------------------------------

double Detector::get_hvmin() const
{
    return hvmin;
}

//-----------------------------------------------------------------------------

size_t Detector::get_jmax() const
{
    return jmax;
}

//-----------------------------------------------------------------------------

double Detector::get_hvmax() const
{
    return hvmax;
}

//-----------------------------------------------------------------------------

double Detector::get_fwhm() const
{
    return fwhm;
}

//-----------------------------------------------------------------------------

std::string Detector::get_back_type() const
{
    return back_type;
}

//-----------------------------------------------------------------------------

double Detector::get_back_value() const
{
    return back_value;
}

//-----------------------------------------------------------------------------

std::vector<double> Detector::get_backlighter() const
{
    return yback;
}

//-----------------------------------------------------------------------------

bool Detector::get_tracking() const
{
    return tracking;
}

//-----------------------------------------------------------------------------

size_t Detector::get_nx() const
{
    return nx;
}

//-----------------------------------------------------------------------------

size_t Detector::get_ny() const
{
    return ny;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_vertex(const size_t i) const
{
    return gdet.get_node(i).getr();
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ux() const
{
    return ux;
}

//-----------------------------------------------------------------------------

Vector3d Detector::get_uy() const
{
    return uy;
}

//-----------------------------------------------------------------------------

double Detector::compute_theta_max(const Vector3d &sc, const double sr)
{
    return asin( sr / (rc-sc).norm() );
}

//-----------------------------------------------------------------------------

double Detector::get_theta_max() const
{
    return theta_max;
}

//-----------------------------------------------------------------------------

size_t Detector::get_ntheta() const
{
    return ntheta;
}

//-----------------------------------------------------------------------------

size_t Detector::get_nphi() const
{
    return nphi;
}

//-----------------------------------------------------------------------------

double Detector::get_dtheta() const
{
    return dtheta;
}

//-----------------------------------------------------------------------------

double Detector::get_dtheta2() const
{
    return dtheta2;
}

//-----------------------------------------------------------------------------

double Detector::get_dphi() const
{
    return dphi;
}

//-----------------------------------------------------------------------------

Vector3d Detector::local_to_global(const Vector3d &v) const
{
    return Vector3d( xr * v, yr * v, zr * v );
}

//-----------------------------------------------------------------------------

void Detector::do_Ray(Progress *parent,
                      const IntPair &patch, const IntPair &direction,
                      const Grid &g, const Mesh &m, const Database &d,
                      const Table &tbl,
                      const std::string &froot, const std::string &hroot,
                      const std::string &tname, Goal &gol)
{
    const size_t &ix = patch.first;
    const size_t &iy = patch.second;

    Vector3d r0; // where the Ray hits this patch on *this Detector
    if (symmetry == "none")
        r0  =  ro  +  ux * ix +  uy * iy;
    else if (symmetry == "spherical")
        r0  =  rc  +  ux * ix;

    double theta = static_cast<double>(direction.first) * dtheta;
    double phi = static_cast<double>(direction.second) * dphi;
    Vector3d cvec(local_to_global(-cnst::CV * Vector3d(theta, phi)));

    const double EQT = 1.0e-15;
    auto f = m.get_zone(Zone::BOUNDING_ZONE)->get_face(0);
    FaceID fid(Zone::BOUNDING_ZONE, -3);
    RetIntercept pt = f->intercept(g, r0, cvec, EQT, fid);

    // set up Progress counter
    int next_level;
    size_t next_freq;
    if (parent == nullptr)
    {
        next_level = 0;
        next_freq = 0;
    }
    else
    {
        next_level = parent->get_level() + 1;
        next_freq = parent->get_next_freq(freq_trace);
    }

    std::string cname(froot + omega_fname(direction) + "_" + tname);
    std::string fname(path + cname);
    std::string header(cname + "\n" + hroot + omega_string(direction));
    Ray ray(next_level, next_freq, nhv, jmin, jmax, tracking, r0, cvec,
            gol.get_analysis(), fname, header);
    fname += ".txt";

    if (pt.is_found)
    {
        ray.diag_id = my_id;
        ray.patch_id = patch;
        ray.bundle_id = direction;
        ray.trace(g, m);
        ray.set_backlighter(yback);
        ray.cross_Mesh(m, d, tbl, symmetry, ix);
        if (ntheta == 0) // parallel Rays; one Ray per patch (W/cm2/sr/eV)
            yp[patch] = ray.y;
        else // bundle of Rays per patch (W/cm2/eV)
        {
            double domega; // pmh_2016_1013
            if (direction == INT_PAIR_00) // spherical cap
                domega = cnst::FOUR_PI * pow(sin(dtheta/4.0), 2);
            else // spherical rectangle
                domega = 2.0 * dphi * sin(theta) * sin(dtheta2);
            yp[patch] += ray.y * (domega * ez.cos_angle(ray.v));
        }
    }

    ArrDbl ybroad(nhv);
    utils::convolution(fwhm, hv, ray.y, hv, ybroad);
    if (gol.get_analysis())
    {
        header += "\ndata in W/cm2/sr/eV";
        gol.fit_eval(cname, ybroad);
    }
    else
    {
        if (write_Ray)
            {
                double scale = gol.get_best_scale(cname);
            if (utils::sign_eqt(scale - 1.0, cnst::SCALE_EQT) == 0)
                header += "\ndata in W/cm2/sr/eV";
            else
            {
                header += "\ndata in arbitrary_units";
                ybroad *= scale;
            }
            ybroad.to_file(fname, header);
        }
    }
}

//-----------------------------------------------------------------------------

void Detector::do_patch(Progress *parent, const IntPair &patch,
                        const Grid &g, const Mesh &m, const Database &d,
                        const Table &tbl,
                        const size_t it, const double t, const double dt,
                        const int ntd, const bool peel_onion, Goal &gol)
{
    // set up Progress counter
    int next_level;
    size_t next_freq;
    if (parent == nullptr)
    {
        next_level = 0;
        next_freq = 0;
    }
    else
    {
        next_level = parent->get_level() + 1;
        next_freq = parent->get_next_freq(freq_Ray);
    }
    const std::string SEP("----------------------------------------\n");
    size_t ncount(ntheta == 0 ? 1 : (ntheta-1)*nphi + 1);
    Progress counter(dname + "_Ray", next_level, ncount, next_freq,
                     SEP, std::cout);

    yp[patch].fill(0.0);
    std::string cname(dname + "-yp" + patch_fname(patch));
    std::string fname(path + cname);
    std::string tname(time_fname(it, ntd));
    std::string header(time_string(it, ntd, t));
    header += patch_string(patch);
    do_Ray(&counter, patch, INT_PAIR_00, g, m, d, tbl,
           cname, header, tname, gol);
    counter.advance();

    for (size_t itheta = 1; itheta < ntheta; ++itheta)
        for (size_t iphi = 0; iphi < nphi; ++iphi)
        {
            do_Ray(&counter, patch, IntPair(itheta, iphi), g, m, d, tbl,
                   cname, header, tname, gol);
            counter.advance();
        }

    if (ntheta > 0) // (W/eV); (W/cm2/sr/eV) for ntheta == 0
    {
        if (symmetry == "none")
            yp[patch] *= da;
        else if (symmetry == "spherical") // Eq.(2)
        {
            double darea;
            if (patch.first == 0) // ix == 0 (central circle)
                darea = cnst::PI * pow(dx/2.0, 2);
            else // ix > 0 (circular strip of width dx)
                darea = cnst::TWO_PI * static_cast<double>(patch.first) * pow(dx, 2);
            yp[patch] *= darea;
        }
    }

    #ifndef MPI
    yt[patch] += yp[patch] * dt; // (J/eV); (J/cm2/sr/eV) for ntheta == 0
    #endif

    header = cname + "_" + tname + "\n" + header;
    fname += "_" + tname + ".txt";

    ArrDbl ybroad(nhv);
    utils::convolution(fwhm, hv, yp[patch], hv, ybroad);
    if (gol.get_analysis())
    {
        if (ntheta == 0)
            header += "data in W/cm2/sr/eV";
        else
            header += "data in W/eV";

        if (peel_onion)
        {
            // one Ray per Zone for now
            auto obj = gol.get_objective(patch.first);
            obj->update_best(ybroad, nhv, it);
        }
        else
            gol.fit_eval(cname, ybroad);
    }
    else // postprocessing
    {
        double scale = gol.get_best_scale(cname);
        if (utils::sign_eqt(scale - 1.0, cnst::SCALE_EQT) == 0)
        {
            if (ntheta == 0)
                header += "data in W/cm2/sr/eV";
            else
                header += "data in W/eV";
        }
        else
        {
            header += "data in arbitrary_units";
            ybroad *= scale;
        }
        ybroad.to_file(fname, header);
    }
}

//-----------------------------------------------------------------------------

void Detector::do_patches(Progress *parent,
                          const Grid &g, const Mesh &m, const Database &d,
                          const Table &tbl,
                          const size_t it, const double t, const double dt,
                          const int ntd, Goal &gol)
{
    ys.fill(0.0);

    { // begin block defining Progress diag_counter scope
    #include <patch_counter.inc>
    PatchEnvironment::construct(this, &counter, &g, &m, &d, &tbl, it, t, dt, ntd, &gol);

    #ifdef MPI
    std::queue<PatchID> qin; // passed to TaskPool::q member
    size_t j = 0;
    for (size_t ix = 0; ix < nx; ++ix)
        for (size_t iy = 0; iy < ny; ++iy) // loop over patches
        {
            PatchID pin(ix, iy, j);
            qin.push(pin);
            ++j;
        }
    TaskPool<PatchID, PatchSpectrum> patches(MPI_COMM_WORLD,
        PatchEnvironment::do_patch, PatchEnvironment::space_integ, qin);
    patches.execute();
    #else
    for (size_t ix = 0; ix < nx; ++ix)
        for (size_t iy = 0; iy < ny; ++iy) // loop over patches
        {
            PatchSpectrum pout;
            PatchID pin(ix, iy, 0);
            PatchEnvironment::do_patch(pin, pout);
            PatchEnvironment::space_integ(pout);
        } // end loop over patches
    #endif
    } // end block defining Progress diag_counter scope


/*  original serial code
    for (size_t ix = 0; ix < nx; ++ix)
        for (size_t iy = 0; iy < ny; ++iy)
        {
            IntPair patch(IntPair(ix, iy));
            do_patch(&counter, patch, g, m, d, tbl, it, t, dt, ntd,
                     false, gol);
            if (symmetry == "none")
                ys += yp[patch]; // (W/eV); (W/cm2/sr/eV) for ntheta == 0
            else if (symmetry == "spherical") // Eq.(2)
            {
                if (ntheta == 0)
                {
                    if (ix == 0) // dx = diameter of the central circle
                        ys = yp[patch] / 8.0;
                    else // ring width = r>(ix) - r<(ix) = dx, for ix > 0
                        ys += yp[patch] * xi; // xi * dx = r>(ix) + r<(ix)
                    xi += 1.0; // xi = real(ix)
                }
                else
                    ys += yp[patch];
            }
            counter.advance();
        }
*/

    #ifdef MPI
    MPI_Barrier(MPI_COMM_WORLD);
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if (my_rank == 0)
    {
    #endif

    if (ntheta == 0) // (W/eV); (W/sr/eV) for ntheta == 0
    {
        if (symmetry == "none")
            ys *= da;
        else if (symmetry == "spherical")
            ys *= cnst::TWO_PI * dx * dx; // Eq.(2)
    }

    yst += ys * dt; // (J/eV); (J/sr/eV) for ntheta == 0

    std::string cname(dname + "-ys_" + time_fname(it, ntd));
    std::string fname(path + cname + ".txt");
    std::string header(cname + "\n" + time_string(it, ntd, t));

    ArrDbl ybroad(nhv);
    utils::convolution(fwhm, hv, ys, hv, ybroad);
    if (gol.get_analysis())
    {
        if (ntheta == 0)
            header += "data in W/sr/eV";
        else
            header += "data in W/eV";

        gol.fit_eval(cname, ybroad);
    }
    else
    {
        double scale = gol.get_best_scale(cname);
        if (utils::sign_eqt(scale - 1.0, cnst::SCALE_EQT) == 0)
        {
            if (ntheta == 0)
                header += "data in W/sr/eV";
            else
                header += "data in W/eV";
        }
        else
        {
            header += "data in arbitrary_units";
            ybroad *= scale;
        }
        ybroad.to_file(fname, header);
    }

    #ifdef MPI
    }
    #endif
}

//-----------------------------------------------------------------------------

void Detector::evaluate(const std::vector<size_t> &ndim,
                        const Grid &g, const Mesh &m, const Database &d,
                        const Table &tbl, const size_t jt, const double t,
                        const double dt, const int ntd, Goal &gol)
{
    if (ntheta != 0)
    {   // only parallel Rays are allowed in analysis with spherical symmetry
        std::cerr << "Error: ntheta is not zero in Detector.evaluate()"
                  << std::endl;
        exit(EXIT_FAILURE);
    }
    size_t izone = utils::one_to_two(ndim, jt).first;

    if (izone == Zone::BOUNDING_ZONE)
    {
        // done searching; retrieve best icase for each Zone
        size_t nzones = ndim.size();
        std::vector<size_t> indx(nzones);
        size_t icase;
        std::pair<size_t, size_t> pr;
        for (size_t iz = 1; iz < nzones; ++iz)
        {
            icase = gol.get_objective(iz-1)->get_best_case();
            pr = utils::one_to_two(ndim, icase);
            if (pr.first != iz)
            {
                std::cerr << "Error in Detector::evaluate: "
                          << "Zone ID mismatch: " << pr.first << " " << iz
                          << std::endl;
                exit(EXIT_FAILURE);
            }
            indx.at(iz) = pr.second;
        }

        // no Rays are needed through the bounding Zone (#0), as
        // it only has this one and only case (vacuum, typically)
        indx.at(Zone::BOUNDING_ZONE) = 0;

        // compute product-based index it for the best fits from indx and ndim,
        // as if it had come from a search with symmetry == "none"
        gol.set_best_case(utils::many_to_one(ndim, indx));
    }
    else // evaluate the Ray through izone, which is not the bounding Zone
    {
        size_t iz = izone - 1; // innermost Zone is #1 (#0 is bounding Zone)
        IntPair patch(IntPair(iz, 0)); // only one Ray per Zone for now
        do_patch(nullptr, patch, g, m, d, tbl, jt, t, dt, ntd, true, gol);
    }
}

//-----------------------------------------------------------------------------

std::string Detector::patch_string(const IntPair &patch) const
{
    const size_t &ix = patch.first;
    const size_t &iy = patch.second;

    double x, y;
    if (symmetry == "none")
    {
        x = dx * (static_cast<double>(ix) + 0.5);
        y = dy * (static_cast<double>(iy) + 0.5);
    }
    else
    {
        x = dx * static_cast<double>(ix);
        y = 0.0;
    }

    return "ix " + utils::int_to_string(ix, ' ', nxd) +
           utils::double_to_string(x) + " cm\n" +
           "iy " + utils::int_to_string(iy, ' ', nyd) +
           utils::double_to_string(y) + " cm\n";
}

//-----------------------------------------------------------------------------

std::string Detector::patch_fname(const IntPair &patch) const
{
    return "_ix" + utils::int_to_string(patch.first, '0', nxd)
         + "_iy" + utils::int_to_string(patch.second, '0', nyd);
}

//-----------------------------------------------------------------------------

std::string Detector::omega_string(const IntPair &direction) const
{
    const size_t &it = direction.first;
    const size_t &ip = direction.second;

    double theta = utils::degrees(dtheta * static_cast<double>(it));
    double phi = utils::degrees(dphi * static_cast<double>(ip));

    return "it " + utils::int_to_string(it, ' ', nthetad)
         + utils::double_to_string(theta) + " deg\n"
         + "ip " + utils::int_to_string(ip, ' ', nphid)
         + utils::double_to_string(phi) + " deg";
}

//-----------------------------------------------------------------------------

std::string Detector::omega_fname(const IntPair &direction) const
{
    return "_it" + utils::int_to_string(direction.first, '0', nthetad)
         + "_ip" + utils::int_to_string(direction.second, '0', nphid);
}

//-----------------------------------------------------------------------------

void Detector::yt_to_files(Progress *parent, Goal &gol, const Hydro &h)
{
    #include <patch_counter.inc>
    std::string header, pname, cname, fname;
    size_t nintervals = h.get_nintervals();
    int ntd = h.get_ntd();
    for (size_t ix = 0; ix < nx; ++ix)
        for (size_t iy = 0; iy < ny; ++iy)
        {
            const IntPair patch(ix, iy);
            pname = "_ix" + utils::int_to_string(ix, '0', nxd)
                  + "_iy" + utils::int_to_string(iy, '0', nyd);
            cname = dname + "-yt" + pname;
            header = cname + "\n" + patch_string(patch);
            if (ntheta == 0)
                header += "data in J/cm2/sr/eV";
            else
                header += "data in J/eV";

            fname = path + cname + ".txt";
            ArrDbl ybroad(nhv);
            std::string cnm(dname + "-yp" + patch_fname(patch));
            for (size_t j = 0; j < nintervals; ++j) // loop over time
            {
                size_t it = h.time_index_at(j);
                std::string tnm(time_fname(it, ntd));
                std::string fnm(path + cnm + "_" + tnm + ".txt");
                ArrDbl ypatch(nhv);
                utils::load_array(fnm, nhv, 0, nhv-1, ypatch);
                double dt = h.dt_at(it);
                ybroad += ypatch * dt; // already convolved with fwhm
            }
            utils::convolution(fwhm, hv, yt[patch], hv, ybroad);
            if (!gol.get_analysis()) ybroad.to_file(fname, header);
            counter.advance();
        }
}

//-----------------------------------------------------------------------------

std::string time_string(const size_t it, const int ntd, const double t)
{
    return "time " + utils::int_to_string(it, ' ', ntd) + " "
           + utils::double_to_string(t) + " s\n";
}

//-----------------------------------------------------------------------------

std::string time_fname(const size_t it, const int ntd)
{return "time" + utils::int_to_string(it, '0', ntd);}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Detector &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

//  end Detector.cpp
