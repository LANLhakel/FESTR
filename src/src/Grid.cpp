/**
 * @file Grid.cpp
 * @brief Grid of Nodes
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 21 November 2014\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Grid.h"
#include "utilities.h"

//-----------------------------------------------------------------------------

Grid::Grid(void): node(), num_nodes(0) {}

//-----------------------------------------------------------------------------

Grid::Grid(const std::string &path, const std::string &tlabel):
    node(), num_nodes(0) {load(path, tlabel);}

//-----------------------------------------------------------------------------

Grid::~Grid(void) {clear();}

//-----------------------------------------------------------------------------

void Grid::clear(void)
{
    num_nodes = 0;
    node.clear();
}

//-----------------------------------------------------------------------------

void Grid::add_node(const Node &nin)
{
    node.push_back(nin);
    ++num_nodes;
}

//-----------------------------------------------------------------------------

Node Grid::get_node(const size_t i) const {return node.at(i);}

//-----------------------------------------------------------------------------

void Grid::replace_node(const Node &nin)
{
    node.at(nin.geti()) = nin;
}

//-----------------------------------------------------------------------------

size_t Grid::size(void) const {return num_nodes;}

//-----------------------------------------------------------------------------

double Grid::abs_diff(const Grid &o) const
{
    size_t range = num_nodes;
    const size_t g_range = o.num_nodes;
    const double rdiff = static_cast<double>(range)
                       - static_cast<double>(g_range);
    if (g_range < range) range = g_range;
    double d;
    double diff = 0.0;
    size_t i;
    for (i = 0; i < range; ++i)
    {
        d = node.at(i).abs_diff(o.node.at(i));
        diff += d;
    }
    return diff + rdiff*rdiff;
}

//-----------------------------------------------------------------------------

void Grid::load(const std::string &path, const std::string &tlabel)
{
    clear();
    std::string fname = path + "grid_" + tlabel + ".txt";
    std::ifstream infile(fname.c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: file " << fname << " is not open in "
                  << "Grid::load" << std::endl;
        exit(EXIT_FAILURE);
    }
    utils::find_line(infile, "# start");
    infile >> num_nodes;
    node.reserve(num_nodes);
    size_t i, j;
    double rx, ry, rz, vx, vy, vz;
    for (i = 0; i < num_nodes; ++i)
    {
        infile >> j >> rx >> ry >> rz >> vx >> vy >> vz;
        node.push_back(Node(i, Vector3d(rx, ry, rz), Vector3d(vx, vy, vz)));
    }
    infile.close();
    infile.clear();
}

//-----------------------------------------------------------------------------

std::string Grid::to_string(void) const
{
    std::string s = "";
    for (size_t i = 0; i < num_nodes; ++i)
    {
        if (i > 0) s += "\n";
        s += node.at(i).to_string();
    }
    return s;
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Grid &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

// end Grid.cpp
