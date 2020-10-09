/**
 * @file Surface.cpp
 * @brief A composite Face that is a collection of other Face objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 16 December 2014\n
 * Last modified on 27 February 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Surface.h>

#include <FaceFactory.h>

#include <algorithm>

//-----------------------------------------------------------------------------

Surface::Surface(): Face(), nfaces(0), face() {}

//-----------------------------------------------------------------------------

Surface::Surface(const size_t my_zone_in, const short int my_id_in):
    Face(my_zone_in, my_id_in), nfaces(0), face() {}

//-----------------------------------------------------------------------------

Surface::Surface(const size_t my_zone_in, const short int my_id_in,
                 const size_t nin):
    Face(my_zone_in, my_id_in), nfaces(0), face()
{
    face.reserve(nin);
}

//-----------------------------------------------------------------------------

Surface::Surface(const size_t nin): Face(), nfaces(0), face()
{
    face.reserve(nin);
}

//-----------------------------------------------------------------------------

Surface::Surface(std::ifstream &istr): Face(), nfaces(0), face()
{
    load(istr);
}

//-----------------------------------------------------------------------------

void Surface::clear()
{
    nfaces = 0;
    face.clear();
    Face::clear();
}

//-----------------------------------------------------------------------------

void Surface::add_face(FacePtr f)
{
    face.emplace_back(std::move(f));
    ++nfaces;
}

//-----------------------------------------------------------------------------

FacePtr Surface::get_face(const size_t i) const
{
    return face.at(i);
}

//-----------------------------------------------------------------------------

size_t Surface::size() const
{
    return nfaces;
}

//-----------------------------------------------------------------------------

bool Surface::is_curved(const Grid &g) const
{
    (void)(g);
    return true;
}

//-----------------------------------------------------------------------------

std::string Surface::to_string() const
{
    std::string s("Surface\n");
    s += utils::int_to_string(nfaces, ' ', cnst::INT_WIDTH) + "\n";
    s += Face::to_string();
    for (size_t i = 0; i < nfaces; ++i)
    {
        if (i == 0) s += "\n";
        s += face.at(i)->to_string();
        if (i < nfaces-1) s += "\n";
    }
    return s;
}

//-----------------------------------------------------------------------------

void Surface::load(std::ifstream &geometry)
{
    clear();
    geometry >> nfaces;
    load_face(geometry, 0); // Surface consists of Faces, not Nodes
    #include <load_Faces.inc>
}

//-----------------------------------------------------------------------------

Vector3d Surface::area2_normal_center(const Grid &g, Vector3d &c) const
{
    (void)(g);
    (void)(c); // left unchanged
    return Vector3d(); // left undefined
}

//-----------------------------------------------------------------------------

Vector3d Surface::normal(const Grid &g) const
{
    (void)(g);
    return Vector3d(); // left undefined
}

//-----------------------------------------------------------------------------

double Surface::area(const Grid &g) const
{
    double s = 0.0;
    for (size_t i = 0; i < nfaces; ++i) s += face.at(i)->area(g);
    return s;
}

//-----------------------------------------------------------------------------

double Surface::distance(const Grid &g, const Vector3d &w) const
{
    (void)(g);
    (void)(w);
    return 0.0; // left undefined
}

//-----------------------------------------------------------------------------

Vector3d Surface::subpoint(const Grid &g, const Vector3d &w) const
{
    (void)(g);
    (void)(w);
    return Vector3d(); // left undefined
}

//-----------------------------------------------------------------------------

Vector3d Surface::face_point(const Grid &g, const Vector3d &w) const
{
    return subpoint(g, w);
}

//-----------------------------------------------------------------------------

bool Surface::contains(const Grid &g, const Vector3d &w) const
{
    (void)(g);
    (void)(w);
    return true; // since w was calculated as a constituent Face's intercept
}

//-----------------------------------------------------------------------------

RetIntercept Surface::intercept(const Grid &g, const Vector3d &p,
                                const Vector3d &u, const double eqt,
                                const FaceID &fid) const
{
    RetIntercept rv, pt;
    for (size_t i = 0; i < nfaces; ++i)
    {
        pt = face.at(i)->intercept(g, p, u, eqt, fid);
        if (pt.is_found  &&  pt.t < rv.t)
        {
            rv.t = pt.t;
            rv.w = pt.w;
            rv.fid = FaceID(i, -1);
            rv.is_found = true;
        }
    }
    return rv;
}

//-----------------------------------------------------------------------------

Vector3d Surface::velocity(const Grid &g, const Vector3d &w) const
{
    (void)(g);
    (void)(w);
    return Vector3d(); // left undefined
}

//-----------------------------------------------------------------------------

//  end Surface.cpp
