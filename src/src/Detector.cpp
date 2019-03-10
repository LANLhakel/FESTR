/**
 * @file Detector.cpp
 * @brief Detector objects
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 28 January 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*=============================================================================

pmh_2015_0210
pmh_2015_0312

=============================================================================*/

#include "Detector.h"
#include "Node.h"
#include "utilities.h"
#include <cstdlib>
#include <iostream>

//-----------------------------------------------------------------------------

#ifdef MPIYES
#include "ReducePool.h"

/// Its address is passed to ReducePool::initialize_partial function pointer
void parallel_init_sum(const int nin, double *vpartial)
{
    size_t n(static_cast<size_t>(nin));
    #include "ArrDblLoop.inc"
    {vpartial[i] = 0.0;}
}

//-----------------------------------------------------------------------------

/// Encapsulates "globals" for MPI parallelization using ReducePool
namespace TimeIntegrationEnvironment
{
    std::string path;
    std::string cnm;
    int ntd;
    const Hydro *h;

    /// TimeIntegrationEnvironment "constructor"
    void construct(std::string path_in, std::string cnm_in, int ntd_in,
                   const Hydro *h_in)
    {
        path = path_in;
        cnm = cnm_in;
        ntd = ntd_in;
        h = h_in;
    }

    /// Its address is passed to ReducePool::perform_task function pointer
    void parallel_task_sum(const size_t &it, const int nin, double *vpartial)
    {
        size_t n(static_cast<size_t>(nin));
        std::string tnm(time_fname(it, ntd));
        std::string fnm(path + cnm + "_" + tnm + ".txt");
        ArrDbl ysint(n);
        utils::load_array(fnm, n, 0, n-1, ysint);
        double dt = h->dt_at(it);
        #include "ArrDblLoop.inc"
        {vpartial[i] += ysint.at(i) * dt;} // already convolved with fwhm
    }
}

//-----------------------------------------------------------------------------

/// Facilitates result extraction from MPI parallelization using ReducePool
namespace OutputArrayEnvironment
{
    ArrDbl *y;

    /// OutputArrayEnvironment "constructor"
    void construct(ArrDbl *y_in) {y = y_in;}

    /// Its address is passed to ReducePool::process_results function pointer
    void copy_output(const int nin, const double *vfinal)
    {
        size_t n(static_cast<size_t>(nin));
        #include "ArrDblLoop.inc"
        {(*y).at(i) = vfinal[i];}
    }
}

#endif // #ifdef MPIYES

//-----------------------------------------------------------------------------

const size_t Detector::NPT = 4;

//-----------------------------------------------------------------------------

Detector::Detector(void):
    freq_patch(0), freq_Ray(0), freq_trace(0),
    dname("no_name"), path("no_path"), symmetry("none"), my_id(-1),
    rc(), ro(), rx(), ry(), ex(), ey(), ez(), bx(), by(), bz(),
    xr(), yr(), zr(), dx(0.0), dy(0.0), da(0.0),
    ux(), uy(), nhv(0), hv(), hvmin(0.0), hvmax(0.0),
    jmin(0), jmax(0), fwhm(-1.0), back_type("none"), back_value(-9.0),
    tracking(false), nx(0), ny(0), nxd(0), nyd(0),
    theta_max(0.0), ntheta(0), nphi(0), nthetad(0), nphid(0),
    dtheta(0.0), dphi(0.0), dtheta2(0.0), gdet(), p(), yp(), ys(), yt(), yst()
    {}

//-----------------------------------------------------------------------------

Detector::Detector(const size_t freq_patch_in,
                   const size_t freq_Ray_in, const size_t freq_trace_in,
                   const std::string &dname_in, const std::string &path_in,
                   const std::string &dbase_path, const std::string &sym_in,
                   const int my_id_in, const Vector3d & rc_in,
                   const Vector3d &rx_in, const Vector3d &ry_in,
                   const double dx_in, const double dy_in,
                   const size_t nhv_in,
                   const double hv_min, const double hv_max,
                   const double fwhm_in, const Vector3d &sc,
                   const std::string &back_type_in,
                   const double back_value_in, const bool tracking_in):
    freq_patch(freq_patch_in), freq_Ray(freq_Ray_in),
    freq_trace(freq_trace_in),
    dname(dname_in), path(path_in), symmetry(sym_in), my_id(my_id_in),
    rc(rc_in), ro(), rx(rx_in), ry(ry_in), ex(), ey(), ez(), bx(), by(), bz(),
    xr(), yr(), zr(), dx(dx_in), dy(dy_in), da(dx_in*dy_in),
    ux(), uy(), nhv(0), hv(), hvmin(hv_min), hvmax(hv_max),
    jmin(nhv_in), jmax(0), fwhm(fwhm_in), back_type(back_type_in),
    back_value(back_value_in), tracking(tracking_in),
    nx(0), ny(0), nxd(0), nyd(0), theta_max(0.0),
    ntheta(0), nphi(0), nthetad(0), nphid(0), dtheta(0.0), dphi(0.0),
    dtheta2(0.0), gdet(), p(), yp(), ys(), yt(), yst()
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
    size_t j;
    double e;
    for (size_t ihv = 0; ihv < nhv_in; ++ihv)
    {
        infile >> j >> e;
        bool min_true(e >= hvmin);
        bool max_true(e <= hvmax);
        if (min_true && max_true) hv.push_back(e);
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

    nhv = jmax - jmin + 1;
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
        if (back_type == "blackbody")
            out_back << utils::double_to_string(utils::planckian(hv.at(ihv), back_value))
                     << std::endl;
        else
            out_back << utils::double_to_string(back_value) << std::endl;
    }
    out_hv.close();
    out_hv.clear();
    out_back.close();
    out_back.clear();

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

    #ifndef MPI
    ArrDbl y0;
    y0.assign(nhv, 0.0);
    #endif

    for (size_t iy = 0; iy < ny; ++iy)
        for (size_t ix = 0; ix < nx; ++ix)
        {
            IntPair patch(ix, iy);
            #ifndef MPI
            yt.insert(SpecPatch::value_type(patch, y0));
            #endif
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
    bz = (rc - sc).unit();
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
}

//-----------------------------------------------------------------------------

Detector::~Detector(void) {}

//-----------------------------------------------------------------------------

double Detector::abs_diff(const Detector &o) const {return rc.abs_diff(o.rc);}

//-----------------------------------------------------------------------------

std::string Detector::to_string(void) const
{
    std::string s(dname + "\nrc" + rc.to_string());
    s += "\nrx" + rx.to_string() + "\nry" + ry.to_string();
    s += "\ndx" + utils::double_to_string(dx);
    s += "\ndy" + utils::double_to_string(dy);
    s += "\nfwhm" + utils::double_to_string(fwhm);
    s += "\nbacklighter " + back_type + utils::double_to_string(back_value);
    s += "\ntracking " + utils::bool_to_string(tracking);
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

std::string Detector::get_dname(void) const {return dname;}

//-----------------------------------------------------------------------------

std::string Detector::get_path(void) const {return path;}

//-----------------------------------------------------------------------------

std::string Detector::get_symmetry(void) const {return symmetry;}

//-----------------------------------------------------------------------------

int Detector::get_my_id(void) const {return my_id;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_rc(void) const {return rc;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ro(void) const {return ro;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_rx(void) const {return rx;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ry(void) const {return ry;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ex(void) const {return ex;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ey(void) const {return ey;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ez(void) const {return ez;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_bx(void) const {return bx;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_by(void) const {return by;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_bz(void) const {return bz;}

//-----------------------------------------------------------------------------

size_t Detector::get_nhv(void) const {return nhv;}

//-----------------------------------------------------------------------------

std::vector<double> Detector::get_hv(void) const {return hv;}

//-----------------------------------------------------------------------------

size_t Detector::get_jmin(void) const {return jmin;}

//-----------------------------------------------------------------------------

double Detector::get_hvmin(void) const {return hvmin;}

//-----------------------------------------------------------------------------

size_t Detector::get_jmax(void) const {return jmax;}

//-----------------------------------------------------------------------------

double Detector::get_hvmax(void) const {return hvmax;}

//-----------------------------------------------------------------------------

double Detector::get_fwhm(void) const {return fwhm;}

//-----------------------------------------------------------------------------

std::string Detector::get_back_type(void) const {return back_type;}

//-----------------------------------------------------------------------------

double Detector::get_back_value(void) const {return back_value;}

//-----------------------------------------------------------------------------

bool Detector::get_tracking(void) const {return tracking;}

//-----------------------------------------------------------------------------

size_t Detector::get_nx(void) const {return nx;}

//-----------------------------------------------------------------------------

size_t Detector::get_ny(void) const {return ny;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_vertex(const size_t i) const
{return gdet.get_node(i).getr();}

//-----------------------------------------------------------------------------

Vector3d Detector::get_ux(void) const {return ux;}

//-----------------------------------------------------------------------------

Vector3d Detector::get_uy(void) const {return uy;}

//-----------------------------------------------------------------------------

double Detector::compute_theta_max(const Vector3d &sc, const double sr)
{
    return asin( sr / (rc-sc).norm() );
}

//-----------------------------------------------------------------------------

double Detector::get_theta_max(void) const {return theta_max;}

//-----------------------------------------------------------------------------

size_t Detector::get_ntheta(void) const {return ntheta;}

//-----------------------------------------------------------------------------

size_t Detector::get_nphi(void) const {return nphi;}

//-----------------------------------------------------------------------------

double Detector::get_dtheta(void) const {return dtheta;}

//-----------------------------------------------------------------------------

double Detector::get_dtheta2(void) const {return dtheta2;}

//-----------------------------------------------------------------------------

double Detector::get_dphi(void) const {return dphi;}

//-----------------------------------------------------------------------------

Vector3d Detector::local_to_global(const Vector3d &v) const
{return Vector3d( xr * v, yr * v, zr * v );}

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
    const Face *f = m.get_zone(Zone::BOUNDING_ZONE)->get_face(0);
    FaceID fid(Zone::BOUNDING_ZONE, -3);
    RetIntercept pt = f->intercept(g, r0, cvec, EQT, fid);

    // set up Progress counter
    int next_level;
    size_t next_freq;
    if (parent == NULL)
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
        ray.set_backlighter(back_type, back_value, hv);
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
    if (parent == NULL)
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
            Objective *obj =
                const_cast<Objective *>(gol.get_objective(patch.first));
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
    #include "patch_counter.inc"
    ys.fill(0.0);
    double xi(0.0);
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

    if (ntheta == 0) // (W/eV); (W/sr/eV) for ntheta == 0
    {
        if (symmetry == "none")
            ys *= da;
        else if (symmetry == "spherical")
            ys *= cnst::TWO_PI * dx * dx; // Eq.(2)
    }

    #ifndef MPI
    yst += ys * dt; // (J/eV); (J/sr/eV) for ntheta == 0
    #endif

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
        do_patch(NULL, patch, g, m, d, tbl, jt, t, dt, ntd, true, gol);
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

void Detector::yt_to_files(Progress *parent, Goal &gol,
                           const size_t nt, const int ntd, const Hydro &h)
{
    #ifdef MPIYES
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    size_t n(nt);
    std::vector<size_t> vin(n); // passed to ReducePool::v member
    #include "ArrDblLoop.inc"
    {vin.at(i) = i;}
    #else
    (void)(nt);
    (void)(ntd);
    (void)(h);
    #endif

    #include "patch_counter.inc"
    std::string header, pname, cname, fname;
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

            #ifdef MPIYES
            std::string cnm(dname + "-yp" + patch_fname(patch));
            TimeIntegrationEnvironment::construct(path, cnm, ntd, &h);
            OutputArrayEnvironment::construct(&ybroad);
            ReducePool<size_t, double> time_integ(MPI_COMM_WORLD,
                parallel_init_sum,
                TimeIntegrationEnvironment::parallel_task_sum,
                OutputArrayEnvironment::copy_output,
                vin, static_cast<int>(nhv), MPI_DOUBLE, MPI_SUM);
            time_integ.execute();
/*
            // original serial code
            std::string cnm(dname + "-yp" + patch_fname(patch));
            for (size_t it = 0; it < nt; ++it) // loop over time steps
            {
                std::string tnm(time_fname(it, ntd));
                std::string fnm(path + cnm + "_" + tnm + ".txt");
                ArrDbl ypatch(nhv);
                load_array(fnm, nhv, 0, nhv-1, ypatch);
                double dt = h.dt_at(it);
                ybroad += ypatch * dt; // already convolved with fwhm
            }
*/
            #else // serial path
            utils::convolution(fwhm, hv, yt[patch], hv, ybroad);
            #endif

            if (!gol.get_analysis())
                #ifdef MPIYES
                if (my_rank == 0)
                #endif
                ybroad.to_file(fname, header);

            counter.advance();
        }
}

//-----------------------------------------------------------------------------

void Detector::yst_using_mpi(const size_t nt, const int ntd, const Hydro &h)
{
    // its serial counterpart is in Detector::do_patches()
    #ifdef MPIYES
    std::string cnm(dname + "-ys");
    TimeIntegrationEnvironment::construct(path, cnm, ntd, &h);
    OutputArrayEnvironment::construct(&yst);
    size_t n(nt);
    std::vector<size_t> vin(n); // passed to ReducePool::v member
    #include "ArrDblLoop.inc"
    {vin.at(i) = i;}
    ReducePool<size_t, double> time_integ(MPI_COMM_WORLD,
        parallel_init_sum,
        TimeIntegrationEnvironment::parallel_task_sum,
        OutputArrayEnvironment::copy_output,
        vin, static_cast<int>(nhv), MPI_DOUBLE, MPI_SUM);
    time_integ.execute();

    #else
    (void)(nt);
    (void)(ntd);
    (void(h));
/*
    // original serial code
    std::string cnm(dname + "-ys");
    for (size_t it = 0; it < nt; ++it)
    {
        std::string tnm(time_fname(it, ntd));
        std::string fnm(path + cnm + "_" + tnm + ".txt");
        ArrDbl ysint(nhv);
        load_array(fnm, nhv, 0, nhv-1, ysint);
        double dt = h.dt_at(it);
        yst += ysint * dt; // already convolved with fwhm
    }
*/
    #endif
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

// end Detector.cpp
