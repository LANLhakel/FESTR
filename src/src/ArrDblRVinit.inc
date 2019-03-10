/**
 * @file ArrDblRVinit.inc
 * @brief Include file: creates a new ArrDbl object with the size of another
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

Return value initialization common to some member functions of class ArrDbl

=============================================================================*/

ArrDbl rv;
rv.n = n;
rv.v.resize(n);

// end ArrDblRVinit.inc
