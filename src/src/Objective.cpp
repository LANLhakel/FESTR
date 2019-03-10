/**
 * @file Objective.cpp
 * @brief Defines an objective to be matched by a calculation
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 24 June 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Objective.h"
#include "utilities.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

//-----------------------------------------------------------------------------

const double Objective::BIG = 1.0e300;

//-----------------------------------------------------------------------------

Objective::Objective(void): oname("no_name"), path("no_path"),
    my_id(-1), weight(0.0), x_is_present(false), w_is_present(false),
    x(), y(), w(), best_fitness(-BIG), best_case(0),
    rescale(false), best_scale(1.0) {}

//-----------------------------------------------------------------------------

Objective::Objective(const std::string &oname_in, const std::string &path_in,
                     const int my_id_in, const double weight_in,
                     const bool x_is_present_in, const bool w_is_present_in,
                     const bool rescale_in):
    oname(oname_in), path(path_in), my_id(my_id_in), weight(weight_in),
    x_is_present(x_is_present_in), w_is_present(w_is_present_in),
    x(), y(), w(), best_fitness(-BIG), best_case(0),
    rescale(rescale_in), best_scale(1.0)
{
    std::string fname(path + oname + ".txt");
    std::ifstream infile(fname.c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: file " << fname << " is not open in "
                  << "Objective::Objective(parametrized)" << std::endl;
        exit(EXIT_FAILURE);
    }
    utils::find_word(infile, "oname");
    infile >> oname;
    utils::find_word(infile, "data");
    std::string s;
    getline(infile, s);
    double xin, yin, win;

    while (true)
    {
        if (x_is_present && w_is_present)
        {
            if ( !(infile >> xin >> yin >> win) ) break;
            x.push_back(xin);
            y.push_back(yin);
            w.push_back(win);
            continue;
        }

        if (!x_is_present && w_is_present)
        {
            if ( !(infile >> yin >> win) ) break;
            y.push_back(yin);
            w.push_back(win);
            continue;
        }

        if (x_is_present && !w_is_present)
        {
            if ( !(infile >> xin >> yin) ) break;
            x.push_back(xin);
            y.push_back(yin);
            w.push_back(1.0);
            continue;
        }

        if (!x_is_present && !w_is_present)
        {
            if ( !(infile >> yin) ) break;
            y.push_back(yin);
            w.push_back(1.0);
            continue;
        }
    }
    infile.close();
    infile.clear();
}

//-----------------------------------------------------------------------------

Objective::~Objective(void) {}

//-----------------------------------------------------------------------------

double Objective::abs_diff(const Objective &o) const
{
    const size_t n = get_size();
    const size_t na = o.get_size();
    double d = fabs(static_cast<double>(get_size()) - static_cast<double>(na));
    const size_t nmin = std::min(n, na);
    for (size_t i = 0; i < nmin; ++i) d += fabs(y.at(i) - o.y.at(i));
    return d;
}

//-----------------------------------------------------------------------------

std::string Objective::to_string(void) const
{
    std::string s(oname);
    const size_t n = get_size();
    if (n > 0) s += "\nweight" + utils::double_to_string(weight) + "\ndata";
    for (size_t i = 0; i < n; ++i)
    {
        s += "\n";
        if (x_is_present) s += utils::double_to_string(x.at(i));
        s += utils::double_to_string(y.at(i));
        s += utils::double_to_string(w.at(i));
    }
    return s;
}

//-----------------------------------------------------------------------------

std::string Objective::get_oname(void) const {return oname;}

//-----------------------------------------------------------------------------

std::string Objective::get_path(void) const {return path;}

//-----------------------------------------------------------------------------

int Objective::get_my_id(void) const {return my_id;}

//-----------------------------------------------------------------------------

double Objective::get_weight(void) const {return weight;}

//-----------------------------------------------------------------------------

std::string Objective::is_x_present(void) const
{return utils::bool_to_string(x_is_present);}

//-----------------------------------------------------------------------------

std::string Objective::is_w_present(void) const
{return utils::bool_to_string(w_is_present);}

//-----------------------------------------------------------------------------

size_t Objective::get_size(void) const {return y.size();}

//-----------------------------------------------------------------------------

double Objective::get_x_at(const size_t i) const {return x.at(i);}

//-----------------------------------------------------------------------------

double Objective::get_y_at(const size_t i) const {return y.at(i);}

//-----------------------------------------------------------------------------

double Objective::get_w_at(const size_t i) const {return w.at(i);}

//-----------------------------------------------------------------------------

double Objective::get_best_fitness(void) const {return best_fitness;}

//-----------------------------------------------------------------------------

size_t Objective::get_best_case(void) const {return best_case;}

//-----------------------------------------------------------------------------

bool Objective::get_rescale(void) const {return rescale;}

//-----------------------------------------------------------------------------

double Objective::get_best_scale(void) const {return best_scale;}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream & ost, const Objective & o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

// end Objective.cpp
