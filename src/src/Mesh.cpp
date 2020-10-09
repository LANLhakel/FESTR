/**
 * @file Mesh.cpp
 * @brief Mesh of Zones
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 18 December 2014\n
 * Last modified on 28 January 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Mesh.h>

#include <Surface.h>

#include <algorithm>

//-----------------------------------------------------------------------------

Mesh::Mesh(): nzones(0), zone() {}

//-----------------------------------------------------------------------------

Mesh::Mesh(const size_t nin): nzones(0), zone()
{
    zone.reserve(nin);
}

//-----------------------------------------------------------------------------

Mesh::Mesh(const std::string &path, const std::string &tlabel):
    nzones(0), zone()
{
    load(path, tlabel);
}

//-----------------------------------------------------------------------------

void Mesh::clear()
{
    nzones = 0;
    zone.clear();
}

//-----------------------------------------------------------------------------

void Mesh::add_zone(ZonePtr z)
{
    zone.emplace_back(std::move(z));
    ++nzones;
}

//-----------------------------------------------------------------------------

ZonePtr Mesh::get_zone(const size_t i) const
{
    return zone.at(i);
}

//-----------------------------------------------------------------------------

size_t Mesh::size() const
{
    return nzones;
}

//-----------------------------------------------------------------------------

FaceID Mesh::next_face(const Grid &g, const RetIntercept &h) const
{
    if (h.fid.my_id == -1) // exit Face is the Surface of bounding Sphere Zone
    {
        auto z = get_zone(0);    // bounding Sphere Zone
        auto f = z->get_face(1); // inner Surface of *z
        return f->get_neighbor(h.fid.my_zone); // 1-to-1 pairing of Faces here
    }
    else // regular Zone
    {    // or exiting bounding Sphere Zone through its outer Face (Sphere)
        auto z = get_zone(h.fid.my_zone);  // this Zone
        auto f = z->get_face(h.fid.my_id); // exit Face of *z
        size_t nf = f->num_nbr();
        for (size_t i = 0; i < nf; ++i)
        {
            FaceID fid = f->get_neighbor(i);
            if (fid.my_id == -1) // the neighbor is the bounding Sphere Zone
            {
                auto nz = get_zone(0);
                FacePtr fz = nz->get_face(1);
                SurfacePtr fs = std::dynamic_pointer_cast<Surface>(fz);
                auto fn = fs->get_face(fid.my_zone);
                if (fn->contains(g, h.w)) return FaceID(0, 1);
            }
            else // the neighbor is a regular Zone
            {
                auto nz = get_zone(fid.my_zone);
                auto fn = nz->get_face(fid.my_id);
                if (fn->contains(g, h.w)) return fid;
            }
        }
        return FaceID(); // bounding Sphere's outer Face has no neighbors
    }
}

//-----------------------------------------------------------------------------

void Mesh::load(const std::string &path, const std::string &tlabel)
{
    clear();
    std::string fname(path + "mesh_" + tlabel + ".txt");
    std::ifstream geometry(fname.c_str());
    if (!geometry.is_open())
    {
        std::cerr << "Error: file " << fname << " is not open in "
                  << "Mesh::load" << std::endl;
        exit(EXIT_FAILURE);
    }
    utils::find_word(geometry, "Number_of_zones");
    geometry >> nzones;
    zone.reserve(nzones);

    fname = path + "time_" + tlabel + ".txt";
    std::ifstream material(fname.c_str());
    if (!material.is_open())
    {
        std::cerr << "Error: file " << fname << " is not open in "
                  << "Mesh::load" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < nzones; ++i)
    {
        utils::find_word(geometry, "Zone");
        utils::find_word(material, "Zone");
        zone.emplace_back(std::make_shared<Zone>(geometry, material));
    }

    geometry.close();
    geometry.clear();
    material.close();
    material.clear();
}

//-----------------------------------------------------------------------------

std::string Mesh::to_string() const
{
    std::string s("Number_of_zones");
    s += utils::int_to_string(nzones, ' ', cnst::INT_WIDTH);
    s += cnststr::ZONE_SEPARATOR;
    for (size_t i = 0; i < nzones; ++i)
    {
        s += zone.at(i)->to_string();
        if (i < nzones-1) s += cnststr::ZONE_SEPARATOR;
    }
    return s;
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Mesh &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

//  end Mesh.cpp
