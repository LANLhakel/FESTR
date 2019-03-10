/**
 * @file Table.cpp
 * @brief Atomic data for materials
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 9 January 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Table.h"
#include "constants.h"
#include "utilities.h"
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>

//-----------------------------------------------------------------------------

Table::Table(void): d() {}

//-----------------------------------------------------------------------------

Table::Table(const std::string &hydro_path, const std::string &table_path,
             const std::string &table_fname): d()
{
    d.clear();
    std::ifstream matfile((hydro_path + "materials.txt").c_str());
    if (!matfile.is_open())
    {
        std::cerr << "Error: file " << hydro_path << "materials.txt "
                  << "is not open in "
                  << "Table::Table(parametrized)" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string sin;
    std::set<std::string> used_mat;
    while (true)
    {
        matfile >> sin;
        used_mat.insert(sin);
        if (matfile.eof()) break;
    }
    matfile.close();
    matfile.clear();

    std::string fname(table_path + table_fname);
    std::ifstream infile(fname.c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: file " << fname << " is not open in "
                  << "Table::Table(parametrized)" << std::endl;
        exit(EXIT_FAILURE);
    }
    utils::find_line(infile, "Material     Z     Atomic weight         File handle");
    std::string fin;
    int zin;
    double ain;
    while (true)
    {
        infile >> sin;
        if (infile.eof()) break;
        infile >> zin >> ain >> fin;
        if (used_mat.find(sin) != used_mat.end())
            d.insert(TableMap::value_type(sin, TableData(zin, ain, fin) ));
    }
    infile.close();
    infile.clear();
}

//-----------------------------------------------------------------------------

Table::~Table(void) {clear();}

//-----------------------------------------------------------------------------

void Table::clear(void) {d.clear();}

//-----------------------------------------------------------------------------

size_t Table::size(void) const {return d.size();}

//-----------------------------------------------------------------------------

int Table::get_Z(const std::string s) const
{
    TableMap::const_iterator it(d.find(s));
    if (it == d.end())
        throw std::out_of_range(s + " is not present in Table");
    else
        return it->second.z;
}

//-----------------------------------------------------------------------------

double Table::get_A(const std::string s) const
{
    TableMap::const_iterator it(d.find(s));
    if (it == d.end())
        throw std::out_of_range(s + " is not present in Table");
    else
        return it->second.a;
}

//-----------------------------------------------------------------------------

int Table::get_N(const std::string s) const
{
    TableMap::const_iterator it(d.find(s));
    if (it == d.end())
        throw std::out_of_range(s + " is not present in Table");
    else
    {
        TableData t(it->second);
        return utils::nint(t.a) - t.z;
    }
}

//-----------------------------------------------------------------------------

std::string Table::get_F(const std::string s) const
{
    TableMap::const_iterator it(d.find(s));
    if (it == d.end())
        throw std::out_of_range(s + " is not present in Table");
    else
        return it->second.f;
}

//-----------------------------------------------------------------------------

// end Table.cpp
