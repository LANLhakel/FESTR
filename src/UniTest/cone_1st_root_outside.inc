/*=============================================================================
 
cone_1st_root_outside.inc

#included in test_Cone.cpp

Conical ribbon: a = (2,0); b = (0,2)
1st intercept: (-3, -1) will be rejected, because it is not "contained",
               albeit it is at the smaller positive distance from the
               Ray's previous position
2nd intercept: (1, 1) will be returned

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 22 May 2015
Last modified on 28 January 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.9 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

FaceID fid(9, 8);
FacePtr f = std::make_shared<Cone>(4, 3);
Vector3d a(2.0, 0.0, 0.0);
Vector3d b(0.0, 2.0, 0.0);
Node n0(0, a);
Node n1(1, b);
f->add_node(n0.geti());
f->add_node(n1.geti());
Grid g;
g.add_node(n0);
g.add_node(n1);

Vector3d h1(-3.0, 0.0, -1.0);
Vector3d h2(1.0, 0.0, 1.0);
Vector3d u = h2 - h1; // Ray direction vector
Vector3d p = h1 - u;  // current Ray location

//  end cone_1st_root_outside.inc
