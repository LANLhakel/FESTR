/**
 * @file Goal.cpp
 * @brief A collection of Objective objects
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 28 June 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Goal.h"
#include "utilities.h"
#include "constants.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <numeric>

//-----------------------------------------------------------------------------

const double Goal::BIG = 1.0e300;

//-----------------------------------------------------------------------------

Goal::Goal(void):
    analysis(false), fitness(), best_fitness(-BIG), best_case(0), n(0),
    path(""), obj() {}

//-----------------------------------------------------------------------------

Goal::Goal(const bool analysis_in, const std::string &goal_path):
    analysis(analysis_in), fitness(), best_fitness(-BIG), best_case(0), n(0),
    path(goal_path), obj()
{
    if (!analysis) return;
    std::string fname(goal_path + "list.txt");
    std::ifstream infile(fname.c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: file " << fname << " is not open in "
                  << "Goal::Goal(parametrized)" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string oname, xstr, wstr, sstr;
    double weight;
    utils::find_word(infile, "Objectives");
    infile >> n;
    utils::find_line(infile,
                    "Objective_Name weight x_is_present w_is_present rescale");
    Objective *ob;
    obj.reserve(n);
    int i;
    int nn = static_cast<int>(n);
    for (i = 0; i < nn; ++i)
    {
        infile >> oname >> weight >> xstr >> wstr >> sstr;
        ob = new Objective(oname, path, i, weight, utils::string_to_bool(xstr),
                           utils::string_to_bool(wstr),
                           utils::string_to_bool(sstr));
        obj.push_back(ob);
        fitness.push_back(-BIG);
    }
    infile.close();
    infile.clear();
}

//-----------------------------------------------------------------------------

Goal::~Goal(void)
{
    analysis = false;
    fitness.clear();
    best_fitness = -BIG;
    best_case = 0;
    n = 0;
    path = "";
    for_each(obj.begin(), obj.end(), utils::DeleteObject());
    obj.clear();
}

//-----------------------------------------------------------------------------

const Objective * Goal::get_objective(const size_t i) const {return obj.at(i);}

//-----------------------------------------------------------------------------

size_t Goal::size(void) const {return n;}

//-----------------------------------------------------------------------------

bool Goal::get_analysis(void) const {return analysis;}

//-----------------------------------------------------------------------------

void Goal::set_analysis(const bool a) {analysis = a;}

//-----------------------------------------------------------------------------

std::string Goal::to_string(void) const
{
    std::string s("Number of Objectives ");
    s += utils::int_to_string(size(), ' ', cnst::INT_WIDTH);
    s += "\nObjective_Name weight x_is_present w_is_present";
    for (size_t i = 0; i < n; ++i)
    {
        const Objective *ob = get_objective(i);
        s += "\n" + ob->get_oname() + " ";
        s += utils::double_to_string(ob->get_weight());
        s += " " + ob->is_x_present() + " " + ob->is_w_present();
    }
    return s;
}

//-----------------------------------------------------------------------------

std::string Goal::get_name(const size_t i) const
{return obj.at(i)->get_oname();}

//-----------------------------------------------------------------------------

size_t Goal::get_index(const std::string &s) const
{
    size_t i;
    for (i = 0; i < n; ++i) if (s == get_name(i)) return i;
    return n;
}

//-----------------------------------------------------------------------------

double Goal::get_fitness_at(const size_t i) const {return fitness.at(i);}

//-----------------------------------------------------------------------------

double Goal::get_fitness(void) const
{
    double s = std::accumulate(fitness.begin(), fitness.end(), 0.0);
    double r = static_cast<double>(n);
    return s / r; // pmh_2015_0719, Eq. (1)
}

//-----------------------------------------------------------------------------

double Goal::get_best_fitness(void) const {return best_fitness;}

//-----------------------------------------------------------------------------

void Goal::set_best_case(const size_t i) {best_case = i;}

//-----------------------------------------------------------------------------

size_t Goal::get_best_case(void) const {return best_case;}

//-----------------------------------------------------------------------------

void Goal::update_best(const size_t i)
{
    double bf = get_fitness();
    if (bf > best_fitness)
    {
        best_fitness = bf;
        best_case = i;
    }
}

//-----------------------------------------------------------------------------

double Goal::get_best_scale(const std::string &s) const
{
    size_t i = get_index(s);
    if (i < n)
        return obj.at(i)->get_best_scale();
    else
        return 1.0;
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Goal &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

// end Goal.cpp
