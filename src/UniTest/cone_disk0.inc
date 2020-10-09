/*=============================================================================
 
cone_disk0.inc

#included in test_Cone.cpp

Disk (special Cone, also with a zero inner radius): a = (0,0); b = (1,0)

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 24 May 2015
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
Vector3d a(0.0, 0.0, 0.0);
Vector3d b(1.0, 0.0, 0.0);
Node n0(0, a);
Node n1(1, b);
f->add_node(n0.geti());
f->add_node(n1.geti());
Grid g;
g.add_node(n0);
g.add_node(n1);

//  end cone_disk0.inc
