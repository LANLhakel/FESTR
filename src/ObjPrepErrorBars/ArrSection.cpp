/**
 * @file ArrSection.cpp
 * @brief Array of doubles with arbitrary index range
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 25 July 2016\n
 * Last modified on 28 March 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <ArrSection.h>
#include <utils.h>

#include <utility>
#include <iostream>

//-----------------------------------------------------------------------------

ArrSection::ArrSection(void): nlow(0), nup(0), n(0), pad0(false), v() {}

//-----------------------------------------------------------------------------

ArrSection::ArrSection(int nlow_in, int nup_in, const bool p0):
    nlow(0), nup(0), n(0), pad0(p0), v()
{
    if (nlow_in > nup_in) std::swap(nlow_in, nup_in);
    nlow = nlow_in;
    nup = nup_in;
    n = nup_in - nlow_in + 1;
    v.assign(n, 0.0);
}

//-----------------------------------------------------------------------------

ArrSection::~ArrSection(void) {}

//-----------------------------------------------------------------------------

int ArrSection::get_lower_limit(void) const {return nlow;}

//-----------------------------------------------------------------------------

int ArrSection::get_upper_limit(void) const {return nup;}

//-----------------------------------------------------------------------------

int ArrSection::size(void) const {return n;}

//-----------------------------------------------------------------------------

double & ArrSection::operator [](const int i) // lvalue, in-range index only
{
    return v.at(i - nlow);
}

//-----------------------------------------------------------------------------

double ArrSection::operator ()(const int i) const // rvalue, any index
{
    if (i <= nlow)
    {
        if (pad0)
            return 0.0;
        else
            return v[0];
    }

    if (i >= nup)
    {
        if (pad0)
            return 0.0;
        else
            return v[n - 1];
    }

    return v[i - nlow];
}

//-----------------------------------------------------------------------------

double ArrSection::abs_diff(const ArrSection &o) const
{
    const int na = o.size();
    double d = fabs(static_cast<double>(n) - static_cast<double>(na));
    const int nmin = std::min(n, na);
    for (int i = 0; i < nmin; ++i) d += fabs(v[i] - o.v[i]);
    return d;
}

//-----------------------------------------------------------------------------

std::string ArrSection::to_string(void) const
{
    std::string s = "";
    for (size_t i = 0; i < n; ++i)
    {
        if (i > 0) s += "\n";
        s += utils::double_to_string(v.at(i));
    }
    return s;
}

//-----------------------------------------------------------------------------

void ArrSection::to_file(const std::string &fname,
                     const std::string &header) const
{
    std::ofstream outfile(fname.c_str());
    outfile << header << "\n" << to_string();
    outfile.close();
    outfile.clear();
}

//-----------------------------------------------------------------------------

void ArrSection::fill(const double f) {v.assign(n, f);}

//-----------------------------------------------------------------------------

// end ArrSection.cpp
