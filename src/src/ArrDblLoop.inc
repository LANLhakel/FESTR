/**
 * @file ArrDblLoop.inc
 * @brief Include file: ArrDbl loop statements
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

#included in ArrDbl.cpp, Detector.cpp, Ray.cpp, Objective.h

Loop setup common to some member functions of classes ArrDbl, Objective

This code can be modified to implement explicit
parallelization, threading, vectorization of this common loop.

=============================================================================*/

#ifdef OMPYES
#pragma omp parallel for
#endif
for (size_t i = 0; i < n; ++i)

// end ArrDblLoop.inc
