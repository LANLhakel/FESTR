/**
 * @file Cell.cpp
 * @brief Class Zone reduced to hold only materials' search ranges for analysis
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 4 July 2015\n
 * Last modified on 28 January 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Cell.h>

#include <constants.h>
#include <utils.h>

#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>

//-----------------------------------------------------------------------------

Cell::Cell(): np_unit("none"),
    my_id(0), telow(-1.0), tehigh(-1.0), trlow(-1.0), trhigh(-1.0),
    nmat(0), mat(), fplow(), fphigh(), nte(0), ntr(0), nfp(), nall(),
    gte(), gtr(), gnp(), gfp(), tegrid(), trgrid(), fpgrid() {}

//-----------------------------------------------------------------------------

Cell::Cell(const size_t my_id_in): np_unit("none"),
    my_id(my_id_in), telow(-1.0), tehigh(-1.0), trlow(-1.0), trhigh(-1.0),
    nmat(0), mat(), fplow(), fphigh(), nte(0), ntr(0), nfp(), nall(),
    gte(), gtr(), gnp(), gfp(), tegrid(), trgrid(), fpgrid() {}

//-----------------------------------------------------------------------------

Cell::Cell(std::ifstream &material): np_unit("none"),
    my_id(0), telow(-1.0), tehigh(-1.0), trlow(-1.0), trhigh(-1.0),
    nmat(0), mat(), fplow(), fphigh(), nte(0), ntr(0), nfp(), nall(),
    gte(), gtr(), gnp(), gfp(), tegrid(), trgrid(), fpgrid()
{
    utils::find_word(material, "Zone");
    material >> my_id;

    utils::find_word(material, "te");
    material >> telow >> tehigh >> nte >> gte;
    if (nte < 2) nte = 1;
    tegrid = utils::get_grid(telow, tehigh, nte, gte, false);
    nte = tegrid.size();
    nall.emplace_back(nte);

    utils::find_word(material, "tr");
    material >> trlow >> trhigh >> ntr >> gtr;
    if (ntr < 2) ntr = 1;
    trgrid = utils::get_grid(trlow, trhigh, ntr, gtr, false);
    ntr = trgrid.size();
    nall.emplace_back(ntr);

    utils::find_word(material, "nmat");
    material >> nmat;
    utils::find_line(material, "material densities (particles/cm3)");
    size_t nproduct = 1;
    for (unsigned short int i = 0; i < nmat; ++i)
    {
        std::string s, gx;
        double xlow, xhigh;
        size_t nx;
        material >> s >> xlow >> xhigh >> nx >> gx;
        mat.emplace_back(s);
        fplow.emplace_back(xlow);
        fphigh.emplace_back(xhigh);
        if (nx < 2) nx = 1;
        gfp.emplace_back(gx);
        std::vector<double> fploc(utils::get_grid(xlow, xhigh, nx, gx, true));
        fpgrid.insert( FpopMap::value_type(s, fploc) );
        nx = fploc.size();
        nproduct *= nx;
        nfp.emplace_back(std::move(nx));
    }
    nall.emplace_back(std::move(nproduct));
}

//-----------------------------------------------------------------------------

void Cell::set_id(const size_t my_id_in) {my_id = my_id_in;}

//-----------------------------------------------------------------------------

size_t Cell::get_id() const {return my_id;}

//-----------------------------------------------------------------------------

std::string Cell::to_string() const
{
    std::string s("Cell");
    s += utils::int_to_string(my_id, ' ', cnst::INT_WIDTH) + "\n";

    s += "te" + utils::double_to_string(telow) + utils::double_to_string(tehigh);
    s += " " + utils::int_to_string(nte, ' ', cnst::INT_WIDTH) + " " + gte;
    s += " eV\n";

    s += "tr" + utils::double_to_string(trlow) + utils::double_to_string(trhigh);
    s += " " + utils::int_to_string(ntr, ' ', cnst::INT_WIDTH) + " " + gtr;
    s += " eV\n";

    s += "nmat " + utils::int_to_string(nmat, ' ', cnst::INT_WIDTH) + "\n";
    s += "material densities (particles/cm3)";
    for (size_t i = 0; i < nmat; ++i)
    {
        s += "\n" + mat.at(i);
        s += utils::double_to_string(fplow.at(i));
        s += utils::double_to_string(fphigh.at(i));
        s += " " + utils::int_to_string(nfp.at(i), ' ', cnst::INT_WIDTH);
        s += " " + gfp.at(i);
    }
    return s;
}

//-----------------------------------------------------------------------------

size_t Cell::get_nte() const {return nte;}

//-----------------------------------------------------------------------------

std::vector<double> Cell::get_tegrid() const {return tegrid;}

//-----------------------------------------------------------------------------

size_t Cell::get_ntr() const {return ntr;}

//-----------------------------------------------------------------------------

std::vector<double> Cell::get_trgrid() const {return trgrid;}

//-----------------------------------------------------------------------------

unsigned short int Cell::get_nmat() const {return nmat;}

//-----------------------------------------------------------------------------

std::vector<size_t> Cell::get_nfp() const {return nfp;}

//-----------------------------------------------------------------------------

FpopMap Cell::get_fpgrid() const {return fpgrid;}

//-----------------------------------------------------------------------------

CellEOS Cell::get_eos(const size_t ite, const size_t itr, const size_t ifp)
{
    CellEOS rv;
    rv.te = tegrid.at(ite);
    rv.tr = trgrid.at(itr);
    rv.nmat = nmat;
    try
    {
        if (nmat > 0)
        {
            std::vector<size_t> indx = utils::one_to_many(nfp, ifp);
            size_t j;
            std::string m;
            for (size_t i = 0; i < nmat; ++i)
            {
                m = mat.at(i);
                j = indx.at(i);
                rv.fp.emplace_back(fpgrid[m].at(j));
                rv.mat.emplace_back(std::move(m));
            }
        }
    }
    catch (const std::out_of_range &oor)
    {
        if (nmat != 0)
        {
            std::cerr << "Error in Cell.get_eos(): "
                      << "nfp is empty, but nmat is not zero" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return rv;
}

//-----------------------------------------------------------------------------

std::vector<size_t> Cell::get_nall() const {return nall;}

//-----------------------------------------------------------------------------

CellEOS Cell::get_cell_eos(const size_t i)
{
    std::vector<size_t> indx = utils::one_to_many(nall, i);
    return get_eos(indx.at(0), indx.at(1), indx.at(2));
}

//-----------------------------------------------------------------------------

size_t Cell::get_ncases() const
{
    const size_t ONE(1);
    return
    std::accumulate(nall.begin(), nall.end(), ONE, std::multiplies<size_t>() );
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Cell &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

//  end Cell.cpp
