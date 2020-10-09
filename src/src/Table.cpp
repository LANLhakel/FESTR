/**
 * @file Table.cpp
 * @brief Atomic data for materials
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 9 January 2015\n
 * Last modified on 8 October 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Table.h>

#include <constants.h>
#include <utils.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <stdexcept>

//-----------------------------------------------------------------------------

Table::Table(): d() {}

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

void Table::clear()
{
    d.clear();
}

//-----------------------------------------------------------------------------

size_t Table::size() const
{
    return d.size();
}

//-----------------------------------------------------------------------------

int Table::get_Z(const std::string s) const
{
    auto it(d.find(s));
    if (it == d.end())
        throw std::out_of_range(s + " is not present in Table");
    else
        return it->second.z;
}

//-----------------------------------------------------------------------------

double Table::get_A(const std::string s) const
{
    auto it(d.find(s));
    if (it == d.end())
        throw std::out_of_range(s + " is not present in Table");
    else
        return it->second.a;
}

//-----------------------------------------------------------------------------

int Table::get_N(const std::string s) const
{
    auto it(d.find(s));
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
    auto it(d.find(s));
    if (it == d.end())
        throw std::out_of_range(s + " is not present in Table");
    else
        return it->second.f;
}

//-----------------------------------------------------------------------------

std::vector<double> Table::atom_to_mass(const std::vector<std::string> &mat,
                                        const std::vector<double> &a) const
{
    size_t n = a.size();
    std::vector<double> m(n, 0.0);
    double s = 0.0;
    for (size_t i = 0; i < n; ++i) s += a[i] * get_A(mat[i]);
    for (size_t i = 0; i < n; ++i) m[i] = a[i] * get_A(mat[i]) / s;

    return m;
}

//-----------------------------------------------------------------------------

std::vector<double> Table::mass_to_atom(const std::vector<std::string> &mat,
                                        const std::vector<double> &m) const
{
    size_t n = m.size();
    std::vector<double> a(n, 0.0);
    double s = 0.0;
    for (size_t i = 0; i < n; ++i) s += m[i] / get_A(mat[i]);
    for (size_t i = 0; i < n; ++i) a[i] = m[i] / get_A(mat[i]) / s;

    return a;
}

//-----------------------------------------------------------------------------

std::vector<int> Table::get_elements() const
{
    std::set<int> elem;
    for (auto it = d.cbegin(); it != d.cend(); ++it) elem.insert(it->second.z);

    size_t nelem = elem.size();
    std::vector<int> rv(nelem, 0);
    size_t j = 0;
    for (auto it = elem.cbegin(); it != elem.cend(); ++it) rv[j++] = *it;

    return rv;
}

//-----------------------------------------------------------------------------

//  end Table.cpp
