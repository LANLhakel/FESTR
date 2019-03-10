/**
 * @file ArrDblRangeCheck.inc
 * @brief Include file: tests size conformity between two ArrDbl objects
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 5 December 2014\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*=============================================================================

#included in ArrDbl.cpp

Range checking common to some member functions of class ArrDbl

=============================================================================*/

if (n != a.n)
{
    std::string message = "Error: ArrDbl ranges do not conform:\n";
    message += "size1 = " + utils::int_to_string(n, ' ', 10) + "\n";
    message += "size2 = " + utils::int_to_string(a.n, ' ', 10);
    throw std::range_error(message);
}

// end ArrDblRangeCheck.inc
