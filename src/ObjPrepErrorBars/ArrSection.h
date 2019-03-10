#ifndef ARRSECTION_H
#define ARRSECTION_H

/**
 * @file ArrSection.h
 * @brief Array of doubles with arbitrary index range
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 25 July 2016\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <vector>
#include <string>

//-----------------------------------------------------------------------------

/// Array of doubles
class ArrSection
{
private:

    /// Lower index limit
    int nlow;

    /// Upper index limit
    int nup;

    /// Number of values in v
    int n;

    /// Flag for padding with zeros outside given index range
    bool pad0;

    /// Array of values v
    std::vector<double> v;

public:

    /// Default constructor
    ArrSection(void);

    /**
     * @brief Parametrized constructor:
     * sets array limits to nlow_in:nup_in, sets the padding flag,
     * and fills the array with zeroes
     * @param[in] nlow_in Lower index limit
     * @param[in] nup_in Upper index limit
     * @param[in] p0 Flag for padding with zeros outside given index range
     */
    ArrSection(int nlow_in, int nup_in, const bool p0);

    /// Destructor
    ~ArrSection(void);

    /**
     * @brief Getter for the lower index limit (ArrSection::nlow)
     * @return Lower index limit
     */
    int get_lower_limit(void) const;

    /**
     * @brief Getter for the upper index limit (ArrSection::nup)
     * @return Upper index limit
     */
    int get_upper_limit(void) const;

    /**
     * @brief Getter for number of values (ArrSection::n)
     * @return Size of the array
     */
    int size(void) const;

    /**
     * @brief Setter/Getter for i-th component (ArrSection::v)
     * @param[in] i v-index (must be within ArrSection::nlow, ArrSection::nup)
     * @return \f$v_i\f$
     */
    double & operator [](const int i);

    /**
     * @brief Getter for i-th component (ArrSection::v)
     * @param[in] i v-index (out-of-range according to ArrSection::pad0)
     * @return \f$v_i\f$ or padding value for out-of-range index
     */
    double operator ()(const int i) const;

    /**
     * @brief Absolute difference between two arrays
     * @param[in] o ArrSection
     * @return See Definition
     */
    double abs_diff(const ArrSection &o) const;

    /**
     * @brief String representation of an ArrSection object
     * @return String representation of *this
     */
    std::string to_string(void) const;

    /**
     * @brief Writes array data to a file, following a header string
     * @param[in] fname Name of output file
     * @param[in] header String written to fname before array data
     */
    void to_file(const std::string &fname,
                 const std::string &header) const;

    /**
     * @brief Fills the array with a constant
     * @param[in] f Fill value
     */
    void fill(const double f);
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of ArrSection to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o ArrSection object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const ArrSection &o);

#endif // ARRSECTION_H
