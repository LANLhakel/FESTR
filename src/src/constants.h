#ifndef LANL_ASC_PEM_CELL_CONSTANTS_H
#define LANL_ASC_PEM_CELL_CONSTANTS_H

/**
 * @file constants.h
 * @brief List of fundamental and other constants
 * @author Peter Hakel
 * @date Created on 20 November 2014\n
 * Last modified on 8 October 2020
 * @version 0.9
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <string>

//-----------------------------------------------------------------------------

/// Global numeric constants
struct cnst
{
/// Atomic mass unit (g)
static const double U;

/// Speed of light in vacuum (cm/s)
static const double CV;

/// Number of characters used to display an integer
static const int INT_WIDTH;

/// Tolerance to detect rescalings due to arbitrary units
static const double SCALE_EQT;

/// \f$\frac{1}{3}\f$
static const double THIRD;

/// \f$\pi\f$
static const double PI;

/// \f$2\pi\f$
static const double TWO_PI;

/// \f$4\pi\f$
static const double FOUR_PI;

/// \f$\frac{4\pi}{3}\f$
static const double FOUR_THIRDS_PI;

}; // struct cnst


/// Global string constants
namespace cnststr
{
/// Working directory
const std::string PATH = "./";

/// Separator
const std::string DASHES = "---------------------------------------------";

/// Zone separator
const std::string ZONE_SEPARATOR = "\n" + DASHES + "\n";

} // namespace cnststr

#endif  // LANL_ASC_PEM_CONSTANTS_H_
