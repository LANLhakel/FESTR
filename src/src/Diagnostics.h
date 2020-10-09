#ifndef LANL_ASC_PEM_DIAGNOSTICS_H_
#define LANL_ASC_PEM_DIAGNOSTICS_H_

/**
 * @file Diagnostics.h
 * @brief A collection of Detector objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 5 February 2015\n
 * Last modified on 28 January 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Database.h>
#include <Detector.h>
#include <Goal.h>

#include <string>
#include <vector>

//-----------------------------------------------------------------------------

/// A collection of Detector objects
class Diagnostics
{
public:

    /// Progress indentation level
    int level;

    /// Frequency of Progress prints
    size_t freq;

    /// Path to *this Diagnostics description
    std::string path;

    /// Path to output files
    std::string outpath;

    /// List of Detectors
    std::vector<Detector> det;

//-----------------------------------------------------------------------------

    /// Default constructor
    Diagnostics();

    /**
     * @brief Parametrized constructor
     * @param[in] level_in Progress indentation level
     * @param[in] diag_path Path to Diagnostics description
     * @param[in] hydro_path Path to Hydro description
     * @param[in] out_path Path for output files
     * @param[in] d Reference to Database object
     */
    Diagnostics(const int level_in,
                const std::string &diag_path,
                const std::string &hydro_path,
                const std::string &out_path,
                const Database &d);

    /**
     * @brief Number of Detectors in *this Diagnostics
     * @return Number of Detectors
     */
    size_t size() const;

    /**
     * @brief String representation of a Diagnostics object
     * @return String representation of *this
     */
    std::string to_string() const;

    /**
     * @brief Name of Detector i
     * @param[in] i Index of Detector within *this Diagnostics
     * @return det[i]
     */
    std::string get_name(const size_t i) const;

    /**
     * @brief Index of Detector according to its name
     * @param[in] s Name of Detector
     * @return Index of Detector named s
     */
    size_t get_index(const std::string &s) const;

    /**
     * @brief Runs all postprocessing time steps
     * @param[in] d Reference to Database object
     * @param[in] h Reference to Hydro object
     * @param[in] gol Reference to Goal object
     */
    void postprocess(const Database &d, const Hydro &h, Goal &gol);

    /**
     * @brief Runs all analysis cases
     * @param[in] d Reference to Database object
     * @param[in] h Reference to Hydro object
     * @param[in] gol Reference to Goal object
     */
    void analyze(const Database &d, Hydro &h, Goal &gol);

    /**
     * @brief Runs all post-processing time steps or analysis cases
     * @param[in] d Reference to Database object
     * @param[in] h Reference to Hydro object
     * @param[in] gol Reference to Goal object
     */
    void execute(const Database &d, Hydro &h, Goal &gol);
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Diagnostics to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Diagnostics object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const Diagnostics &o);

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_DIAGNOSTICS_H
