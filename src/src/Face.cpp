/**
 * @file Face.cpp
 * @brief Abstract base class for various Face types that define Zone objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 20 November 2014\n
 * Last modified on 28 January 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Face.h>

#include <utils.h>

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const FaceID &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

Face::Face(): my_zone(0), my_id(-2), node(), nbr() {}

//-----------------------------------------------------------------------------

Face::Face(const size_t my_zone_in, const short int my_id_in):
    my_zone(my_zone_in), my_id(my_id_in), node(), nbr() {}

//-----------------------------------------------------------------------------

Face::~Face()
{
    clear();
}

//-----------------------------------------------------------------------------

void Face::clear()
{
    my_zone = 0;
    my_id = -2;
    node.clear();
    nbr.clear();
}

//-----------------------------------------------------------------------------

void Face::set_my_zone(const size_t my_zone_in)
{
    my_zone = my_zone_in;
}

//-----------------------------------------------------------------------------

size_t Face::get_my_zone() const
{
    return my_zone;
}

//-----------------------------------------------------------------------------

void Face::set_my_id(const short int my_id_in)
{
    my_id = my_id_in;
}

//-----------------------------------------------------------------------------

short int Face::get_my_id() const
{
    return my_id;
}

//-----------------------------------------------------------------------------

size_t Face::size() const
{
    return node.size();
}

//-----------------------------------------------------------------------------

bool Face::is_flat(const Grid &g) const
{
    return !is_curved(g);
}

//-----------------------------------------------------------------------------

void Face::add_node(const size_t i)
{
    node.emplace_back(std::move(i));
}

//-----------------------------------------------------------------------------

size_t Face::get_node(const size_t i) const
{
    return node.at(i);
}

//-----------------------------------------------------------------------------

double Face::abs_diff(const Face &o) const
{
    const double zdiff = static_cast<double>(my_zone)
                       - static_cast<double>(o.my_zone);
    const double idiff = static_cast<double>(my_id)
                       - static_cast<double>(o.my_id);
    size_t range = node.size();
    const size_t f_range = o.node.size();
    const double rdiff = static_cast<double>(range)
                       - static_cast<double>(f_range);

    if (f_range < range) range = f_range;
    double d;
    double diff = 0.0;
    for (size_t i = 0; i < range; ++i)
    {
        d = static_cast<double>(node.at(i) - o.node.at(i));
        diff += d*d;
    }
    return diff + zdiff*zdiff + idiff*idiff + rdiff*rdiff;
}

//-----------------------------------------------------------------------------

std::string Face::to_string() const
{
    size_t i;
    std::string s = utils::int_to_string(my_zone, ' ', cnst::INT_WIDTH) +
                    utils::int_to_string(my_id, ' ', cnst::INT_WIDTH);

    const size_t nsize = Face::size(); // Surface has its own size() function
    if (nsize > 0) s += "\n";
    for (i = 0; i < nsize; ++i)
        s += utils::int_to_string(node.at(i), ' ', cnst::INT_WIDTH);

    const size_t numnbr = num_nbr();
    s += "\n          neighbors";
    s += utils::int_to_string(numnbr, ' ', cnst::INT_WIDTH);
    for (i = 0; i < numnbr; ++i) s += "\n" + get_neighbor(i).to_string();

    return s;
}

//-----------------------------------------------------------------------------

void Face::load_face(std::ifstream &istr, const size_t nnodes)
{
    Face::clear(); // derived classes have their own clear() functions
    istr >> my_zone >> my_id; // load FaceID
    size_t i, j, nnbr;
    short int k;

    for (i = 0; i < nnodes; ++i) // load Nodes
    {
        istr >> j;
        add_node(j);
    }

    utils::find_word(istr, "neighbors");
    istr >> nnbr;
    for (i = 0; i < nnbr; ++i) // load Neighbors' FaceID's
    {
        istr >> j >> k;
        add_neighbor(j, k);
    }
}

//-----------------------------------------------------------------------------

void Face::add_neighbor(const size_t zone_in, const short int face_in)
{
    nbr.emplace_back(FaceID(zone_in, face_in));
}

//-----------------------------------------------------------------------------

FaceID Face::get_neighbor(const size_t i) const
{
    return nbr.at(i);
}

//-----------------------------------------------------------------------------

size_t Face::num_nbr() const
{
    return nbr.size();
}

//-----------------------------------------------------------------------------

bool Face::has_above(const Grid &g, const Vector3d &v) const
{
    return distance(g, v) > 0.0;
}

//-----------------------------------------------------------------------------

bool Face::has_below(const Grid &g, const Vector3d &v) const
{
    return distance(g, v) < 0.0;
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Face &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

const FaceID Face::BOUNDING_SPHERE = FaceID(0, 0);

//-----------------------------------------------------------------------------

//  end Face.cpp
