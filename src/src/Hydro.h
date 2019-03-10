#ifndef HYDRO_H
#define HYDRO_H

/**
 * @file Hydro.h
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

#include "Table.h"
#include "Mesh.h"
#include "Cell.h"
#include <vector>

//-----------------------------------------------------------------------------

/// Holds material conditions within all Zone objects in the Mesh
class Hydro
{
private:

    /// Directory path to input data files for *this Hydro
    std::string path;

    /// Table of materials
    Table tbl;

    /**
     * @brief Number of time instants (postprocessing), or
     *        search cases + 1 (analysis);
     *        \n ntimes == 2 for a single instantaneous calculation
     */
    size_t ntimes;

    /**
     * @brief Number of time intervals (postprocessing), or
     *        search cases (analysis);
     *        \n nintervals == 1 for a single instantaneous calculation
     */
    size_t nintervals;

    /**
     * @brief Time instants in seconds; \n time[0] == 0.0 and time[1] == 1.0
     *        for a single instantaneous calculation
     */
    std::vector<double> time;

    /// Number of digits needed to represent Hydro::ntimes
    int ntd;

    /// "true" for analysis, "false" for postprocessing mode
    bool analysis;

    /// Number of Zone objects in the Mesh
    size_t nzones;

    /// The Mesh used only in analysis mode
    std::vector<const Cell *> cell;

    /// Number of analysis cases per Cell
    std::vector<size_t> ndim;

    /// "spherical" or "none" (from class Detector)
    std::string symmetry;

public:

    /// Default constructor
    Hydro(void);

    /**
     * @brief Parametrized constructor: connects *this with input data files
     * @param[in] analysis_in Initializes Hydro::analysis
     * @param[in] hydro_path Initializes Hydro::path
     * @param[in] table_path Path to Table (helps to initialize Hydro::tbl)
     * @param[in] table_fname Table filename (helps to initialize Hydro::tbl)
     * @param[in] symmetry_in Initializes Hydro::symmetry
     */
    Hydro(const bool analysis_in, const std::string &hydro_path,
          const std::string &table_path, const std::string &table_fname,
          const std::string &symmetry_in);

    /// Destructor
    ~Hydro(void);

    /**
     * @brief Getter for Hydro::path
     * @return Directory path to input data files for *this Hydro
     */
    std::string get_path(void) const;

    /**
     * @brief Getter for Table of materials
     * @return Reference to Hydro::tbl
     */
    const Table & get_table(void) const;

    /**
     * @brief Getter for Hydro::ndim
     * @return Number of analysis cases per Cell
     */
    std::vector<size_t> get_ndim(void) const;

    /**
     * @brief Getter for Hydro::ntimes
     * @return Number of time instants, or search cases + 1
     */
    size_t get_ntimes(void) const;

    /**
     * @brief Getter for Hydro::nintervals
     * @return Number of time intervals, or search cases
     */
    size_t get_nintervals(void) const;

    /**
     * @brief Getter for Hydro::ntd
     * @return Number of digits needed to represent Hydro::ntimes
     */
    int get_ntd(void) const;

    /** @brief Time instant (seconds) at index it (Hydro::time)
     *  @param[in] it Time instant index
     *  @return Time instant (seconds)
     */
    double time_at(const size_t it) const;

    /** @brief Length of time interval (seconds) at index it
     *  @param[in] it Time instant index
     *  @return Hydro::time[it+1] - Hydro::time[it] (seconds)
     */
    double dt_at(const size_t it) const;

    /** @brief Loads Grid, Mesh, Zone / Cell objects for time index it
     *  @param[in] it Time instant index
     *  @param[in,out] g Grid
     *  @param[in,out] m Mesh
     */
    void load_at(const size_t it, Grid &g, Mesh &m) const;

    /**
     * @brief String representation of a Hydro object
     * @return String representation of *this
     */
    std::string to_string(void) const;

    /**
     * @brief Getter for Hydro::analysis
     * @return "true" for analysis, "false" for postprocessing mode
     */
    bool get_analysis(void) const;

    /**
     * @brief Getter for Hydro::nzones
     * @return Number of Zone objects in the Mesh
     */
    size_t get_nzones(void) const;

    /**
     * @brief Setter for Hydro::symmetry (turns symmetry-based shortcuts on/off
     *        when recalculating the final best case in analysis mode,
     *        see Diagnostics::analyze)
     * @param[in] s "spherical" or "none" (from class Detector)
     */
    void set_symmetry(const std::string &s);

    /**
     * @brief Getter for Hydro::symmetry
     * @return "spherical" or "none" (from class Detector)
     */
    std::string get_symmetry(void) const;

};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Hydro to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Hydro object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const Hydro &o);

//-----------------------------------------------------------------------------

#endif // HYDRO_H
