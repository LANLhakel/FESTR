#ifndef PROGRESS_H
#define PROGRESS_H

/**
 * @file Progress.h
 * @brief Progress objects are used to monitor the progress of a calculation.
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 8 August 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <string>
#include <ostream>

//-----------------------------------------------------------------------------

/// Object for monitoring the progress of a calculation
class Progress
{
private:

    /// Name of *this Progress object
    std::string name;

    /// Common root of printed strings: contains the name of *this object
    std::string label;

    /// Indentation preceding the showing of Progress::name
    int level;

    /// Number of cases (no percentage prints, ? for total, if n = 0)
    size_t n;

    /// Only print every freq'th case (no prints, if freq = 0)
    size_t freq;

    /// Separator printed between individual cases of *this Progress object
    std::string sep;

    /// Overall internal counter, work range: \f$1 \leq i \leq n\f$
    size_t i;

    /** @brief Modulo internal counter, work range:
     *         \f$1 \leq j \leq freq\f$; if \f$j=freq,\;j\rightarrow 0\f$
     */
    size_t j;

    /// Number of digits needed to display n
    int ndig;

    /// = Progress::n / 100 (used to compute progress as a percentage)
    double rn;

    /// Substring common to all printouts of *this Progress object's cases
    std::string maxstr;

    /// Reference to the targeted output stream
    std::ostream &ostr;

    /// Prints current case
    void print(void) const;

public:

    /// Default constructor
    Progress(void);

    /**
     * @brief Parametrized constructor
     * @param[in] name_in Name of *this Progress object
     * @param[in] level_in Indentation preceding the showing of name
     * @param[in] nin Number of cases
     * @param[in] freq_in Frequency of progress prints
     * @param[in] sep_in Case separation string in prints
     * @param[in] ostr_in Target output stream for prints
     */
    Progress(const std::string &name_in, const int level_in,
             const size_t nin, const size_t freq_in,
             const std::string &sep_in, std::ostream &ostr_in);

    /// Destructor: prints the final case, if not printed already
    ~Progress(void);

    /**
     * @brief Getter for indentation level (Progress::level)
     * @return Indentation level
     */
    int get_level(void) const;

    /**
     * @brief String representation of a Progress object
     * @return String representation of *this
     */
    std::string to_string(void) const;

    /// Advances the counters, prints the case if j reaches freq
    void advance(void);

    /**
     * @brief Keeps or turns off prints in a next-level Progress object; if
     * current case is not printed, next-level Progress will not print either
     * @param[in] f Frequency intended for next-level Progress object
     * @return Frequency to be actually used by next-level Progress object
     */
    size_t get_next_freq(const size_t f) const;
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Progress to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Progress object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const Progress &o);

//-----------------------------------------------------------------------------

#endif // PROGRESS_H
