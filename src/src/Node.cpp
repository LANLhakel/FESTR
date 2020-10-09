/**
 * @file Node.cpp
 * @brief Grid Node
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 19 November 2014\n
 * Last modified on 28 January 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Node.h>

//-----------------------------------------------------------------------------

Node::Node(): i(0), r(), v() {}

//-----------------------------------------------------------------------------

Node::Node(const size_t iin, const Vector3d &rin): i(iin), r(rin), v() {}

//-----------------------------------------------------------------------------

Node::Node(const size_t iin, const Vector3d &rin, const Vector3d &vin):
    i(iin), r(rin), v(vin) {}

//-----------------------------------------------------------------------------

void Node::seti(const size_t iin)
{
    i = iin;
}

//-----------------------------------------------------------------------------

size_t Node::geti() const
{
    return i;
}

//-----------------------------------------------------------------------------

void Node::setr(const Vector3d &rin)
{
    r = rin;
}

//-----------------------------------------------------------------------------

Vector3d Node::getr() const
{
    return r;
}

//-----------------------------------------------------------------------------

void Node::setv(const Vector3d &vin)
{
    v = vin;
}

//-----------------------------------------------------------------------------

Vector3d Node::getv() const
{
    return v;
}

//-----------------------------------------------------------------------------

double Node::abs_diff(const Node &o) const
{
    const double idiff = static_cast<double>(i - o.i);
    const Vector3d rdiff = r - o.r;
    const Vector3d vdiff = v - o.v;
    return idiff*idiff + rdiff.norm() + vdiff.norm();
}

//-----------------------------------------------------------------------------

std::string Node::to_string() const
{
    return r.to_string() + v.to_string();
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Node &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

//  end Node.cpp
