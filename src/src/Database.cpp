/**
 * @file Database.cpp
 * @brief A collection of Detector objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 31 December 2014\n
 * Last modified on 6 October 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Database.h>

#include <constants.h>

#include <cmath>
#include <fstream>

//-----------------------------------------------------------------------------

void Database::read_grid_file(const std::string &fname, const int iwidth,
                              size_t &nbits, size_t &n,
                              std::vector<double> &v,
                              std::vector<std::string> &v_str)
{
    std::ifstream infile(fname.c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: file " << fname << " is not open in "
                  << "Database::read_grid_file" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::ifstream infile_str(fname.c_str());
    if (!infile_str.is_open())
    {
        std::cerr << "Error: file " << fname << " (str) is not open in "
                  << "Database::read_grid_file" << std::endl;
        exit(EXIT_FAILURE);
    }
    utils::find_line(infile, "Number of bits:");
    infile >> nbits;
    utils::find_line(infile, "Number of grid points:");
    infile >> n;
    utils::find_line(infile, "Grid points:");
    utils::find_line(infile_str, "Grid points:");
    for (size_t i = 0; i < n; ++i)
    {
        size_t j, k;
        double x;
        std::string s;
        infile >> j;
        infile_str >> j;
        if (iwidth == 0) // ne_man
        {
            infile >> x;
            v.emplace_back(std::move(x));
            infile_str >> s;
            v_str.emplace_back(utils::trim(s));
        }
        else // iwidth > 0
        {
            infile >> k;
            v.emplace_back(std::move(static_cast<double>(k)));
            v_str.emplace_back(utils::int_to_string(k, '0', iwidth));
        }
    }
    infile.close();
    infile.clear();
    infile_str.close();
    infile_str.clear();
}

//-----------------------------------------------------------------------------

double Database::nearest_ne(const std::string &froot,  const Table &tbl,
                            const double np, const unsigned short int nmat,
                            const std::vector<std::string> &mat,
                            const std::vector<double> &fp, size_t &ine) const
{
    StoichZbar ne_diff(this, tbl, froot, np, nmat, mat, fp);
    ine = utils::nearest_exh(0.0, ne_diff, nne);
    std::vector<double> zbars;
    zbars.reserve(nmat);
    load_zbars(froot, tbl, nmat, mat, ine, zbars);
    return utils::ne_charge_neut(np, nmat, fp, zbars);
}

//-----------------------------------------------------------------------------

Database::Database():
    tops_cmnd(""), path(""), tops_default(false),
    nbits_te(0), nte(0), te(), te_str(),
    nbits_tr(0), ntr(0), tr(), tr_str(),
    nbits_neman(0), nneman(0), neman(), neman_str(),
    nbits_neexp(0), nneexp(0), neexp(), neexp_str(),
    nbits_ne(0), nne(0), ne(), ne_str(),
    nhv(0), hv() {}

//-----------------------------------------------------------------------------

Database::Database(const std::string &t, const std::string &p, const bool td):
    tops_cmnd(t), path(p), tops_default(td),
    nbits_te(0), nte(0), te(), te_str(),
    nbits_tr(0), ntr(0), tr(), tr_str(),
    nbits_neman(0), nneman(0), neman(), neman_str(),
    nbits_neexp(0), nneexp(0), neexp(), neexp_str(),
    nbits_ne(0), nne(0), ne(), ne_str(),
    nhv(0), hv()
{
    if (t == "none")
    {
        read_grid_file(p + "grids/te_grid.txt", 0, nbits_te, nte, te, te_str);
        read_grid_file(p + "grids/tr_grid.txt", 0, nbits_tr, ntr, tr, tr_str);
        read_grid_file(p + "grids/ne_man_grid.txt", 0,
                       nbits_neman, nneman, neman, neman_str);
        read_grid_file(p + "grids/ne_exp_grid.txt", 2,
                       nbits_neexp, nneexp, neexp, neexp_str);
        // Assemble electron number density grid
        nbits_ne = nbits_neman + nbits_neexp;
        nne = nneman * nneexp;
        for (size_t iexp = 0; iexp < nneexp; ++iexp)
        {
            double e = pow(10.0, neexp.at(iexp));
            std::string estr = neexp_str.at(iexp);
            for (size_t iman = 0; iman < nneman; ++iman)
            {
                double x = neman.at(iman) * e;
                ne.emplace_back(std::move(x));
                std::string s = neman_str.at(iman) + "e" + estr;
                ne_str.emplace_back(std::move(s));
            }
        }
    } // t == "none"

    size_t nbits_hv;
    std::vector<std::string> hv_str;
    read_grid_file(p + "grids/hv_grid.txt", 0, nbits_hv, nhv, hv, hv_str);
}

//-----------------------------------------------------------------------------

std::string Database::get_tops_cmnd() const
{
    return tops_cmnd;
}

//-----------------------------------------------------------------------------

std::string Database::get_path() const
{
    return path;
}

//-----------------------------------------------------------------------------

bool Database::get_tops_default() const
{
    return tops_default;
}

//-----------------------------------------------------------------------------

size_t Database::get_nbits_te() const
{
    return nbits_te;
}

//-----------------------------------------------------------------------------

size_t Database::get_nte() const
{
    return nte;
}

//-----------------------------------------------------------------------------

double Database::get_te_at(const size_t i) const
{
    return te.at(i);
}

//-----------------------------------------------------------------------------

std::string Database::get_te_str_at(const size_t i) const
{
    return te_str.at(i);
}

//-----------------------------------------------------------------------------

std::string Database::nearest_te_str(const double x, size_t &i) const
{
    i = utils::nearest(x, te, nte, i);
    return get_te_str_at(i);
}

//-----------------------------------------------------------------------------

size_t Database::get_nbits_tr() const
{
    return nbits_tr;
}

//-----------------------------------------------------------------------------

size_t Database::get_ntr() const
{
    return ntr;
}

//-----------------------------------------------------------------------------

double Database::get_tr_at(const size_t i) const
{
    return tr.at(i);
}

//-----------------------------------------------------------------------------

std::string Database::get_tr_str_at(const size_t i) const
{
    return tr_str.at(i);
}

//-----------------------------------------------------------------------------

std::string Database::nearest_tr_str(const double x, size_t &i) const
{
    i = utils::nearest(x, tr, ntr, i);
    return get_tr_str_at(i);
}

//-----------------------------------------------------------------------------

size_t Database::get_nbits_neman() const
{
    return nbits_neman;
}

//-----------------------------------------------------------------------------

size_t Database::get_nneman() const
{
    return nneman;
}

//-----------------------------------------------------------------------------

double Database::get_neman_at(const size_t i) const
{
    return neman.at(i);
}

//-----------------------------------------------------------------------------

std::string Database::get_neman_str_at(const size_t i) const
{
    return neman_str.at(i);
}

//-----------------------------------------------------------------------------

size_t Database::get_nbits_neexp() const
{
    return nbits_neexp;
}

//-----------------------------------------------------------------------------

size_t Database::get_nneexp() const
{
    return nneexp;
}

//-----------------------------------------------------------------------------

double Database::get_neexp_at(const size_t i) const
{
    return neexp.at(i);
}

//-----------------------------------------------------------------------------

std::string Database::get_neexp_str_at(const size_t i) const
{
    return neexp_str.at(i);
}

//-----------------------------------------------------------------------------

size_t Database::get_nbits_ne() const
{
    return nbits_ne;
}

//-----------------------------------------------------------------------------

size_t Database::get_nne() const
{
    return nne;
}

//-----------------------------------------------------------------------------

double Database::get_ne_at(const size_t i) const
{
    return ne.at(i);
}

//-----------------------------------------------------------------------------

std::string Database::get_ne_str_at(const size_t i) const
{
    return ne_str.at(i);
}

//-----------------------------------------------------------------------------

size_t Database::get_nhv() const
{
    return nhv;
}

//-----------------------------------------------------------------------------

double Database::get_hv_at(const size_t i) const
{
    return hv.at(i);
}

//-----------------------------------------------------------------------------

std::string Database::to_string() const
{
    std::string s("Database path: " + get_path() + "\n");
    s += "nte:" + utils::int_to_string(get_nte(), ' ', cnst::INT_WIDTH) + "\n";
    s += "ntr:" + utils::int_to_string(get_ntr(), ' ', cnst::INT_WIDTH) + "\n";
    s += "nne:" + utils::int_to_string(get_nne(), ' ', cnst::INT_WIDTH) + "\n";
    s += "nhv:" + utils::int_to_string(get_nhv(), ' ', cnst::INT_WIDTH);
    return s;
}

//-----------------------------------------------------------------------------

void Database::load_zbars(const std::string &froot, const Table &tbl,
                          const unsigned short int nmat,
                          const std::vector<std::string> &mat,
                          const size_t ine, std::vector<double> &zb) const
{
    const std::string dirpath(path + "eos/");
    const std::string allparam(froot + get_ne_str_at(ine) + "pcc_zb.txt");
    for (unsigned short int i = 0; i < nmat; ++i)
    {
        std::string m(tbl.get_F(mat.at(i)));
        std::string fname(dirpath + m + "/" + m + allparam);
        std::ifstream infile(fname.c_str());
        if (!infile.is_open())
        {
            std::cerr << "Error: file " << fname << " is not open in "
                      << "Database::load_zbars" << std::endl;
            exit(EXIT_FAILURE);
        }
        utils::find_word(infile, "zbar");
        double zbar;
        infile >> zbar;
        zb.emplace_back(std::move(zbar));
        infile.close();
        infile.clear();
    }
}

//-----------------------------------------------------------------------------

NeData Database::find_ne(const Table &tbl, const double te_in, size_t &ite,
                         const double tr_in, size_t &itr,
                         const double np, const unsigned short int nmat,
                         const std::vector<std::string> &mat,
                         const std::vector<double> &fp,
                         size_t &ine) const
{
    NeData rv;
    rv.second = "_te" + nearest_te_str(te_in, ite) + "ev_tr"
              + nearest_tr_str(tr_in, itr) + "ev_ne";
    rv.first = nearest_ne(rv.second, tbl, np, nmat, mat, fp, ine);
    rv.second += get_ne_str_at(ine) + "pcc_";
    return rv;
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Database &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

StoichZbar::StoichZbar(const Database * const dp_in, const Table &tbl_in,
                       const std::string &frt_in,
                       const double nps_in,
                       const unsigned short int nms_in,
                       const std::vector<std::string> &mts_in,
                       const std::vector<double> &fps_in): dp(dp_in),
    tbl(tbl_in), frt(frt_in), nps(nps_in), nms(nms_in), mts(mts_in),
    fps(fps_in) {}

//-----------------------------------------------------------------------------

double StoichZbar::operator[](const size_t ine) const
{
    std::vector<double> zbars;
    zbars.reserve(nms);
    dp->load_zbars(frt, tbl, nms, mts, ine, zbars);
    return dp->get_ne_at(ine) - utils::ne_charge_neut(nps, nms, fps, zbars);
}

//-----------------------------------------------------------------------------

//  end Database.cpp
