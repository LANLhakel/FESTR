/*=============================================================================
 
trace.inc

#included in test_Ray.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 26 January 2015
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

#include <mesh.inc>
#include <dbase3.inc>
Vector3d r(12.968712349342937, 0.75, 0.5);
Vector3d v(-2.0, 0.0, 0.0);
Ray ray(0, 0, 3, 0, 2, false, r, v, false, "", "");
ray.trace(g, m);

//  end trace.inc
