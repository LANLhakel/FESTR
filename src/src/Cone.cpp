/**
 * @file Cone.cpp
 * @brief Conical ribbons for 2-D RZ geometry (derived from class Face)
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 14 May 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Cone.h"
#include "utilities.h"
#include <cmath>

//-----------------------------------------------------------------------------

// X: node index local to *this; range: 0 through size()-1
#define NODE(X)     g.get_node(get_node((X)))
#define POINT(X)    NODE((X)).getr()
#define VELOCITY(X) NODE((X)).getv()

//-----------------------------------------------------------------------------

const double Cone::SMALL = 1.0e-8; // in centimeters

//-----------------------------------------------------------------------------

Cone::Cone(void): Face() {}

//-----------------------------------------------------------------------------

Cone::Cone(const size_t my_zone_in, const short int my_id_in):
    Face(my_zone_in, my_id_in) {}

//-----------------------------------------------------------------------------

Cone::Cone(std::ifstream &istr) {load(istr);}

//-----------------------------------------------------------------------------

Cone::~Cone(void) {}

//-----------------------------------------------------------------------------

bool Cone::is_curved(const Grid &g) const
{
    return fabs( POINT(1).gety() - POINT(0).gety() ) > SMALL;
}

//-----------------------------------------------------------------------------

std::string Cone::to_string(void) const
{
    return "Cone\n" + Face::to_string();
}

//-----------------------------------------------------------------------------

void Cone::load(std::ifstream &istr)
{
    load_face(istr, 2); // every Cone contains two Nodes (in the rz plane)
}

//-----------------------------------------------------------------------------

Vector3d Cone::area2_normal_center(const Grid &g, Vector3d &c) const
{   // lateral area of a frustum of a rotational cone
    const Vector3d a = POINT(0);
    const Vector3d b = POINT(1);
    c = (a + b) / 2.0;
    const Vector3d v = b - a;
    double ra = a.getx();
    double rb = b.getx();
    double dr = rb - ra;
    double dz = b.gety() - a.gety();
    double s = sqrt(dr*dr + dz*dz);
    double area2 = cnst::TWO_PI * (ra + rb) * s;
    return v.right_normal() * area2;
}

//-----------------------------------------------------------------------------

Vector3d Cone::normal(const Grid &g) const
{
    Vector3d c;
    return area2_normal_center(g, c).normalize();
}

//-----------------------------------------------------------------------------

double Cone::area(const Grid &g) const
{
    Vector3d c;
    return area2_normal_center(g, c).norm() / 2.0;
}

//-----------------------------------------------------------------------------

double Cone::distance(const Grid &g, const Vector3d &w) const
{   // pmh_2015_0508
    const Vector3d d = w.get_rz() - subpoint(g, w).get_rz();
    const Vector3d n = normal(g);
    return d * n;
}

//-----------------------------------------------------------------------------

Vector3d Cone::subpoint(const Grid &g, const Vector3d &w) const
{   // pmh_2015_0508
    const double wx = w.getx();
    const double wy = w.gety();
    const double wz = w.getz();
    const double wr = sqrt(wx*wx + wy*wy);
    const double phi = atan2(wy, wx);

    const Vector3d a = POINT(0);
    const Vector3d b = POINT(1);
    const double ra = a.getx();
    const double za = a.gety();
    const double dr = b.getx() - ra; // Eq.(3)
    const double dz = b.gety() - za; // Eq.(2)

    double numerator = (wr - ra) * dr  +  (wz - za) * dz;
    double denominator = dr*dr + dz*dz;
    double t = numerator / denominator; // Eq.(13)

    double rs = ra + t*dr;
    return Vector3d(rs*cos(phi), rs*sin(phi), za + t*dz);
}

//-----------------------------------------------------------------------------

bool Cone::contains(const Grid &g, const Vector3d &w) const
{   // pmh_2015_0508, page 5
    const Vector3d v(w.get_rz());
    return (v - POINT(0)) * (v - POINT(1)) <= 1.0e-19;
}

//-----------------------------------------------------------------------------

RetIntercept Cone::intercept(const Grid &g, const Vector3d &p,
                             const Vector3d &u, const double eqt,
                             const FaceID &fid) const
{
    RetIntercept rv;
    rv.fid = FaceID(get_my_zone(), get_my_id());
    const Vector3d atail = POINT(0);
    const double za = atail.gety();
    const double pz = p.getz();
    const double uz = u.getz();

    if (is_flat(g)) // see Polygon::intercept (pmh_2014_1125) with n = zhat
    {
        if (rv.fid == fid  ||  fabs(uz) < Vector3d::get_small())
        {
            const double BIG = -Vector3d::get_big();
            rv.t = BIG;
            rv.w = Vector3d(BIG, BIG, BIG);
            rv.is_found = false;
        }
        else
        {
            rv.t = (za - pz) / uz;
            rv.w = p  +  u * rv.t;
            rv.is_found = utils::sign_eqt(rv.t, eqt) == 1 && contains(g, rv.w);
        }

        return rv;
    }
    else // pmh_2015_0508
    {
        const Vector3d bhead = POINT(1);
        const double ra = atail.getx();
        const double px = p.getx();
        const double py = p.gety();
        const double dr = bhead.getx() - ra; // Eq.(3)
        const double dz = bhead.gety() - za; // Eq.(2)
        const double ux = u.getx();
        const double uy = u.gety();
        const double rp2 = px*px + py*py; // Eq.(6)
        const double zd = pz - za; // Eq.(7)
        const double dz2 = dz * dz;
        const double ff = dz2 * (px*ux + py*uy); // Eq.(8)
        const double gg = dz * ra * dr; // Eq.(9)
        const double hh = gg  +  zd * dr * dr; // Eq.(11)
        const double uzdr = uz * dr;

        // Eq.(12)
        const double a = dz2 * (ux*ux + uy*uy)  -  uzdr * uzdr;
        const double b = 2.0 * (ff  -  uz * hh);
        const double c = dz2 * (rp2 - ra*ra)  -  zd * (gg + hh);
        #include "choose_root.inc" // contains: return rv;
    }
}

//-----------------------------------------------------------------------------

Vector3d Cone::velocity(const Grid &g, const Vector3d &w) const
{
    Vector3d wrz(w.get_rz());
    const double wx = w.getx();
    const double wy = w.gety();
    const double phi = atan2(wy, wx);

    const double VEC_SMALL = Vector3d::get_small();
    Vector3d u;
    double d;
    double s = 0.0;
    for (size_t i = 0; i < 2; ++i)
    {
        d = (POINT(i) - wrz).norm();
        if (d < VEC_SMALL)
        {
            u = VELOCITY(i);
            s = 1.0;
            break;
        }
        d = 1.0 / d;
        s += d;
        u += d * VELOCITY(i);
    }
    u /= s;
    double ux = u.getx() * cos(phi);
    double uy = u.getx() * sin(phi);
    return Vector3d(ux, uy, u.gety());
}

//-----------------------------------------------------------------------------

#undef VELOCITY
#undef POINT
#undef NODE

//-----------------------------------------------------------------------------

// end Cone.cpp
