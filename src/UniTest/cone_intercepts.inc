/*=============================================================================
 
cone_intercepts.inc

#included in test_Cone.cpp

Conical ribbon: a = (2,4); b = (5,8); (#included from "cone.cpp")
1st intercept: (3, 5 1/3) rotated by phi = 30 degrees ( = h1)
2nd intercept: (4, 6 2/3) rotated by phi = 45 degrees ( = h2)

pmh_2015_0521

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 21 May 2015
Last modified on 27 February 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.9 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

#include <cone.inc>
Vector3d h1(1.5*sqrt(3.0), 1.5, 5.0 + 1.0/3.0);
Vector3d h2(4.0/sqrt(2.0), 4.0/sqrt(2.0), 6.0 + 2.0/3.0);
Vector3d u = h2 - h1; // Ray direction vector

//  end cone_intercepts.inc
