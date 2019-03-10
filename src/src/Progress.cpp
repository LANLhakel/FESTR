/**
 * @file Progress.cpp
 * @brief Progress objects are used to monitor the progress of a calculation.
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 8 August 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Progress.h"
#include "utilities.h"
#include <iostream>

//-----------------------------------------------------------------------------

Progress::Progress(void): name("empty"), label("none"), level(0), n(0),
    freq(0), sep(""), i(0), j(0), ndig(0), rn(0.0), maxstr(""), ostr(std::cerr)
{}

//-----------------------------------------------------------------------------

Progress::Progress(const std::string &name_in, const int level_in,
                   const size_t nin, const size_t freq_in,
                   const std::string &sep_in, std::ostream &ostr_in):
    name(name_in), label(""), level(level_in), n(nin), freq(freq_in),
    sep(""), i(0), j(0), ndig(utils::ndigits(nin)),
    rn(static_cast<double>(nin)/100.0),
    maxstr(nin > 0 ? " of " + utils::int_to_string(nin, ' ', utils::ndigits(nin))
                   + ", " : " of ?"), ostr(ostr_in)
{
    for (int k = 0; k < level; ++k) label += ">";
    label += " " + name + ": ";
    if (sep_in != "") sep = "\n" + sep_in;
    if (freq_in > 0) print();
}

//-----------------------------------------------------------------------------

Progress::~Progress(void)
{
    if (freq > 0)
    {
        if (n%freq > 0) print();
        if (n == 0)
        {
            if (j > 0) print();
            ostr << label << "? = "
                 << utils::int_to_string(i, ' ', utils::ndigits(i))
                 << std::endl;
        }

        // ...hardwired...
        if (name == "Ray_transport") ostr << std::endl;
        if (name == "Ray_trace")
            ostr << "........................................" << std::endl;
    }
}

//-----------------------------------------------------------------------------

int Progress::get_level(void) const {return level;}

//-----------------------------------------------------------------------------

std::string Progress::to_string(void) const
{
    std::string s("Progress: " + name + "\nlevel: ");
    size_t lev(static_cast<size_t>(level));
    s += utils::int_to_string(lev, ' ', utils::ndigits(lev));
    s += "\nn: " + utils::int_to_string(n, ' ', utils::ndigits(n));
    s += "\nfreq: " + utils::int_to_string(freq, ' ', utils::ndigits(freq));
    return s;
}

//-----------------------------------------------------------------------------

void Progress::print(void) const
{
    std::string s(label + utils::int_to_string(i, ' ', ndig) + maxstr);
    if (n > 0)
    {
        if (i == n)
            s += "100%";
        else
            s += utils::int_to_string(floor(static_cast<double>(i)/rn), ' ', 3) + "%";
    }
    ostr << s << sep << std::endl;
}

//-----------------------------------------------------------------------------

void Progress::advance(void)
{
    if (freq == 0) return;
    ++i; ++j; if (j == freq) {j = 0; print();}
}

//-----------------------------------------------------------------------------

size_t Progress::get_next_freq(const size_t f) const
{
    if (freq == 0) return 0;
    return (j+1) == freq ? f : 0;
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Progress &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

// end Progress.cpp
