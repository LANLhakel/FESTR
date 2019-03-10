/**
 * @file Polygon.cpp
 * @brief Convex Polygons (derived from class Face)
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 21 November 2014\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Polygon.h"
#include "utilities.h"
#include <cmath>

//-----------------------------------------------------------------------------

// X: node index local to *this; range: 0 through size()-1
#define NODE(X)     g.get_node(get_node((X)))
#define POINT(X)    NODE((X)).getr()
#define VELOCITY(X) NODE((X)).getv()

//-----------------------------------------------------------------------------

Polygon::Polygon(void): Face() {}

//-----------------------------------------------------------------------------

Polygon::Polygon(const size_t my_zone_in, const short int my_id_in):
    Face(my_zone_in, my_id_in) {}

//-----------------------------------------------------------------------------

Polygon::Polygon(std::ifstream &istr) {load(istr);}

//-----------------------------------------------------------------------------

Polygon::~Polygon(void) {}

//-----------------------------------------------------------------------------

bool Polygon::is_curved(const Grid &g) const
{
    (void)(g);
    return false;
}

//-----------------------------------------------------------------------------

std::string Polygon::to_string(void) const
{
    return "Polygon\n"
           + utils::int_to_string(Face::size(), ' ', cnst::INT_WIDTH) + "\n"
           + Face::to_string();
}

//-----------------------------------------------------------------------------

void Polygon::load(std::ifstream &istr)
{
    size_t nnodes;
    istr >> nnodes;
    load_face(istr, nnodes);
}

//-----------------------------------------------------------------------------

// *this Polygon is assumed to be convex
Vector3d Polygon::area2_normal_center(const Grid &g, Vector3d &c) const
{
    const Vector3d origin = POINT(0);
    Vector3d p_next = POINT(1);
    Vector3d v_next = p_next - origin;
    Vector3d p_prev, v_prev, a, s, ctr;
    c.set0();
    for (size_t i = 2; i < size(); ++i)
    {
        p_prev = p_next;
        p_next = POINT(i);

        // normal vector part
        v_prev = v_next;
        v_next = p_next - origin;
        a = v_prev % v_next;
        s += a;

        // center part
        ctr = (origin + p_prev + p_next) / 3.0; // centroid of a triangle
        c += ctr * a.norm(); // building triangle-area-weighted average vector
    }
    c /= s.norm();
    return s; // |s| = 2*area
}

//-----------------------------------------------------------------------------

Vector3d Polygon::normal(const Grid &g) const
{
    Vector3d c;
    return area2_normal_center(g, c).normalize();
}

//-----------------------------------------------------------------------------

double Polygon::area(const Grid &g) const
{
    Vector3d c;
    return area2_normal_center(g, c).norm() / 2.0;
}

//-----------------------------------------------------------------------------

double Polygon::distance(const Grid &g, const Vector3d &w) const
{   // pmh_2014_1125
    const Vector3d d = w - POINT(0);
    const Vector3d n = normal(g);
    return d * n;
}

//-----------------------------------------------------------------------------

Vector3d Polygon::subpoint(const Grid &g, const Vector3d &w) const
{   // pmh_2014_1125
    const double t = distance(g, w);
    const Vector3d n = normal(g);
    return w - n*t;
}

//-----------------------------------------------------------------------------

// *this Polygon is assumed to be convex
// z component of v is assumed == 0 after transformation into *this plane
bool Polygon::contains(const Grid &g, const Vector3d &w) const
{   // pmh_2014_1125
    const int NOT_INITIALIZED = -2;
    int first_turn = NOT_INITIALIZED;
    int turn;

    // build local coordinate system in the plane of *this
    const Vector3d Zhat = normal(g);
    const Vector3d origin = POINT(0);
    const Vector3d Xhat = (POINT(1) - origin).normalize();
    const Vector3d Yhat = Zhat % Xhat;

    // build q as the representation of v in this local coordinate system
    const Vector3d p = w - origin;
    const Vector3d q(p*Xhat, p*Yhat, 0.0);
    Vector3d head3d, tail3d, head, tail;

    // loop over *this Polygon's sides
    size_t i;
    const size_t n = size();
    for (size_t j = 0; j < n; ++j)
    {   // see if q is on the same side relative to each side's vector
        i = j + 1;
        if (i == n) i = 0;
        head3d = POINT(i) - origin;
        tail3d = POINT(j) - origin;
        head = Vector3d(head3d*Xhat, head3d*Yhat, 0.0);
        tail = Vector3d(tail3d*Xhat, tail3d*Yhat, 0.0);
        turn = q.get_turn(tail, head);

        if (turn != 0)
        {   // points lying exactly on the line are not considered
            if (first_turn == NOT_INITIALIZED)
            {
                first_turn = turn;
            }
            else
            {   // if turn differs from first_turn => v is outside of *this
                if (first_turn != turn) return false;
            }
        }
    }

    // all turns were in the same direction => *this contains v
    return true;
}

//-----------------------------------------------------------------------------

RetIntercept Polygon::intercept(const Grid &g, const Vector3d &p,
                                const Vector3d &u, const double eqt,
                                const FaceID &fid) const
{   // pmh_2014_1125
    RetIntercept rv;
    rv.fid = FaceID(get_my_zone(), get_my_id());
    const Vector3d n = normal(g);
    const double denominator = u * n;

    if (rv.fid == fid  ||  fabs(denominator) < Vector3d::get_small())
    {
        const double BIG = -Vector3d::get_big();
        rv.t = BIG;
        rv.w = Vector3d(BIG, BIG, BIG);
        rv.is_found = false;
    }
    else
    {
        const Vector3d a = POINT(0);
        const double numerator = (a - p) * n;
        rv.t = numerator / denominator; // Eq.(3)
        rv.w = p  +  u * rv.t; // Eq.(2)
        rv.is_found = utils::sign_eqt(rv.t, eqt) == 1  &&  contains(g, rv.w);
    }

    return rv;
}

//-----------------------------------------------------------------------------

Vector3d Polygon::velocity(const Grid &g, const Vector3d &w) const
{
    const double SMALL = Vector3d::get_small();
    Vector3d u;
    double d;
    double s = 0.0;
    for (size_t i = 0; i < size(); ++i)
    {
        d = (POINT(i) - w).norm();
        if (d < SMALL) return VELOCITY(i);
        d = 1.0 / d;
        s += d;
        u += d * VELOCITY(i);
    }
    return u / s;
}

//-----------------------------------------------------------------------------

#undef VELOCITY
#undef POINT
#undef NODE

//-----------------------------------------------------------------------------

// end Polygon.cpp
