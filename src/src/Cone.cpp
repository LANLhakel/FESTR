/**
 * @file Cone.cpp
 * @brief Conical ribbons for 2-D RZ geometry (derived from class Face)
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 14 May 2015\n
 * Last modified on 17 February 2022
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Cone.h>

#include <utils.h>

#include <cmath>
#include <utility>

//-----------------------------------------------------------------------------

// X: node index local to *this; range: 0 through size()-1
#define NODE(X)     g.get_node(get_node((X)))
#define POINT(X)    NODE((X)).getr()
#define VELOCITY(X) NODE((X)).getv()

//-----------------------------------------------------------------------------

const double Cone::SMALL = 5.0e-7; // centimeters
const double Cone::MINIMUM_DISTANCE = 1.0e-6; // centimeters
const double Cone::ZERO = 1.0e-19; // centimeters squared
    
//-----------------------------------------------------------------------------

Cone::Cone(): Face() {}

//-----------------------------------------------------------------------------

Cone::Cone(const size_t my_zone_in, const short int my_id_in):
    Face(my_zone_in, my_id_in) {}

//-----------------------------------------------------------------------------

Cone::Cone(std::ifstream &istr)
{
    load(istr);
}

//-----------------------------------------------------------------------------

Cone::~Cone() {}

//-----------------------------------------------------------------------------

bool Cone::is_curved(const Grid &g) const
{
    return fabs( POINT(1).gety() - POINT(0).gety() ) > SMALL;
}

//-----------------------------------------------------------------------------

std::string Cone::to_string() const
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

Vector3d Cone::face_point(const Grid &g, const Vector3d &w) const
{
    double phi = atan2(w.gety(), w.getx());
    Vector3d mid = (POINT(0) + POINT(1)) / 2.0;
    double midx = mid.getx();
    double midy = mid.gety();

    return Vector3d(midx*cos(phi), midx*sin(phi), midy);
}

//-----------------------------------------------------------------------------

bool Cone::contains(const Grid &g, const Vector3d &w) const
{   // pmh_2015_0508, page 5; amended in pmh_2019_1031
    const Vector3d v(w.get_rz());
    const double vx = v.getx();
    const double vy = v.gety();

    const Vector3d a(POINT(0));
    const double ax = a.getx();
    const double ay = a.gety();

    const Vector3d b(POINT(1));
    const double bx = b.getx();
    const double by = b.gety();

    return (vx - ax) * (vx - bx)  <=  ZERO   &&
           (vy - ay) * (vy - by)  <=  ZERO;
}

//-----------------------------------------------------------------------------

RetIntercept Cone::intercept(const Grid &g, const Vector3d &p,
                             const Vector3d &u, const double eqt,
                             const FaceID &fid) const
{
    RetIntercept rv;
    rv.fid = FaceID(get_my_zone(), get_my_id());
    Vector3d atail = POINT(0);
    double za = atail.gety();
    double pz = p.getz();
    double uz = u.getz();

    if (is_flat(g)) // see Polygon::intercept (pmh_2014_1125) with n = zhat
    {
        if (rv.fid == fid  ||  fabs(uz) < Vector3d::get_small())
        {
            double BIG = -Vector3d::get_big();
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
    }
    else // pmh_2015_0508
    {
        Vector3d bhead = POINT(1);
        double ra = atail.getx();
        double px = p.getx();
        double py = p.gety();
        double dr = bhead.getx() - ra; // Eq.(3)
        double dz = bhead.gety() - za; // Eq.(2)
        double ux = u.getx();
        double uy = u.gety();
        double rp2 = px*px + py*py; // Eq.(6)
        double zd = pz - za; // Eq.(7)
        double dz2 = dz * dz;
        double ff = dz2 * (px*ux + py*uy); // Eq.(8)
        double gg = dz * ra * dr; // Eq.(9)
        double hh = gg  +  zd * dr * dr; // Eq.(11)
        double uzdr = uz * dr;

        double uxy2 = ux*ux + uy*uy;
        if (uxy2 > 1.0e-8)
        {   // general case
            // Eq.(12)
            double a = dz2 * uxy2  -  uzdr * uzdr;
            double b = 2.0 * (ff  -  uz * hh);
            double c = dz2 * (rp2 - ra*ra)  -  zd * (gg + hh);
            #include <choose_root.inc>
        }
        else
        {   // avoid numerical problems for vertical rays
            if (fabs(dr) < Vector3d::get_small())
            {   // no solution if *this is a cylinder
                double BIG = -Vector3d::get_big();
                rv.t = BIG;
                rv.w = Vector3d(BIG, BIG, BIG);
                rv.is_found = false;
            }
            else
            {
                rv.w.setx(px);
                rv.w.sety(py);
                rv.w.setz(za  +  (sqrt(rp2) - ra) * dz / dr);
                rv.t = (rv.w.getz() - p.getz()) / uz;
                rv.is_found = utils::sign_eqt(rv.t, eqt) == 1 && contains(g, rv.w);
            }
        }

        // check whether Ray runs along *this
        double phi = atan2(rv.w.gety(), rv.w.getx());
        double b_rad = bhead.getx();
        Vector3d head(b_rad*cos(phi), b_rad*sin(phi), bhead.gety());
        double a_rad = atail.getx();
        Vector3d tail(a_rad*cos(phi), a_rad*sin(phi), atail.gety());
        Vector3d cone_dir = (tail - head).normalize();
        Vector3d cross_product = (cone_dir % u) / u.norm();
        if (fabs(cross_product.norm()) < 1.0e-16)
        {   // Ray runs along *this
            double BIG = -Vector3d::get_big();
            rv.t = BIG;
            rv.w = Vector3d(BIG, BIG, BIG);
            rv.is_found = false;
        }
        else
        {   // see, if a valid solution is rejected due to
            // floating-point numerics near *this Cone's vertex
            if (!rv.is_found  &&  fid == rv.fid  &&
                sqrt(rp2) < 2*MINIMUM_DISTANCE) // short hop
            {   // move the Ray across the z-axis (tolerating a small error)
                rv.w = Vector3d(-px, -py, pz);
                // but this solution is provisional (don't get stuck here)
                rv.t = Vector3d::get_big() / 2.0;
                rv.is_found = true;
            }
        }
    }

    if (rv.is_found  &&  rv.t < Vector3d::get_big() / 4.0)
    {  // see, if the solution needs to be moved away from edge
       // pmh_2019_1031
        Vector3d w = rv.w;
        double phi = atan2(w.gety(), w.getx());
        std::pair<Vector3d, Vector3d> endpoints = get_endpoints(g, phi);
        Vector3d a = endpoints.first;
        Vector3d b = endpoints.second;
        if ((w-a).norm() < MINIMUM_DISTANCE)
            rv.w = linear_Vector3d_fit(MINIMUM_DISTANCE, a, b);
        if ((w-b).norm() < MINIMUM_DISTANCE)
            rv.w = linear_Vector3d_fit(MINIMUM_DISTANCE, b, a);
    }

    return rv;
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

std::pair<Vector3d, Vector3d> Cone::get_endpoints(const Grid &g,
                                                  const double phi) const
{   // pmh_2019_1031
    Vector3d v0 = POINT(0);
    Vector3d v1 = POINT(1);
    double r0 = v0.getx();
    double r1 = v1.getx();
    double z0 = v0.gety();
    double z1 = v1.gety();
    Vector3d a(r0*cos(phi), r0*sin(phi), z0);
    Vector3d b(r1*cos(phi), r1*sin(phi), z1);
    if (z0 < z1) std::swap(a, b);
    return std::pair<Vector3d, Vector3d>(a, b);
}

//-----------------------------------------------------------------------------

#undef VELOCITY
#undef POINT
#undef NODE


//-----------------------------------------------------------------------------

//  end Cone.cpp
