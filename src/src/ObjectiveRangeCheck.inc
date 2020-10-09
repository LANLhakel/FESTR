/**
 * @file ObjectiveRangeCheck.inc
 * @brief Include file: tests size conformity between two Objective objects
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 25 June 2015\n
 * Last modified on 28 January 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */


/*=============================================================================

#included in Objective.h

Range checking common to some member functions of class Objective

=============================================================================*/

if (n != get_size())
{
    std::string message = "Error: Objective ranges do not conform:\n";
    message += "size1 = " + utils::int_to_string(n, ' ', 10) + "\n";
    message += "size2 = " + utils::int_to_string(get_size(), ' ', 10);
    throw std::range_error(message);
}

//  end ObjectiveRangeCheck.inc
