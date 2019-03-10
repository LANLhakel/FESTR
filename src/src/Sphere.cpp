/**
 * @file Sphere.cpp
 * @brief Spherical shells (derived from class Face)
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 21 November 2014\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Sphere.h"
#include "utilities.h"
#include <cmath>

//-----------------------------------------------------------------------------

// X: node index local to *this; range: 0 through size()-1
#define NODE(X)     g.get_node(get_node((X)))
#define POINT(X)    NODE((X)).getr()
#define VELOCITY(X) NODE((X)).getv()

//-----------------------------------------------------------------------------

Sphere::Sphere(void): Face(), r(0.0), v(0.0) {}

//-----------------------------------------------------------------------------

Sphere::Sphere(const size_t my_zone_in, const short int my_id_in):
    Face(my_zone_in, my_id_in), r(0.0), v(0.0) {}

//-----------------------------------------------------------------------------

Sphere::Sphere(const size_t my_zone_in, const short int my_id_in,
               const double rin):
    Face(my_zone_in, my_id_in), r(rin), v(0.0) {}

//-----------------------------------------------------------------------------

Sphere::Sphere(const size_t my_zone_in, const short int my_id_in,
               const double rin, const double vin):
    Face(my_zone_in, my_id_in), r(rin), v(vin) {}

//-----------------------------------------------------------------------------

Sphere::Sphere(std::ifstream &istr): Face(), r(0.0), v(0.0) {load(istr);}

//-----------------------------------------------------------------------------

Sphere::~Sphere(void) {}

//-----------------------------------------------------------------------------

bool Sphere::is_curved(const Grid &g) const
{
    (void)(g);
    return true;
}

//-----------------------------------------------------------------------------

void Sphere::setr(const double rin) {r = rin;}

//-----------------------------------------------------------------------------

double Sphere::getr(void) const {return fabs(r);}

//-----------------------------------------------------------------------------

void Sphere::setv(const double vin) {v = vin;}

//-----------------------------------------------------------------------------

double Sphere::getv(void) const {return v;}

//-----------------------------------------------------------------------------

void Sphere::setn(const int nin)
{
    double radius = fabs(r);
    if (nin > 0)
        r = radius;
    else if (nin < 0)
        r = -radius;
    else
        r = 0.0;
}

//-----------------------------------------------------------------------------

int Sphere::getn(void) const
{
    if (r > 0.0)
        return 1;
    else if (r < 0.0)
        return -1;
    else
        return 0;
}

//-----------------------------------------------------------------------------

Vector3d Sphere::center_position(const Grid &g) const
{
    return POINT(0);
}

//-----------------------------------------------------------------------------

Vector3d Sphere::center_velocity(const Grid &g) const
{
    return VELOCITY(0);
}

//-----------------------------------------------------------------------------

std::string Sphere::to_string(void) const
{
    return "Sphere\n" + Face::to_string() + "\n" +
           utils::double_to_string(r) + utils::double_to_string(v);
}

//-----------------------------------------------------------------------------

void Sphere::load(std::ifstream &istr)
{
    load_face(istr, 1); // every Sphere contains one Node (its center)
    istr >> r >> v;
}

//-----------------------------------------------------------------------------

Vector3d Sphere::area2_normal_center(const Grid &g, Vector3d &c) const
{
    c.set0();
    return Vector3d(2.0 * getn() * area(g), 0.0, 0.0);
}

//-----------------------------------------------------------------------------

Vector3d Sphere::normal(const Grid &g) const
{
    (void)(g);
    const double x = static_cast<double>(getn());
    return Vector3d(x, 0.0, 0.0);
}

//-----------------------------------------------------------------------------

double Sphere::area(const Grid &g) const
{
    (void)(g);
    return cnst::FOUR_PI * r * r;
}

//-----------------------------------------------------------------------------

double Sphere::distance(const Grid &g, const Vector3d &w) const
{
    const double wrad = (w - POINT(0)).norm();
    return (wrad - getr()) * getn();
}

//-----------------------------------------------------------------------------

Vector3d Sphere::subpoint(const Grid &g, const Vector3d &w) const
{
    const Vector3d center = POINT(0);
    const Vector3d d = w - center;
    const double dnorm = d.norm();

    if (fabs(dnorm) < Vector3d::get_small())
    {   // w == center; no solution
        const double BIG = -Vector3d::get_big();
        return Vector3d(BIG, BIG, BIG);
    }
    else // w != center; well defined solution
        return center  +  d/dnorm * getr();
}

//-----------------------------------------------------------------------------

bool Sphere::contains(const Grid &g, const Vector3d &w) const
{
    (void)(g);
    (void)(w);
    return true; // Sphere has no boundary
}

//-----------------------------------------------------------------------------

RetIntercept Sphere::intercept(const Grid &g, const Vector3d &p,
                               const Vector3d &u, const double eqt,
                               const FaceID &fid) const
{   // pmh_2014_1201
    RetIntercept rv;
    rv.fid = FaceID(get_my_zone(), get_my_id());
    const Vector3d d = p - POINT(0);
    const double a = u * u;
    const double b = 2.0 * (d * u);
    const double c = d * d  -  r * r;

    // Eq.(3)
    #include "choose_root.inc" // contains: return rv;
}

//-----------------------------------------------------------------------------

Vector3d Sphere::velocity(const Grid &g, const Vector3d &w) const
{
    const Vector3d n = (w - POINT(0)).normalize();
    return VELOCITY(0)  +  n * v;
}

//-----------------------------------------------------------------------------

#undef VELOCITY
#undef POINT
#undef NODE

//-----------------------------------------------------------------------------

// end Sphere.cpp
