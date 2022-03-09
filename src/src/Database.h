#ifndef LANL_ASC_PEM_DATABASE_H_
#define LANL_ASC_PEM_DATABASE_H_

/**
 * @file Database.h
 * @brief A collection of Detector objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 31 December 2014\n
 * Last modified on 8 March 2022
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Table.h>
#include <utils.h>

#include <iostream>
#include <string>
#include <vector>
#include <utility>

//-----------------------------------------------------------------------------

/** @brief Return value from the charge-neutrality constraint;\n
 * first: actual (not Table) electron number density in electrons/cm3,\n
 * second: string containing te, tr, ne labels for Database file access
 */
typedef std::pair<double, std::string> NeData;

//-----------------------------------------------------------------------------

/// Equation-of-State (EOS) and spectral grids, and access
class Database
{
public:

    /// Default constructor
    Database();

    /**
     * @brief Parametrized constructor:
     *        loads temperature, density, spectral grids
     * @param[in] t Path to TOPS executable (can be "none")
     * @param[in] p Path to grid data files (used if t == "none")
     * @param[in] td Flags whether p is "tops_default/" or not
     */
    Database(const std::string &t, const std::string &p,
             const bool td);

    /**
     * @brief Getter for TOPS path (Database::tops_cmnd)
     * @return Path to TOPS executable
     */
    std::string get_tops_cmnd() const;

    /**
     * @brief Getter for path to grid files (Database::path)
     * @return Path to grid files
     */
    std::string get_path() const;

    /**
     * @brief Getter for the Database::tops_default path flag
     * @return tops_default/ path flag
     */
    bool get_tops_default() const;
    
    /**
     * @brief Getter for number of bits in electron temperature grid
     *        (Database::nbits_te)
     * @return Number of bits in electron temperature grid
     */
    size_t get_nbits_te() const;

    /**
     * @brief Getter for number of points in electron temperature grid
     *        (Database::nte)
     * @return Number of points in electron temperature grid
     */
    size_t get_nte() const;

    /**
     * @brief Getter for electron temperature grid point
     *        (Database::te)
     * @param[in] i Index
     * @return Electron temperature grid value at index i
     */
    double get_te_at(const size_t i) const;

    /**
     * @brief Getter for electron temperature grid point as string
     *        (Database::te)
     * @param[in] i Index
     * @return Electron temperature grid value at index i as string
     */
    std::string get_te_str_at(const size_t i) const;

    /**
     * @brief Nearest electron temperature grid point as string
     * @param[in] x Electron temperature
     * @param[in,out] i Index (of the returned value on exit)
     * @return Electron temperature grid value as string
     */
    std::string nearest_te_str(const double x, size_t &i) const;

    /**
     * @brief Getter for number of bits in radiation temperature grid
     *        (Database::nbits_tr)
     * @return Number of bits in radiation temperature grid
     */
    size_t get_nbits_tr() const;

    /**
     * @brief Getter for number of points in radiation temperature grid
     *        (Database::ntr)
     * @return Number of points in radiation temperature grid
     */
    size_t get_ntr() const;

    /**
     * @brief Getter for radiation temperature grid point
     *        (Database::tr)
     * @param[in] i Index
     * @return Radiation temperature grid value at index i
     */
    double get_tr_at(const size_t i) const;

    /**
     * @brief Getter for radiation temperature grid point as string
     *        (Database::tr)
     * @param[in] i Index
     * @return Radiation temperature grid value at index i as string
     */
    std::string get_tr_str_at(const size_t i) const;

    /**
     * @brief Nearest radiation temperature grid point as string
     * @param[in] x Radiation temperature
     * @param[in,out] i Index (of the returned value on exit)
     * @return Radiation temperature grid value as string
     */
    std::string nearest_tr_str(const double x, size_t &i) const;

    /**
     * @brief Getter for number of bits in electron number density grid
     *        (mantissa, Database::nbits_neman)
     * @return Number of bits in electron number density grid (mantissa)
     */
    size_t get_nbits_neman() const;

    /**
     * @brief Getter for number of points in electron number density grid
     *        (mantissa, Database::nneman)
     * @return Number of points in electron number density grid (mantissa)
     */
    size_t get_nneman() const;

    /**
     * @brief Getter for electron number density grid point
     *        (mantissa, Database::neman)
     * @param[in] i Index
     * @return Electron number density grid value at index i (mantissa)
     */
    double get_neman_at(const size_t i) const;

    /**
     * @brief Getter for electron number density grid point as string
     *        (mantissa, Database::neman)
     * @param[in] i Index
     * @return Electron number density grid value at index i as string
     *         (mantissa)
     */
    std::string get_neman_str_at(const size_t i) const;

    /**
     * @brief Getter for number of bits in electron number density grid
     *        (exponent, Database::nbits_neexp)
     * @return Number of bits in electron number density grid (exponent)
     */
    size_t get_nbits_neexp() const;

    /**
     * @brief Getter for number of points in electron number density grid
     *        (exponent, Database::nneexp)
     * @return Number of points in electron number density grid (exponent)
     */
    size_t get_nneexp() const;

    /**
     * @brief Getter for electron number density grid point
     *        (exponent, Database::neexp)
     * @param[in] i Index
     * @return Electron number density grid value at index i (exponent)
     */
    double get_neexp_at(const size_t i) const;

    /**
     * @brief Getter for electron number density grid point as string
     *        (exponent, Database::neexp)
     * @param[in] i Index
     * @return Electron number density grid value at index i as string
     *         (exponent)
     */
    std::string get_neexp_str_at(const size_t i) const;

    /**
     * @brief Getter for number of bits in electron number density grid
     *        (Database::nbits_ne)
     * @return Number of bits in electron number density grid
     */
    size_t get_nbits_ne() const;

    /**
     * @brief Getter for number of points in electron number density grid
     *        (Database::nne)
     * @return Number of points in electron number density grid
     */
    size_t get_nne() const;

    /**
     * @brief Getter for electron number density grid point
     *        (Database::ne)
     * @param[in] i Index
     * @return Electron number density grid value at index i
     */
    double get_ne_at(const size_t i) const;

    /**
     * @brief Getter for electron number density grid point as string
     *        (Database::ne)
     * @param[in] i Index
     * @return Electron number density grid value at index i as string
     */
    std::string get_ne_str_at(const size_t i) const;

    /**
     * @brief Getter for number of points in photon energy grid (Database::nhv)
     * @return Number of points in photon energy grid
     */
    size_t get_nhv() const;

    /**
     * @brief Getter for photon energy grid point (Database::hv)
     * @param[in] i Index
     * @return Photon energy grid value at index i
     */
    double get_hv_at(const size_t i) const;

    /**
     * @brief String representation of a Database object
     * @return String representation of *this
     */
    std::string to_string() const;

    /**
     * @brief Retrieves average ionization for all materials
     * @param[in] froot File-name root based on te, tr
     * @param[in] tbl Table of materials
     * @param[in] nmat Number of materials in the Zone
     * @param[in] mat List of materials in the Zone
     * @param[in] ine Electron number density Database index
     * @param[out] zb Material average ionizations from Database at index ine
     *             (zb is assumed to be empty on entry)
     */
    void load_zbars(const std::string &froot, const Table &tbl,
                    const unsigned short int nmat,
                    const std::vector<std::string> &mat,
                    const size_t ine, std::vector<double> &zb) const;

    /**
     * @brief Finds common electron number density that is consistent with
     *        the charge-neutrality constraint for given temperature and
     *        stoichiometry of the Zone
     * @param[in] tbl Table of materials
     * @param[in] te_in Electron temperature in the Zone
     * @param[in,out] ite Electron temperature Database index
     * @param[in] tr_in Radiation temperature in the Zone
     * @param[in,out] itr Radiation temperature Database index
     * @param[in] np Total particle number density (particles/cm3)
     * @param[in] nmat Number of materials in the Zone
     * @param[in] mat List of materials in the Zone
     * @param[in] fp Fractional populations of materials
     * @param[in,out] ine Electron number density Database index
     * @return Pair:\n first: actual (not Table) electron number density in
     *         electrons/cm3,\n
     * second: string containing te, tr, ne labels for Database file access
     */
    NeData find_ne(const Table &tbl, const double te_in, size_t &ite,
                   const double tr_in, size_t &itr,
                   const double np, const unsigned short int nmat,
                   const std::vector<std::string> &mat,
                   const std::vector<double> &fp,
                   size_t &ine) const;


private:

    /// Path to TOPS executable; "none", if TOPS is not used
    std::string tops_cmnd;

    /// Directory path to *this Database
    std::string path;

    /// "tops_default/" path flag
    bool tops_default;

    /// Number of bits in electron temperature grid
    size_t nbits_te;

    /// Number of points in electron temperature grid
    size_t nte;

    /// Electron temperature grid (eV)
    std::vector<double> te;

    /// Electron temperature grid (eV) as strings
    std::vector<std::string> te_str;

    /// Number of bits in radiation temperature grid
    size_t nbits_tr;

    /// Number of points in radiation temperature grid
    size_t ntr;

    /// Radiation temperature grid (eV)
    std::vector<double> tr;

    /// Radiation temperature grid (eV) as strings
    std::vector<std::string> tr_str;

    /// Number of bits in electron number density grid (mantissa)
    size_t nbits_neman;

    /// Number of points in electron number density grid (mantissa)
    size_t nneman;

    /// Electron number density grid (mantissa)
    std::vector<double> neman;

    /// Electron number density grid (mantissa) as strings
    std::vector<std::string> neman_str;

    /// Number of bits in electron number density grid (exponent)
    size_t nbits_neexp;

    /// Number of points in electron number density grid (exponent)
    size_t nneexp;

    /// Electron number density grid (exponent)
    std::vector<double> neexp;

    /// Electron number density grid (exponent) as strings
    std::vector<std::string> neexp_str;

    /// Number of bits in electron number density grid
    size_t nbits_ne;

    /// Number of points in electron number density grid
    size_t nne;

    /// Electron number density grid (electrons/cm3)
    std::vector<double> ne;

    /// Electron number density grid (electrons/cm3) as strings
    std::vector<std::string> ne_str;

    /// Number of points in photon energy grid */
    size_t nhv;

    /// Photon energy grid (eV)
    std::vector<double> hv;

    /**
     * @brief Read a file with grid information
     * @param[in] fname Name of input file with grid information
     * @param[in] iwidth Width used in int-to-string conversion of grid data;
     *            0, if grid data are read as doubles
     * @param[in] nbits Number of bits needed to represent the grid size
     * @param[in] n Number of grid points
     * @param[out] v The grid of values (as numbers)
     * @param[out] v_str The grid of values (as strings)
     */
    void read_grid_file(const std::string &fname, const int iwidth,
                        size_t &nbits, size_t &n,
                        std::vector<double> &v,
                        std::vector<std::string> &v_str);

    /**
     * @brief Search EOS database for the common electron number density
     *        shared by all materials in the Zone and consistent with the
     *        charge-neutrality constraint
     * @param[in] froot File-name root based on te, tr
     * @param[in] tbl Table of materials
     * @param[in] np Total atom number density (ions/cm3)
     * @param[in] nmat Number of materials in the Zone
     * @param[in] mat List of materials in the Zone
     * @param[in] fp Fractional populations of materials in the Zone
     * @param[in,out] ine Electron number density Database index
     * @return Mixed electron number density closest to a Database point
     * @todo Consider replacing the exhaustive search with a (faster) binary
     *       search seeded by the previously obtained value of ine
     */
    double nearest_ne(const std::string &froot, const Table &tbl,
                      const double np, const unsigned short int nmat,
                      const std::vector<std::string> &mat,
                      const std::vector<double> &fp, size_t &ine) const;
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Database to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Database object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const Database &o);

//-----------------------------------------------------------------------------

/** @brief Charge-neutrality constraint helper class
 *
 * Allows nearest_ne() to use nearest() from utils.h,
 * which requires "double operator [](size_t)" method to be available
 */
class StoichZbar
{
public:

    /**
     * @brief Parametrized constructor
     * @param[in] dp_in Pointer to parent Database object
     * @param[in] tbl_in Reference to Table object
     * @param[in] frt_in File-name root based on te, tr
     * @param[in] nps_in Total particle number density (particles/cm3)
     * @param[in] nms_in Number of materials
     * @param[in] mts_in Material IDs
     * @param[in] fps_in Fractional populations of materials
     */
    StoichZbar(const Database * const dp_in, const Table &tbl_in,
               const std::string &frt_in,
               const double nps_in,
               const unsigned short int nms_in,
               const std::vector<std::string> &mts_in,
               const std::vector<double> &fps_in);

    /**
     * @brief Copy constructor
     * @param[in] o StoichZbar object to be copied (shallow copy of dp OK)
     */
    StoichZbar(const StoichZbar &o) = default;

    /**
     * @brief Overloaded assignment operator
     * @param[in] o StoichZbar object to be copied (shallow copy of dp OK)
     * @return Reference to copied object
     */
    StoichZbar &operator=(const StoichZbar &o) = delete;

    /**
     * @brief Charge-neutrality constraint
     * @param[in] ine Index of electron-density point from Database
     * @return Difference between Table electron density ne[ine] and the one
     * from charge neutrality for the given temperatures and atom densities:
     * \f$n_e-n_p\sum_{i=1}^{nms}f_i\;\bar{z}_i(T_e,T_r,n_e)\f$, which we will
     * want to equal zero within the resolution of the Database
     */
    double operator [](const size_t ine) const;


private:
    
    /// Pointer to parent Database object
    const Database *dp;
    
    /// Reference to Table object
    const Table &tbl;
    
    /// File-name root based on te, tr
    std::string frt;
    
    /// Total particle number density (particles/cm3)
    double nps;
    
    /// Number of materials
    unsigned short int nms;
    
    /// Material IDs
    std::vector<std::string> mts;
    
    /// Fractional populations of materials
    std::vector<double> fps;
};

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_DATABASE_H_
