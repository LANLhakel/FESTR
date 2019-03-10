#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @file constants.h
 * @brief List of fundamental and other constants
 * @author Peter Hakel
 * @date Created on 20 November 2014\n
 * Last modified on 3 March 2019
 * @version 0.8
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <string>

/// Encapsulates global constants
namespace cnst
{

/// Atomic mass unit (g)
const double U = 1.660539e-24;

/// Speed of light in vacuum (cm/s)
const double CV = 2.99792458e10;

/// Number of characters used to display an integer
const int INT_WIDTH = 11;

/// Tolerance to detect rescalings due to arbitrary units
const double SCALE_EQT = 1.0e-5;

const double THIRD = 1.0 / 3.0;
const double PI = 3.1415926535897932384626433832795028842;
const double TWO_PI = 2.0 * PI;
const double FOUR_PI = 4.0 * PI;
const double FOUR_THIRDS_PI = FOUR_PI * THIRD;
const std::string PATH = "./";
const std::string DASHES = "---------------------------------------------";
const std::string ZONE_SEPARATOR = "\n" + DASHES + "\n";

} // namespace cnst

#endif // CONSTANTS_H
