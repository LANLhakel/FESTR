/**
 * @file Hydro.cpp
 * @brief Holds material conditions within all Zone objects in the Mesh
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 7 January 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Hydro.h"
#include "Table.h"
#include "utilities.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>

//-----------------------------------------------------------------------------

Hydro::Hydro(void):
    path(""), tbl(), ntimes(0), nintervals(0), time(), ntd(0),
    analysis(false), nzones(0), cell(), ndim(), symmetry("none")
{}

//-----------------------------------------------------------------------------

Hydro::Hydro(const bool analysis_in, const std::string &hydro_path,
             const std::string &table_path, const std::string &table_fname,
             const std::string &symmetry_in):
    path(hydro_path), tbl(hydro_path, table_path, table_fname),
    ntimes(0), nintervals(0), time(), ntd(0),
    analysis(analysis_in), nzones(0), cell(), ndim(), symmetry(symmetry_in)
{
    std::string fname;

    if (analysis) // read the (one-and-only) Mesh for analysis
    {
        fname = path + "mesh_0.txt";
        std::ifstream geometry(fname.c_str());
        if (!geometry.is_open())
        {
            std::cerr << "Error: file " << fname << " is not open in "
                      << "Hydro::Hydro(parametrized)" << std::endl;
            exit(EXIT_FAILURE);
        }
        utils::find_word(geometry, "Number_of_zones");
        geometry >> nzones;
        geometry.close();
        geometry.clear();
        cell.reserve(nzones);

        fname = path + "time_0.txt";
        std::ifstream material(fname.c_str());
        if (!material.is_open())
        {
            std::cerr << "Error: file " << fname << " is not open in "
                      << "Hydro::Hydro(parametrized)" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (symmetry == "spherical")
            nintervals = 0; // initialize for addition
        else // symmetry == "none"
            nintervals = 1; // initialize for multiplication

        Cell *cellptr;
        size_t nx;
        for (size_t i = 0; i < nzones; ++i)
        {
            cellptr = new Cell(material);
            cell.push_back(cellptr);
            nx = cellptr->get_ncases();
            ndim.push_back(nx);
            if (symmetry == "spherical")
                nintervals += nx;
            else // symmetry == "none"
                nintervals *= nx;
        }
        ntimes = nintervals + 1;
        time.push_back(0.0);
        time.push_back(1.0);
        ntd = 1;

        material.close();
        material.clear();

    }
    else // !analysis; read time instants for postprocessing
    {
        fname = hydro_path + "times.txt";
        std::ifstream infile(fname.c_str());
        if (!infile.is_open())
        {
            std::cerr << "Error: file " << fname << " is not open in "
                      << "Hydro::Hydro(parametrized)" << std::endl;
            exit(EXIT_FAILURE);
        }
        utils::find_line(infile, "# start");
        infile >> ntimes;
        ntd = utils::ndigits(ntimes);
        nintervals = ntimes - 1;
        time.reserve(ntimes);
        size_t i, j;
        double t;
        for (i = 0; i < ntimes; ++i)
        {
            infile >> j >> t;
            time.push_back(t);
        }
        infile.close();
        infile.clear();
    } // analysis
}

//-----------------------------------------------------------------------------

Hydro::~Hydro(void)
{
    path = "";
    tbl.clear();
    ntimes = 0;
    nintervals = 0;
    time.clear();
    ntd = 0;
    analysis = false;
    nzones = 0;
    for_each(cell.begin(), cell.end(), utils::DeleteObject());
    cell.clear();
    ndim.clear();
}

//-----------------------------------------------------------------------------

std::string Hydro::get_path(void) const {return path;}

//-----------------------------------------------------------------------------

const Table & Hydro::get_table(void) const {return tbl;}

//-----------------------------------------------------------------------------

std::vector<size_t> Hydro::get_ndim(void) const {return ndim;}

//-----------------------------------------------------------------------------

size_t Hydro::get_ntimes(void) const {return ntimes;}

//-----------------------------------------------------------------------------

size_t Hydro::get_nintervals(void) const {return nintervals;}

//-----------------------------------------------------------------------------

int Hydro::get_ntd(void) const {return ntd;}

//-----------------------------------------------------------------------------

double Hydro::time_at(const size_t it) const {return time.at(it);}

//-----------------------------------------------------------------------------

double Hydro::dt_at(const size_t it) const
{return time.at(it+1) - time.at(it);}

//-----------------------------------------------------------------------------

void Hydro::load_at(const size_t i, Grid &g, Mesh &m) const
{
    std::string tlabel;
    if (analysis) // analysis of case #i
    {
        tlabel = "0";
        if (g.size() == 0) g.load(path, tlabel);
        if (m.size() == 0) m.load(path, tlabel);
        
        if (symmetry == "spherical")
        {
            std::pair<size_t, size_t> pr = utils::one_to_two(ndim, i);
            size_t izone = pr.first;
            size_t icase = pr.second;
            Cell *cptr = const_cast<Cell *>(cell.at(izone));
            CellEOS e = cptr->get_cell_eos(icase);
            Zone *zptr = const_cast<Zone *>(m.get_zone(izone));
            zptr->set_te(e.te);
            zptr->set_tr(e.tr);
            zptr->set_nmat(e.nmat);
            zptr->set_mat(e.mat);
            zptr->set_fp(e.fp);
        }
        else // symmetry == "none"
        {
            std::vector<size_t> indx = utils::one_to_many(ndim, i);
            // seed Mesh with CellEOS data
            for (size_t izone = 0; izone < nzones; ++izone)
            {
                Cell *cptr = const_cast<Cell *>(cell.at(izone));
                CellEOS e = cptr->get_cell_eos(indx.at(izone));
                Zone *zptr = const_cast<Zone *>(m.get_zone(izone));
                zptr->set_te(e.te);
                zptr->set_tr(e.tr);
                zptr->set_nmat(e.nmat);
                zptr->set_mat(e.mat);
                zptr->set_fp(e.fp);
            }
        }
    }
    else // postprocessing time interval [i, i+1]
    {
        tlabel = utils::int_to_string(i, '0', ntd);
        g.load(path, tlabel);
        m.load(path, tlabel);
    }
}

//-----------------------------------------------------------------------------

std::string Hydro::to_string(void) const
{
    std::string s("");
    return s;
}

//-----------------------------------------------------------------------------

bool Hydro::get_analysis(void) const {return analysis;}

//-----------------------------------------------------------------------------

size_t Hydro::get_nzones(void) const {return nzones;}

//-----------------------------------------------------------------------------

void Hydro::set_symmetry(const std::string &s) {symmetry = s;}

//-----------------------------------------------------------------------------

std::string Hydro::get_symmetry(void) const {return symmetry;}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Hydro &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

// end Hydro.cpp
