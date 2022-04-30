/*=============================================================================
 
cone_vertical_ray.inc

#included in test_Cone.cpp, cone_intercepts.inc

Conical ribbon: a = (0.0, 0.60498412); b = (0.03071343, 0.60783436)

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 17 February 2022
Last modified on 17 February 2022

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
Vector3d a(0.0, 0.60498412, 0.0);
Vector3d b(0.03071343, 0.60783436, 0.0);
Node n0(0, a, 3*a);
Node n1(1, b, 3*b);
f->add_node(n0.geti());
f->add_node(n1.geti());
Grid g;
g.add_node(n0);
g.add_node(n1);
Vector3d p = Vector3d(0.0, 0.0, 20.6); // current Ray location
Vector3d u = Vector3d(0.0, 0.0, -cnst::CV); // current Ray direction

//  end cone_vertical_ray.inc
