#ifndef EQUALITY_H
#define EQUALITY_H

/*=============================================================================

equality.h
Equality test functions for various data types.

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 23 October 2014
Last modified on 3 March 2019

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.8 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

#include <cmath>

//-----------------------------------------------------------------------------

// Equality test for discrete data types

template<typename ObjectType>
bool are_equal(const ObjectType &x, const ObjectType &y)
{
    return x == y;
}

//-----------------------------------------------------------------------------

// Equality test with tolerance eqt for float, double, etc.

template<typename RealType>
bool are_equal_real_num(const RealType &x, const RealType &y,
                        const RealType &eqt)
{
    return fabs(x-y) < eqt;
}

//-----------------------------------------------------------------------------

// Equality test with tolerance eqt for objects containing float, double, etc.
// data members. ObjectType must define member function x.abs_diff(y)
// to quantify the "absolute difference" between object instances x and y.

template<typename ObjectType, typename RealType>
bool are_equal_real_obj(const ObjectType &x, const ObjectType &y,
                        const RealType &eqt)
{
    return x.abs_diff(y) < eqt;
}

//-----------------------------------------------------------------------------

#endif // EQUALITY_H
