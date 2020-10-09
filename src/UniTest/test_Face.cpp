/*=============================================================================

test_Face.cpp
Definitions for unit, integration, and regression tests for class Face.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 13 November 2018
Last modified on 2 October 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.8 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

#include <test_Face.h>
#include <Test.h>

void test_Face(int &failed_test_count, int &disabled_test_count)
{   // empty; there are no instances of an abstract base class,
    // its code is tested via classes that are derived from it.
    (void)(failed_test_count);
    (void)(disabled_test_count);
}

//  end test_Face.cpp
