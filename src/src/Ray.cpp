/**
 * @file Ray.cpp
 * @brief Ray carrying a spectrum and its own current position and direction
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 24 December 2014\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Ray.h"
#include "utilities.h"
#include "Face.h"
#include "Progress.h"
#include <cmath>

//-----------------------------------------------------------------------------

Waypoint::Waypoint(void): outface(), inface(), hitpt() {}

//-----------------------------------------------------------------------------

Waypoint::Waypoint(const Vector3d &hp):
    outface(Face::BOUNDING_SPHERE), inface(Face::BOUNDING_SPHERE), hitpt(hp) {}

//-----------------------------------------------------------------------------

Waypoint::Waypoint(const FaceID &oface, const FaceID &iface,
                   const Vector3d &hp):
    outface(oface), inface(iface), hitpt(hp) {}

//-----------------------------------------------------------------------------

void Ray::init(const size_t nin, const Vector3d &rin)
{
    em.assign(nin, 0.0);
    ab.assign(nin, 0.0);
    sc.assign(nin, 0.0);
    Waypoint w(rin);
    wpt.push(w);
}

//-----------------------------------------------------------------------------

Ray::Ray(void): level(0), freq(0), n(0), jmin(0), jmax(0), nzones(0), nzd(0),
    iz(0), distance(0.0), tracking(false), froot(""), hroot(""),
    diag_id(-1), patch_id(0, 0), bundle_id(0, 0),
    r(), v(), analysis(false), zid(Zone::BOUNDING_ZONE), y(), wpt(),
    ite(0), itr(0), ine(0), em(), ab(), sc() {}

//-----------------------------------------------------------------------------

Ray::Ray(const int level_in, const size_t freq_in, const size_t nin,
         const size_t jmin_in, const size_t jmax_in, const bool tracking_in,
         const Vector3d &rin, const Vector3d &vin, const bool analysis_in,
         const std::string &froot_in, const std::string &hroot_in):
    level(level_in), freq(freq_in), n(nin), jmin(jmin_in), jmax(jmax_in),
    nzones(0), nzd(0), iz(0), distance(0.0), tracking(tracking_in),
    froot(froot_in), hroot(hroot_in), diag_id(-1), patch_id(0, 0),
    bundle_id(0, 0), r(rin), v(vin), analysis(analysis_in),
    zid(Zone::BOUNDING_ZONE), y(), wpt(), ite(0), itr(0), ine(0),
    em(), ab(), sc()
{
    y.assign(nin, 0.0);
    init(nin, rin);
}

//-----------------------------------------------------------------------------

Ray::Ray(const int level_in, const size_t freq_in, const size_t nin,
         const size_t jmin_in, const size_t jmax_in, const bool tracking_in,
         const Vector3d &rin, const Vector3d &vin, const bool analysis_in,
         const ArrDbl &yin,
         const std::string &froot_in, const std::string &hroot_in):
    level(level_in), freq(freq_in), n(nin), jmin(jmin_in), jmax(jmax_in),
    nzones(0), nzd(0), iz(0), distance(0.0), tracking(tracking_in),
    froot(froot_in), hroot(hroot_in), diag_id(-1), patch_id(0, 0),
    bundle_id(0, 0), r(rin), v(vin), analysis(analysis_in),
    zid(Zone::BOUNDING_ZONE), y(yin), wpt(), ite(0), itr(0), ine(0),
    em(), ab(), sc() {init(nin, rin);}

//-----------------------------------------------------------------------------

Ray::~Ray(void) {}

//-----------------------------------------------------------------------------

size_t Ray::size(void) const {return n;}

//-----------------------------------------------------------------------------

size_t Ray::get_nzones(void) const {return nzones;}

//-----------------------------------------------------------------------------

bool Ray::get_tracking(void) const {return tracking;}

//-----------------------------------------------------------------------------

double Ray::abs_diff(const Ray &o) const
{
    return r.abs_diff(o.r) + v.abs_diff(o.v) + y.abs_diff(o.y);
}

//-----------------------------------------------------------------------------

void Ray::set_backlighter(const std::string &back_type,
                          const double back_value, std::vector<double> &hv)
{
    if (back_type == "blackbody") // back_value is blackbody temperature in eV
        for (size_t i = 0; i < hv.size(); ++i)
            y.at(i) = utils::planckian(hv.at(i), back_value);

    else // back_type == "flat", back_value is uniform specific intensity
        y.fill(back_value);
}

//-----------------------------------------------------------------------------

void Ray::trace(const Grid &g, const Mesh &m)
{
    Progress counter("Ray_trace", level, 0, freq, "", std::cout);
    counter.advance(); // final b.Sphere waypoint already pushed onto RayStack
    RetIntercept intrcpt;
    Waypoint w;
    w.outface = wpt.top().outface;
    while (true)
    {
        if (tracking) ++nzones;
        const Zone *z = m.get_zone(zid);
        intrcpt = z->hit(g, r, v, w.outface);
        w.hitpt = intrcpt.w;
        w.inface = intrcpt.fid;
        w.outface = m.next_face(g, intrcpt);
        r = w.hitpt;
        if (w.inface == Face::BOUNDING_SPHERE) break;
        zid = w.outface.my_zone;
        wpt.push(w);
        counter.advance();
    }
    nzd = utils::ndigits(nzones);
    v.reverse();
}

//-----------------------------------------------------------------------------

void Ray::transport(const double ct) // transport this->y across *this
{
    // Optically-thin formula used for optical depth < 2.0e-10
    const double TR_THIN = exp(-2.0e-10);
    #include "ArrDblLoop.inc"
    {
        double op = ab.at(i) + sc.at(i); // opacity
        double tr = exp( - op * ct );    // transmission
        double se;                       // self_emission
        if (tr > TR_THIN)
            se = em.at(i) * ct; // optically thin limit in 1-D
        else
            se = (1.0 - tr) * em.at(i) / op; // general 1-D solution
        y.at(i) = y.at(i) * tr + se; // transmitted_backlighter + self_emission
    }
}

//-----------------------------------------------------------------------------

void Ray::cross_Zone(const Zone *z, const Database &d, const Table &tbl,
                     const std::string &symmetry, const size_t ix,
                     const int ndmesh)
{   // assumes that this->zid has already been set; e.g., in cross_Mesh()
    const Waypoint &w = wpt.top();
    const Vector3d r_old = r;
    r = w.hitpt;
    const double ct = (r - r_old).norm(); // chord length across current Zone
    Zone *zz = const_cast<Zone *>(z);
    if (d.get_tops_cmnd() == "none")
    {
        zz->load_spectra(d, tbl, ite, itr, ine, symmetry, ix, analysis,
                         jmin, jmax, em, ab, sc);
        transport(ct);
    }
    wpt.pop();

    if (tracking)
    {
        distance += ct;
        std::string izlabel("iz" + utils::int_to_string(iz, '0', nzd));
        std::string izstring("iz " + utils::int_to_string(iz, ' ', nzd));
        std::string header(hroot);
        utils::replace_in_string(header, "\n", "_"+izlabel+"\n");
        header += "\n" + izstring + utils::double_to_string(distance) + " cm";
        header += "\nZoneID " + utils::int_to_string(z->get_id(), ' ', ndmesh);
        header += "\ndata in W/cm2/sr/eV";
        std::string fname(froot + "_" + izlabel + ".txt");
        y.to_file(fname, header);
        ++iz;
    }
}

//-----------------------------------------------------------------------------

void Ray::cross_Mesh(const Mesh &m, const Database &d, const Table &tbl,
                     const std::string &symmetry, const size_t ix)
{
    Progress counter("Ray_transport", level, wpt.size(), freq, "", std::cout);
    while ( !wpt.empty() )
    {
        zid = wpt.top().outface.my_zone;
        cross_Zone(m.get_zone(zid), d, tbl, symmetry, ix,
                   utils::ndigits(m.size()));
        counter.advance();
    }
}

//-----------------------------------------------------------------------------

std::string Ray::to_string(void) const
{
    std::string s(r.to_string() + v.to_string() + "\n");
    s += utils::int_to_string(zid, ' ', cnst::INT_WIDTH) + "\n"
       + utils::int_to_string(n, ' ', cnst::INT_WIDTH);
    if (n > 0) s += "\n" + y.to_string();
    return s;
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Ray &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

// end Ray.cpp
